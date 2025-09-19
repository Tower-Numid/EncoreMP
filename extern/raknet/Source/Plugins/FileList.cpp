/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  Copyright (c) 2016-2018, TES3MP Team
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "FileList.h"

#if _CRABNET_SUPPORT_FileOperations == 1

#include <stdio.h> // CRABNET_DEBUG_PRINTF
#include "RakAssert.h"

#if defined(ANDROID)
#include <asm/io.h>
#elif defined(_WIN32) || defined(__CYGWIN__)
#include <io.h>
#endif


#ifdef _WIN32
// For mkdir
#include <direct.h>
#else

#include <sys/stat.h>

#endif

//#include "DR_SHA1.h"
#include "DS_Queue.h"
#include "StringCompressor.h"
#include "BitStream.h"
#include "FileOperations.h"
#include "SuperFastHash.h"
#include "RakAssert.h"
#include "../Utils/LinuxStrings.h"

#define MAX_FILENAME_LENGTH 512
static const unsigned HASH_LENGTH = 4;

using namespace RakNet;

// alloca

#if   defined(_WIN32)
#include <malloc.h>
#else
#if !defined ( __FreeBSD__ )
#include <alloca.h>
#endif

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../Utils/_FindFirst.h"
#include <stdint.h> //defines intptr_t
#endif

#include "RakAlloca.h"

//int RAK_DLL_EXPORT FileListNodeComp( char * const &key, const FileListNode &data )
//{
//    return strcmp(key, data.filename);
//}


STATIC_FACTORY_DEFINITIONS(FileListProgress, FileListProgress)
STATIC_FACTORY_DEFINITIONS(FLP_Printf, FLP_Printf)
STATIC_FACTORY_DEFINITIONS(FileList, FileList)

#ifdef _MSC_VER
#pragma warning(push)
#endif

/// First callback called when FileList::AddFilesFromDirectory() starts
void FLP_Printf::OnAddFilesFromDirectoryStarted(FileList *, char *dir)
{
    CRABNET_DEBUG_PRINTF("Adding files from directory %s\n", dir);
}

/// Called for each directory, when that directory begins processing
void FLP_Printf::OnDirectory(FileList *, char *dir, unsigned int directoriesRemaining)
{
    CRABNET_DEBUG_PRINTF("Adding %s. %i remaining.\n", dir, directoriesRemaining);
}

void FLP_Printf::OnFilePushesComplete(SystemAddress systemAddress, unsigned short)
{
    char str[32];
    systemAddress.ToString(true, (char *) str);
    CRABNET_DEBUG_PRINTF("File pushes complete to %s\n", str);
}

void FLP_Printf::OnSendAborted(SystemAddress systemAddress)
{
    char str[32];
    systemAddress.ToString(true, (char *) str);
    CRABNET_DEBUG_PRINTF("Send aborted to %s\n", str);
}

FileList::~FileList()
{
    Clear();
}

void FileList::AddFile(const char *filepath, const char *filename, FileListNodeContext context)
{
    if (filepath == nullptr || filename == nullptr)
        return;

    char *data;

    FILE *fp = fopen(filepath, "rb");
    if (fp == nullptr)
        return;
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (length > (int) ((unsigned int) -1 / 8))
    {
        // If this assert hits, split up your file. You could also change BitSize_t in RakNetTypes.h to unsigned long long but this is not recommended for performance reasons
        RakAssert("Cannot add files over 536 MB" && 0);
        fclose(fp);
        return;
    }


#if USE_ALLOCA == 1
    bool usedAlloca = false;
    if (length < MAX_ALLOCA_STACK_ALLOCATION)
    {
        data = (char *) alloca(length);
        usedAlloca = true;
    }
    else
#endif
    {
        data = (char *) malloc(length);
        RakAssert(data);
    }

    size_t ret = fread(data, 1, length, fp);
    RakAssert(ret == (size_t) length)
    AddFile(filename, filepath, data, length, length, context);
    fclose(fp);

#if USE_ALLOCA == 1
    if (!usedAlloca)
#endif
    free(data);

}

void FileList::AddFile(const char *filename, const char *fullPathToFile, const char *data, const unsigned dataLength,
                       const unsigned fileLength, FileListNodeContext context, bool isAReference, bool takeDataPointer)
{
    if (filename == nullptr)
        return;
    if (strlen(filename) > MAX_FILENAME_LENGTH)
    {
        // Should be enough for anyone
        RakAssert(0);
        return;
    }
    // If adding a reference, do not send data
    RakAssert(!isAReference || data == nullptr);
    // Avoid duplicate insertions unless the data is different, in which case overwrite the old data
    for (unsigned i = 0; i < fileList.Size(); i++)
    {
        if (strcmp(fileList[i].filename, filename) == 0)
        {
            if (fileList[i].fileLengthBytes == fileLength && fileList[i].dataLengthBytes == dataLength &&
                (dataLength == 0 || fileList[i].data == nullptr ||
                 memcmp(fileList[i].data, data, dataLength) == 0
                ))
                // Exact same file already here
                return;

            // File of the same name, but different contents, so overwrite
            free(fileList[i].data);
            fileList.RemoveAtIndex(i);
            break;
        }
    }

    FileListNode n;
//    size_t fileNameLen = strlen(filename);
    if ((dataLength != 0u) && (data != nullptr))
    {
        if (takeDataPointer)
            n.data = (char *) data;
        else
        {
            n.data = (char *) malloc(dataLength);
            RakAssert(n.data);
            memcpy(n.data, data, dataLength);
        }
    }
    else
        n.data = nullptr;
    n.dataLengthBytes = dataLength;
    n.fileLengthBytes = fileLength;
    n.isAReference = isAReference;
    n.context = context;
    if (n.context.dataPtr == nullptr)
        n.context.dataPtr = n.data;
    if (n.context.dataLength == 0)
        n.context.dataLength = dataLength;
    n.filename = filename;
    n.fullPathToFile = fullPathToFile;

    fileList.Insert(n);
}

void FileList::AddFilesFromDirectory(const char *applicationDirectory, const char *subDirectory, bool writeHash,
                                     bool writeData, bool recursive, FileListNodeContext context)
{


    DataStructures::Queue<char *> dirList;
    char root[260];
    char fullPath[520];
    _finddata_t fileInfo{};

    auto dirSoFar = (char *) malloc(520);
    RakAssert(dirSoFar);

    if (applicationDirectory != nullptr)
        strcpy(root, applicationDirectory);
    else
        root[0] = 0;

    int rootLen = (int) strlen(root);
    if (rootLen != 0)
    {
        strcpy(dirSoFar, root);
        if (FixEndingSlash(dirSoFar))
            rootLen++;
    }
    else
        dirSoFar[0] = 0;

    if (subDirectory != nullptr)
    {
        strcat(dirSoFar, subDirectory);
        FixEndingSlash(dirSoFar);
    }
    for (unsigned int flpcIndex = 0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
        fileListProgressCallbacks[flpcIndex]->OnAddFilesFromDirectoryStarted(this, dirSoFar);
    // CRABNET_DEBUG_PRINTF("Adding files from directory %s\n",dirSoFar);
    dirList.Push(dirSoFar);

    while (dirList.Size())
    {
        dirSoFar = dirList.Pop();
        strcpy(fullPath, dirSoFar);
        // Changed from *.* to * for Linux compatibility
        strcat(fullPath, "*");


        long dir = _findfirst(fullPath, &fileInfo);
        if (dir == -1)
        {
            _findclose(dir);
            free(dirSoFar);
            for (unsigned i = 0; i < dirList.Size(); i++)
                free(dirList[i]);
            return;
        }

//        CRABNET_DEBUG_PRINTF("Adding %s. %i remaining.\n", fullPath, dirList.Size());
        for (unsigned int flpcIndex = 0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
            fileListProgressCallbacks[flpcIndex]->OnDirectory(this, fullPath, dirList.Size());

        do
        {
            // no guarantee these entries are first...
            if (strcmp(".", fileInfo.name) == 0 || strcmp("..", fileInfo.name) == 0)
                continue;

            if ((fileInfo.attrib & (_A_HIDDEN | _A_SUBDIR | _A_SYSTEM)) == 0)
            {
                strcpy(fullPath, dirSoFar);
                strcat(fullPath, fileInfo.name);
                char *fileData = nullptr;

                for (unsigned int flpcIndex = 0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
                    fileListProgressCallbacks[flpcIndex]->OnFile(this, dirSoFar, fileInfo.name, fileInfo.size);

                if (writeData && writeHash)
                {
                    FILE *fp = fopen(fullPath, "rb");
                    if (fp != nullptr)
                    {
                        fileData = (char *) malloc(fileInfo.size + HASH_LENGTH);
                        RakAssert(fileData);
                        size_t ret = fread(fileData + HASH_LENGTH, fileInfo.size, 1, fp);
                        RakAssert(ret == fileInfo.size)

                        fclose(fp);

                        unsigned int hash = SuperFastHash(fileData + HASH_LENGTH, fileInfo.size);
                        if (RakNet::BitStream::DoEndianSwap())
                            RakNet::BitStream::ReverseBytesInPlace((unsigned char *) &hash, sizeof(hash));
                        memcpy(fileData, &hash, HASH_LENGTH);

                        //                    sha1.Reset();
                        //                    sha1.Update( ( unsigned char* ) fileData+HASH_LENGTH, fileInfo.size );
                        //                    sha1.Final();
                        //                    memcpy(fileData, sha1.GetHash(), HASH_LENGTH);
                        // File data and hash
                        AddFile((const char *) fullPath + rootLen, fullPath, fileData, fileInfo.size + HASH_LENGTH,
                                fileInfo.size, context);
                    }
                }
                else if (writeHash)
                {
//                    sha1.Reset();
//                    DR_SHA1.hashFile((char*)fullPath);
//                    sha1.Final();

                    unsigned int hash = SuperFastHashFile(fullPath);
                    if (RakNet::BitStream::DoEndianSwap())
                        RakNet::BitStream::ReverseBytesInPlace((unsigned char *) &hash, sizeof(hash));

                    // Hash only
                    //    AddFile((const char*)fullPath+rootLen, (const char*)sha1.GetHash(), HASH_LENGTH, fileInfo.size, context);
                    AddFile((const char *) fullPath + rootLen, fullPath, (const char *) &hash, HASH_LENGTH,
                            fileInfo.size, context);
                }
                else if (writeData)
                {
                    fileData = (char *) malloc(fileInfo.size);
                    RakAssert(fileData);
                    FILE *fp = fopen(fullPath, "rb");
                    size_t ret = fread(fileData, fileInfo.size, 1, fp);
                    RakAssert(ret == fileInfo.size)
                    fclose(fp);

                    // File data only
                    AddFile(fullPath + rootLen, fullPath, fileData, fileInfo.size, fileInfo.size, context);
                }
                else
                {
                    // Just the filename
                    AddFile(fullPath + rootLen, fullPath, 0, 0, fileInfo.size, context);
                }

                free(fileData);
            }
            else if ((fileInfo.attrib & _A_SUBDIR) && (fileInfo.attrib & (_A_HIDDEN | _A_SYSTEM)) == 0 && recursive)
            {
                auto newDir = (char *) malloc(520);
                RakAssert(newDir);
                strcpy(newDir, dirSoFar);
                strcat(newDir, fileInfo.name);
                strcat(newDir, "/");
                dirList.Push(newDir);
            }

        } while (_findnext(dir, &fileInfo) != -1);

        _findclose(dir);
        free(dirSoFar);
    }

}

void FileList::Clear()
{
    for (unsigned i = 0; i < fileList.Size(); i++)
        free(fileList[i].data);
    fileList.Clear(false);
}

void FileList::Serialize(RakNet::BitStream *outBitStream)
{
    outBitStream->WriteCompressed(fileList.Size());
    for (unsigned i = 0; i < fileList.Size(); i++)
    {
        outBitStream->WriteCompressed(fileList[i].context.op);
        outBitStream->WriteCompressed(fileList[i].context.flnc_extraData1);
        outBitStream->WriteCompressed(fileList[i].context.flnc_extraData2);
        StringCompressor::Instance().EncodeString(fileList[i].filename.C_String(), MAX_FILENAME_LENGTH, outBitStream);

        bool writeFileData = (fileList[i].dataLengthBytes > 0) == true;
        outBitStream->Write(writeFileData);
        if (writeFileData)
        {
            outBitStream->WriteCompressed(fileList[i].dataLengthBytes);
            outBitStream->Write(fileList[i].data, fileList[i].dataLengthBytes);
        }

        outBitStream->Write((bool) (fileList[i].fileLengthBytes == fileList[i].dataLengthBytes));
        if (fileList[i].fileLengthBytes != fileList[i].dataLengthBytes)
            outBitStream->WriteCompressed(fileList[i].fileLengthBytes);
    }
}

bool FileList::Deserialize(RakNet::BitStream *inBitStream)
{
    char filename[512];
    uint32_t fileListSize;
    bool b = inBitStream->ReadCompressed(fileListSize);

    RakAssert(b);
    RakAssert(fileListSize < 10000);

    if (!b || fileListSize > 10000)
        return false; // Sanity check
    Clear();
    for (unsigned i = 0; i < fileListSize; i++)
    {
        FileListNode n;
        inBitStream->ReadCompressed(n.context.op);
        inBitStream->ReadCompressed(n.context.flnc_extraData1);
        inBitStream->ReadCompressed(n.context.flnc_extraData2);
        StringCompressor::Instance().DecodeString((char *) filename, MAX_FILENAME_LENGTH, inBitStream);

        bool dataLenNonZero;
        inBitStream->Read(dataLenNonZero);
        if (dataLenNonZero)
        {
            inBitStream->ReadCompressed(n.dataLengthBytes);
            // sanity check
            if (n.dataLengthBytes > 2000000000)
            {
                RakAssert(n.dataLengthBytes <= 2000000000);
                return false;
            }
            n.data = (char *) malloc((size_t) n.dataLengthBytes);
            RakAssert(n.data);
            inBitStream->Read(n.data, n.dataLengthBytes);
        }
        else
        {
            n.dataLengthBytes = 0;
            n.data = nullptr;
        }

        bool fileLenMatchesDataLen;
        b = inBitStream->Read(fileLenMatchesDataLen);
        if (fileLenMatchesDataLen)
            n.fileLengthBytes = (unsigned) n.dataLengthBytes;
        else
            b = inBitStream->ReadCompressed(n.fileLengthBytes);

        RakAssert(b);

        if (!b)
        {
            Clear();
            return false;
        }

        n.filename = filename;
        n.fullPathToFile = filename;
        fileList.Insert(n);
    }

    return true;
}

void FileList::GetDeltaToCurrent(FileList *input, FileList *output, const char *dirSubset, const char *remoteSubdir)
{
    // For all files in this list that do not match the input list, write them to the output list.
    // dirSubset allows checking only a portion of the files in this list.
    unsigned dirSubsetLen, remoteSubdirLen;
    if (dirSubset != nullptr)
        dirSubsetLen = (unsigned int) strlen(dirSubset);
    else
        dirSubsetLen = 0;
    if ((remoteSubdir != nullptr) && (remoteSubdir[0] != 0))
    {
        remoteSubdirLen = (unsigned int) strlen(remoteSubdir);
        if (IsSlash(remoteSubdir[remoteSubdirLen - 1]))
            remoteSubdirLen--;
    }
    else
        remoteSubdirLen = 0;

    for (unsigned thisIndex = 0; thisIndex < fileList.Size(); thisIndex++)
    {
        unsigned localPathLen = (unsigned int) fileList[thisIndex].filename.GetLength();
        while (localPathLen > 0)
        {
            if (IsSlash(fileList[thisIndex].filename[localPathLen - 1]))
            {
                localPathLen--;
                break;
            }
            localPathLen--;
        }

        // fileList[thisIndex].filename has to match dirSubset and be shorter or equal to it in length.
        if (dirSubsetLen > 0 &&
            (localPathLen < dirSubsetLen ||
             _strnicmp(fileList[thisIndex].filename.C_String(), dirSubset, dirSubsetLen) != 0 ||
             (localPathLen > dirSubsetLen && IsSlash(fileList[thisIndex].filename[dirSubsetLen]) == false)))
            continue;

        bool match = false;
        for (unsigned inputIndex = 0; inputIndex < input->fileList.Size(); inputIndex++)
        {
            // If the filenames, hashes, and lengths match then skip this element in fileList.  Otherwise write it to output
            if (_stricmp(input->fileList[inputIndex].filename.C_String() + remoteSubdirLen,
                         fileList[thisIndex].filename.C_String() + dirSubsetLen) == 0)
            {
                match = true;
                if (input->fileList[inputIndex].fileLengthBytes == fileList[thisIndex].fileLengthBytes &&
                    input->fileList[inputIndex].dataLengthBytes == fileList[thisIndex].dataLengthBytes &&
                    memcmp(input->fileList[inputIndex].data, fileList[thisIndex].data,
                           (size_t) fileList[thisIndex].dataLengthBytes) == 0)
                {
                    // File exists on both machines and is the same.
                    break;
                }
                else
                {
                    // File exists on both machines and is not the same.
                    output->AddFile(fileList[thisIndex].filename, fileList[thisIndex].fullPathToFile, 0, 0,
                                    fileList[thisIndex].fileLengthBytes, FileListNodeContext(0, 0, 0, 0), false);
                    break;
                }
            }
        }
        if (!match)
        {
            // Other system does not have the file at all
            output->AddFile(fileList[thisIndex].filename, fileList[thisIndex].fullPathToFile, 0, 0,
                            fileList[thisIndex].fileLengthBytes, FileListNodeContext(0, 0, 0, 0), false);
        }
    }
}

void FileList::ListMissingOrChangedFiles(const char *applicationDirectory, FileList *missingOrChangedFiles,
                                         bool alwaysWriteHash, bool neverWriteHash)
{
//    CSHA1 sha1;
    char fullPath[512];
//    char *fileData;

    for (unsigned i = 0; i < fileList.Size(); i++)
    {
        strcpy(fullPath, applicationDirectory);
        FixEndingSlash(fullPath);
        strcat(fullPath, fileList[i].filename);
        FILE *fp = fopen(fullPath, "rb");
        if (fp == nullptr)
        {
            missingOrChangedFiles->AddFile(fileList[i].filename, fileList[i].fullPathToFile, 0, 0, 0,
                                           FileListNodeContext(0, 0, 0, 0), false);
        }
        else
        {
            fseek(fp, 0, SEEK_END);
            unsigned fileLength = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            if (fileLength != fileList[i].fileLengthBytes && alwaysWriteHash == false)
            {
                missingOrChangedFiles->AddFile(fileList[i].filename, fileList[i].fullPathToFile, 0, 0, fileLength,
                                               FileListNodeContext(0, 0, 0, 0), false);
            }
            else
            {

//                fileData= (char*) malloc(( fileLength);
//                fread(fileData, fileLength, 1, fp);

//                sha1.Reset();
//                sha1.Update( ( unsigned char* ) fileData, fileLength );
//                sha1.Final();

//                free(fileData);

                unsigned int hash = SuperFastHashFilePtr(fp);
                if (RakNet::BitStream::DoEndianSwap())
                    RakNet::BitStream::ReverseBytesInPlace((unsigned char *) &hash, sizeof(hash));

                //if (fileLength != fileList[i].fileLength || memcmp( sha1.GetHash(), fileList[i].data, HASH_LENGTH)!=0)
                if (fileLength != fileList[i].fileLengthBytes || memcmp(&hash, fileList[i].data, HASH_LENGTH) != 0)
                {
                    if (!neverWriteHash)
                        //    missingOrChangedFiles->AddFile((const char*)fileList[i].filename, (const char*)sha1.GetHash(), HASH_LENGTH, fileLength, 0);
                        missingOrChangedFiles->AddFile((const char *) fileList[i].filename,
                                                       (const char *) fileList[i].fullPathToFile, (const char *) &hash,
                                                       HASH_LENGTH, fileLength, FileListNodeContext(0, 0, 0, 0), false);
                    else
                        missingOrChangedFiles->AddFile((const char *) fileList[i].filename,
                                                       (const char *) fileList[i].fullPathToFile, 0, 0, fileLength,
                                                       FileListNodeContext(0, 0, 0, 0), false);
                }
            }
            fclose(fp);
        }
    }
}

void FileList::PopulateDataFromDisk(const char *applicationDirectory, bool writeFileData, bool writeFileHash,
                                    bool removeUnknownFiles)
{
    char fullPath[512];
//    CSHA1 sha1;

    for (unsigned i = 0; i < fileList.Size();)
    {
        free(fileList[i].data);
        strcpy(fullPath, applicationDirectory);
        FixEndingSlash(fullPath);
        strcat(fullPath, fileList[i].filename.C_String());
        FILE *fp = fopen(fullPath, "rb");
        if (fp != nullptr)
        {
            if (writeFileHash || writeFileData)
            {
                fseek(fp, 0, SEEK_END);
                fileList[i].fileLengthBytes = (unsigned int) ftell(fp);
                fseek(fp, 0, SEEK_SET);
                if (writeFileHash)
                {
                    if (writeFileData)
                    {
                        // Hash + data so offset the data by HASH_LENGTH
                        fileList[i].data = (char *) malloc(fileList[i].fileLengthBytes + HASH_LENGTH);
                        RakAssert(fileList[i].data);
                        size_t ret = fread(fileList[i].data + HASH_LENGTH, fileList[i].fileLengthBytes, 1, fp);
                        RakAssert(ret == fileList[i].fileLengthBytes)
//                        sha1.Reset();
//                        sha1.Update((unsigned char*)fileList[i].data+HASH_LENGTH, fileList[i].fileLength);
//                        sha1.Final();
                        unsigned int hash = SuperFastHash(fileList[i].data + HASH_LENGTH, fileList[i].fileLengthBytes);
                        if (RakNet::BitStream::DoEndianSwap())
                            RakNet::BitStream::ReverseBytesInPlace((unsigned char *) &hash, sizeof(hash));
//                        memcpy(fileList[i].data, sha1.GetHash(), HASH_LENGTH);
                        memcpy(fileList[i].data, &hash, HASH_LENGTH);
                    }
                    else
                    {
                        // Hash only
                        fileList[i].dataLengthBytes = HASH_LENGTH;
                        if (fileList[i].fileLengthBytes < HASH_LENGTH)
                            fileList[i].data = (char *) malloc(HASH_LENGTH);
                        else
                            fileList[i].data = (char *) malloc(fileList[i].fileLengthBytes);
                        RakAssert(fileList[i].data);
                        size_t ret = fread(fileList[i].data, fileList[i].fileLengthBytes, 1, fp);
                        RakAssert(ret == fileList[i].fileLengthBytes);
                        //        sha1.Reset();
                        //        sha1.Update((unsigned char*)fileList[i].data, fileList[i].fileLength);
                        //        sha1.Final();
                        unsigned int hash = SuperFastHash(fileList[i].data, fileList[i].fileLengthBytes);
                        if (RakNet::BitStream::DoEndianSwap())
                            RakNet::BitStream::ReverseBytesInPlace((unsigned char *) &hash, sizeof(hash));
                        // memcpy(fileList[i].data, sha1.GetHash(), HASH_LENGTH);
                        memcpy(fileList[i].data, &hash, HASH_LENGTH);
                    }
                }
                else
                {
                    // Data only
                    fileList[i].dataLengthBytes = fileList[i].fileLengthBytes;
                    fileList[i].data = (char *) malloc(fileList[i].fileLengthBytes);
                    RakAssert(fileList[i].data);
                    size_t ret = fread(fileList[i].data, fileList[i].fileLengthBytes, 1, fp);
                    RakAssert(ret == fileList[i].fileLengthBytes);
                }

                fclose(fp);
                i++;
            }
            else
            {
                fileList[i].data = nullptr;
                fileList[i].dataLengthBytes = 0;
            }
        }
        else
        {
            if (removeUnknownFiles)
                fileList.RemoveAtIndex(i);
            else
                i++;
        }
    }
}

void FileList::FlagFilesAsReferences()
{
    for (unsigned int i = 0; i < fileList.Size(); i++)
    {
        fileList[i].isAReference = true;
        fileList[i].dataLengthBytes = fileList[i].fileLengthBytes;
    }
}

void FileList::WriteDataToDisk(const char *applicationDirectory)
{
    char fullPath[512];

    for (unsigned i = 0; i < fileList.Size(); i++)
    {
        strcpy(fullPath, applicationDirectory);
        FixEndingSlash(fullPath);
        strcat(fullPath, fileList[i].filename.C_String());

        // Security - Don't allow .. in the filename anywhere so you can't write outside of the root directory
        for (unsigned j = 1; j < fileList[i].filename.GetLength(); j++)
        {
            if (fileList[i].filename[j] == '.' && fileList[i].filename[j - 1] == '.')
            {
                RakAssert(0);
                // Just cancel the write entirely
                return;
            }
        }

        WriteFileWithDirectories(fullPath, fileList[i].data, (unsigned int) fileList[i].dataLengthBytes);
    }
}

#ifdef _MSC_VER
#pragma warning( disable : 4996 ) // unlink declared deprecated by Microsoft in order to make it harder to be cross platform.  I don't agree it's deprecated.
#endif

void FileList::DeleteFiles(const char *applicationDirectory)
{
    for (unsigned i = 0; i < fileList.Size(); i++)
    {
        // The filename should not have .. in the path - if it does ignore it
        for (unsigned j = 1; j < fileList[i].filename.GetLength(); j++)
        {
            if (fileList[i].filename[j] == '.' && fileList[i].filename[j - 1] == '.')
            {
                RakAssert(0);
                // Just cancel the deletion entirely
                return;
            }
        }

        char fullPath[512];

        strcpy(fullPath, applicationDirectory);
        FixEndingSlash(fullPath);
        strcat(fullPath, fileList[i].filename.C_String());

        if (unlink(fullPath) != 0)
        {
            CRABNET_DEBUG_PRINTF("FileList::DeleteFiles: unlink (%s) failed.\n", fullPath);
        }
    }

}

void FileList::AddCallback(FileListProgress *cb)
{
    if (cb == nullptr)
        return;

    if (fileListProgressCallbacks.GetIndexOf(cb) == (unsigned int) -1)
        fileListProgressCallbacks.Push(cb);
}

void FileList::RemoveCallback(FileListProgress *cb)
{
    unsigned int idx = fileListProgressCallbacks.GetIndexOf(cb);
    if (idx != (unsigned int) -1)
        fileListProgressCallbacks.RemoveAtIndex(idx);
}

void FileList::ClearCallbacks()
{
    fileListProgressCallbacks.Clear(true);
}

void FileList::GetCallbacks(DataStructures::List<FileListProgress *> &callbacks)
{
    callbacks = fileListProgressCallbacks;
}


bool FileList::FixEndingSlash(char *str)
{
#ifdef _WIN32
    if (str[strlen(str)-1]!='/' && str[strlen(str)-1]!='\\')
    {
        strcat(str, "\\"); // Only \ works with system commands, used by AutopatcherClient
        return true;
    }
#else
    if (str[strlen(str) - 1] != '\\' && str[strlen(str) - 1] != '/')
    {
        strcat(str, "/"); // Only / works with Linux
        return true;
    }
#endif

    return false;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _CRABNET_SUPPORT_FileOperations
