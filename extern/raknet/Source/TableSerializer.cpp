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

#include "TableSerializer.h"
#include "DS_Table.h"
#include "BitStream.h"
#include "StringCompressor.h"
#include "RakAssert.h"

using namespace RakNet;

void TableSerializer::SerializeTable(DataStructures::Table *in, RakNet::BitStream *out)
{
    DataStructures::Page<unsigned, DataStructures::Table::Row *, _TABLE_BPLUS_TREE_ORDER> *cur = in->GetRows().GetListHead();
    const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns = in->GetColumns();
    SerializeColumns(in, out);
    out->Write(in->GetRows().Size());
    while (cur)
    {
        for (unsigned rowIndex = 0; rowIndex < (unsigned) cur->size; rowIndex++)
            SerializeRow(cur->data[rowIndex], cur->keys[rowIndex], columns, out);
        cur = cur->next;
    }
}

void TableSerializer::SerializeColumns(DataStructures::Table *in, RakNet::BitStream *out)
{
    const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns = in->GetColumns();
    out->Write(columns.Size());
    for (unsigned i = 0; i < columns.Size(); i++)
    {
        StringCompressor::Instance().EncodeString(columns[i].columnName, _TABLE_MAX_COLUMN_NAME_LENGTH, out);
        out->Write((unsigned char) columns[i].columnType);
    }
}

void TableSerializer::SerializeColumns(DataStructures::Table *in, RakNet::BitStream *out,
                                       DataStructures::List<int> &skipColumnIndices)
{
    const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns = in->GetColumns();
    out->Write(columns.Size() - skipColumnIndices.Size());

    for (unsigned i = 0; i < columns.Size(); i++)
    {
        if (skipColumnIndices.GetIndexOf(i) == (unsigned) -1)
        {
            StringCompressor::Instance().EncodeString(columns[i].columnName, _TABLE_MAX_COLUMN_NAME_LENGTH, out);
            out->Write((unsigned char) columns[i].columnType);
        }
    }
}

bool
TableSerializer::DeserializeTable(unsigned char *serializedTable, unsigned int dataLength, DataStructures::Table *out)
{
    RakNet::BitStream in(serializedTable, dataLength, false);
    return DeserializeTable(&in, out);
}

bool TableSerializer::DeserializeTable(RakNet::BitStream *in, DataStructures::Table *out)
{
    unsigned rowSize;
    DeserializeColumns(in, out);
    if (!in->Read(rowSize) || rowSize > 100000)
    {
        RakAssert(0);
        return false; // Hacker crash prevention
    }

    for (unsigned rowIndex = 0; rowIndex < rowSize; rowIndex++)
    {
        if (!DeserializeRow(in, out))
            return false;
    }
    return true;
}

bool TableSerializer::DeserializeColumns(RakNet::BitStream *in, DataStructures::Table *out)
{
    unsigned columnSize;
    if (!in->Read(columnSize) || columnSize > 10000)
        return false; // Hacker crash prevention

    out->Clear();
    for (unsigned i = 0; i < columnSize; i++)
    {
        char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH];
        StringCompressor::Instance().DecodeString(columnName, 32, in);
        unsigned char columnType;
        in->Read(columnType);
        out->AddColumn(columnName, (DataStructures::Table::ColumnType) columnType);
    }
    return true;
}

void TableSerializer::SerializeRow(DataStructures::Table::Row *in, unsigned keyIn,
                                   const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns,
                                   RakNet::BitStream *out)
{
    out->Write(keyIn);
    unsigned int columnsSize = columns.Size();
    out->Write(columnsSize);
    for (unsigned cellIndex = 0; cellIndex < columns.Size(); cellIndex++)
    {
        out->Write(cellIndex);
        SerializeCell(out, in->cells[cellIndex], columns[cellIndex].columnType);
    }
}

void TableSerializer::SerializeRow(DataStructures::Table::Row *in, unsigned keyIn,
                                   const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns,
                                   RakNet::BitStream *out, DataStructures::List<int> &skipColumnIndices)
{
    out->Write(keyIn);
    unsigned int numEntries = 0;
    for (unsigned cellIndex = 0; cellIndex < columns.Size(); cellIndex++)
    {
        if (skipColumnIndices.GetIndexOf(cellIndex) == (unsigned) -1)
            numEntries++;
    }
    out->Write(numEntries);

    for (unsigned cellIndex = 0; cellIndex < columns.Size(); cellIndex++)
    {
        if (skipColumnIndices.GetIndexOf(cellIndex) == (unsigned) -1)
        {
            out->Write(cellIndex);
            SerializeCell(out, in->cells[cellIndex], columns[cellIndex].columnType);
        }
    }
}

bool TableSerializer::DeserializeRow(RakNet::BitStream *in, DataStructures::Table *out)
{
    const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns = out->GetColumns();
    unsigned key;
    if (!in->Read(key))
        return false;
    DataStructures::Table::Row *row = out->AddRow(key);
    unsigned numEntries;
    in->Read(numEntries);
    for (unsigned int cnt = 0; cnt < numEntries; cnt++)
    {
        unsigned cellIndex;
        in->Read(cellIndex);
        if (!DeserializeCell(in, row->cells[cellIndex], columns[cellIndex].columnType))
        {
            out->RemoveRow(key);
            return false;
        }
    }
    return true;
}

void TableSerializer::SerializeCell(RakNet::BitStream *out, DataStructures::Table::Cell *cell,
                                    DataStructures::Table::ColumnType columnType)
{
    out->Write(cell->isEmpty);
    if (!cell->isEmpty)
    {
        if (columnType == DataStructures::Table::NUMERIC)
            out->Write(cell->i);
        else if (columnType == DataStructures::Table::STRING)
            StringCompressor::Instance().EncodeString(cell->c, 65535, out);
        else if (columnType == DataStructures::Table::POINTER)
            out->Write(cell->ptr);
        else
        {
            // Binary
            RakAssert(columnType == DataStructures::Table::BINARY);
            RakAssert(cell->i > 0);
            unsigned binaryLength = (unsigned) cell->i;
            out->Write(binaryLength);
            out->WriteAlignedBytes((const unsigned char *) cell->c, (const unsigned int) cell->i);
        }
    }
}

bool TableSerializer::DeserializeCell(RakNet::BitStream *in, DataStructures::Table::Cell *cell,
                                      DataStructures::Table::ColumnType columnType)
{
    bool isEmpty = false;
    cell->Clear();

    if (!in->Read(isEmpty))
        return false;
    if (!isEmpty)
    {
        if (columnType == DataStructures::Table::NUMERIC)
        {
            double value;
            if (!in->Read(value))
                return false;
            cell->Set(value);
        }
        else if (columnType == DataStructures::Table::STRING)
        {
            char tempString[65535];
            if (!StringCompressor::Instance().DecodeString(tempString, 65535, in))
                return false;
            cell->Set(tempString);
        }
        else if (columnType == DataStructures::Table::POINTER)
        {
            void *ptr;
            if (!in->Read(ptr))
                return false;
            cell->SetPtr(ptr);
        }
        else
        {
            unsigned binaryLength;
            // Binary
            RakAssert(columnType == DataStructures::Table::BINARY);
            if (!in->Read(binaryLength) || binaryLength > 10000000)
                return false; // Sanity check to max binary cell of 10 megabytes
            in->AlignReadToByteBoundary();
            if (BITS_TO_BYTES(in->GetNumberOfUnreadBits()) < (BitSize_t) binaryLength)
                return false;
            cell->Set((char *) in->GetData() + BITS_TO_BYTES(in->GetReadOffset()), (int) binaryLength);
            in->IgnoreBits(BYTES_TO_BITS((int) binaryLength));
        }
    }
    return true;
}

void TableSerializer::SerializeFilterQuery(RakNet::BitStream *in, DataStructures::Table::FilterQuery *query)
{
    StringCompressor::Instance().EncodeString(query->columnName, _TABLE_MAX_COLUMN_NAME_LENGTH, in, 0);
    in->WriteCompressed(query->columnIndex);
    in->Write((unsigned char) query->operation);
    in->Write(query->cellValue->isEmpty);
    if (!query->cellValue->isEmpty)
    {
        in->Write(query->cellValue->i);
        // Sanity check to max binary cell of 10 megabytes
        in->WriteAlignedBytesSafe((const char *) query->cellValue->c, (unsigned int) query->cellValue->i, 10000000);
        in->Write(query->cellValue->ptr);
    }
}

bool TableSerializer::DeserializeFilterQuery(RakNet::BitStream *out, DataStructures::Table::FilterQuery *query)
{
    RakAssert(query->cellValue);
    StringCompressor::Instance().DecodeString(query->columnName, _TABLE_MAX_COLUMN_NAME_LENGTH, out, 0);
    out->ReadCompressed(query->columnIndex);
    unsigned char op;
    out->Read(op);
    query->operation = (DataStructures::Table::FilterQueryType) op;
    query->cellValue->Clear();
    bool b = out->Read(query->cellValue->isEmpty);
    if (!query->cellValue->isEmpty)
    {
        // HACK - cellValue->i is used for integer, character, and binary data.
        // However, for character and binary c will be 0. So use that to determine if the data was integer or not.
        out->Read(query->cellValue->i);
        unsigned int inputLength;
        // Sanity check to max binary cell of 10 megabytes
        out->ReadAlignedBytesSafeAlloc(&query->cellValue->c, inputLength, 10000000);
        if (query->cellValue->c)
            query->cellValue->i = inputLength;
        b = out->Read(query->cellValue->ptr);
    }
    return b;
}

void TableSerializer::SerializeFilterQueryList(RakNet::BitStream *in, DataStructures::Table::FilterQuery *query,
                                               unsigned int numQueries, unsigned int maxQueries)
{
    in->Write((bool) (query && numQueries > 0));
    if (query == 0 || numQueries <= 0)
        return;

    RakAssert(numQueries <= maxQueries);
    in->WriteCompressed(numQueries);
    for (unsigned i = 0; i < numQueries; i++)
        SerializeFilterQuery(in, query);
}

bool TableSerializer::DeserializeFilterQueryList(RakNet::BitStream *out, DataStructures::Table::FilterQuery **query,
                                                 unsigned int *numQueries, unsigned int maxQueries,
                                                 int allocateExtraQueries)
{
    bool anyQueries = false;
    out->Read(anyQueries);
    if (!anyQueries)
    {
        if (allocateExtraQueries <= 0)
            *query = 0;
        else
            *query = new DataStructures::Table::FilterQuery[allocateExtraQueries];

        *numQueries = 0;
        return true;
    }
    bool b = out->ReadCompressed(*numQueries);
    if (*numQueries > maxQueries)
    {
        RakAssert(0);
        *numQueries = maxQueries;
    }
    if (*numQueries == 0)
        return b;

    *query = new DataStructures::Table::FilterQuery[*numQueries + allocateExtraQueries];
    DataStructures::Table::FilterQuery *queryPtr = *query;

    for (unsigned i = 0; i < *numQueries; i++)
    {
        queryPtr[i].cellValue = new DataStructures::Table::Cell;
        b = DeserializeFilterQuery(out, queryPtr + i);
    }

    return b;
}

void TableSerializer::DeallocateQueryList(DataStructures::Table::FilterQuery *query, unsigned int numQueries)
{
    if (query == 0 || numQueries == 0)
        return;

    for (unsigned i = 0; i < numQueries; i++)
        delete query[i].cellValue;
    delete[] query;
}
