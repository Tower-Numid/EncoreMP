/**
* Original file by the_viking, fixed by R√¥mulo Fernandes, fixed by Emmanuel Nars
* Should emulate windows finddata structure
*/
#if (defined(__GNUC__) || defined(__GCCXML__)) && !defined(_WIN32)

#include "_FindFirst.h"
#include "DS_List.h"

#include "FileList.h"

#include <sys/stat.h>

#include <fnmatch.h>

static DataStructures::List<_findinfo_t *> fileInfo;

#include "RakAssert.h"

/**
* _findfirst - equivalent
*/
long _findfirst(const char *name, _finddata_t *f)
{
    std::string nameCopy = name;
    std::string filter;

    // This is linux only, so don't bother with '\'
    const char *lastSep = strrchr(name, '/');
    if (!lastSep)
    {
        // filter pattern only is given, search current directory.
        filter = nameCopy;
        nameCopy = ".";
    }
    else
    {
        // strip filter pattern from directory name, leave
        // trailing '/' intact.
        filter = lastSep + 1;
        size_t sepIndex = lastSep - name;
        nameCopy.erase(sepIndex + 1, nameCopy.length() - sepIndex - 1);
    }

    DIR *dir = opendir(nameCopy.c_str());

    if (!dir)
        return -1;

    auto *fi = new _findinfo_t;
    fi->filter = filter;
    fi->dirName = nameCopy;  // we need to remember this for stat()
    fi->openedDir = dir;
    fileInfo.Insert(fi);

    long ret = fileInfo.Size() - 1;

    // Retrieve the first file. We cannot rely on the first item
    // being '.'
    if (_findnext(ret, f) == -1)
        return -1;
    
    return ret;
}

int _findnext(long h, _finddata_t *f)
{
    RakAssert(h >= 0 && h < (long) fileInfo.Size());
    if (h < 0 || h >= (long) fileInfo.Size()) return -1;

    _findinfo_t *fi = fileInfo[h];

    dirent *entry;
    while ((entry = readdir(fi->openedDir)) != nullptr)
    {
        // Only report stuff matching our filter
        if (fnmatch(fi->filter.c_str(), entry->d_name, FNM_PATHNAME) != 0) continue;

        // To reliably determine the entry's type, we must do
        // a stat...  don't rely on entry->d_type, as this
        // might be unavailable!
        struct stat filestat{};
        std::string fullPath = fi->dirName + entry->d_name;

        if (stat(fullPath.c_str(), &filestat) != 0)
        {
            CRABNET_DEBUG_PRINTF("Cannot stat %s\n", fullPath.c_str());
            continue;
        }

        if (S_ISREG(filestat.st_mode))
            f->attrib = _A_NORMAL;
        else if (S_ISDIR(filestat.st_mode))
            f->attrib = _A_SUBDIR;
        else
            continue;  // We are interested in files and directories only. Links currently are not supported.

        f->size = (unsigned long) filestat.st_size;
        strncpy(f->name, entry->d_name, STRING_BUFFER_SIZE);

        return 0;
    }

    return -1;
}

/**
 * _findclose - equivalent
 */
int _findclose(long h)
{
    if (h == -1) return 0;

    if (h < 0 || h >= (long) fileInfo.Size())
    {
        RakAssert(false);
        return -1;
    }

    _findinfo_t *fi = fileInfo[h];
    closedir(fi->openedDir);
    fileInfo.RemoveAtIndex(h);
    delete fi;
    return 0;
}

#endif
