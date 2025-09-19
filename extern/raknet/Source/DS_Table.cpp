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

#include "DS_Table.h"
#include "DS_OrderedList.h"
#include <string.h>
#include "RakAssert.h"
#include "RakAssert.h"
#include "Itoa.h"

using namespace DataStructures;

#ifdef _MSC_VER
#pragma warning( push )
#endif

void ExtendRows(Table::Row *input, int index)
{
    (void) index;
    input->cells.Insert(new Table::Cell);
}

void FreeRow(Table::Row *input, int index)
{
    (void) index;

    for (unsigned i = 0; i < input->cells.Size(); i++)
        delete input->cells[i];
    delete input;
}

Table::Cell::Cell()
{
    isEmpty = true;
    c = nullptr;
    ptr = nullptr;
    i = 0.0;
}

Table::Cell::~Cell()
{
    Clear();
}

Table::Cell &Table::Cell::operator=(const Table::Cell &input)
{
    RakAssert(this != &input);
    isEmpty = input.isEmpty;
    i = input.i;
    ptr = input.ptr;

    free(c);

    if (input.c)
    {
        c = (char *) malloc((int) i);
        RakAssert(c);
        memcpy(c, input.c, (int) i);
    }
    else
        c = nullptr;
    return *this;
}

Table::Cell::Cell(const Table::Cell &input)
{
    isEmpty = input.isEmpty;
    i = input.i;
    ptr = input.ptr;
    if (input.c)
    {
        c = (char *) malloc((int) i);
        RakAssert(c);
        memcpy(c, input.c, (int) i);
    }
}

void Table::Cell::Set(double input)
{
    Clear();
    i = input;
    c = nullptr;
    ptr = nullptr;
    isEmpty = false;
}

void Table::Cell::Set(unsigned int input)
{
    Set((int) input);
}

void Table::Cell::Set(int input)
{
    Clear();
    i = (double) input;
    c = nullptr;
    ptr = nullptr;
    isEmpty = false;
}

void Table::Cell::Set(const char *input)
{
    Clear();

    if (input != nullptr)
    {
        i = (int) strlen(input) + 1;
        c = (char *) malloc((int) i);
        RakAssert(c);
        strcpy(c, input);
    }
    else
    {
        c = nullptr;
        i = 0;
    }
    ptr = nullptr;
    isEmpty = false;
}

void Table::Cell::Set(const char *input, int inputLength)
{
    Clear();
    if (input != nullptr)
    {
        c = (char *) malloc(inputLength);
        RakAssert(c);
        i = inputLength;
        memcpy(c, input, inputLength);
    }
    else
    {
        c = nullptr;
        i = 0;
    }
    ptr = nullptr;
    isEmpty = false;
}

void Table::Cell::SetPtr(void *p)
{
    Clear();
    c = nullptr;
    ptr = p;
    isEmpty = false;
}

void Table::Cell::Get(int *output)
{
    RakAssert(!isEmpty);
    int o = (int) i;
    *output = o;
}

void Table::Cell::Get(double *output)
{
    RakAssert(!isEmpty);
    *output = i;
}

void Table::Cell::Get(char *output)
{
    RakAssert(!isEmpty);
    strcpy(output, c);
}

void Table::Cell::Get(char *output, int *outputLength)
{
    RakAssert(!isEmpty);
    memcpy(output, c, (int) i);
    if (outputLength != nullptr)
        *outputLength = (int) i;
}

RakNet::RakString Table::Cell::ToString(ColumnType columnType)
{
    if (isEmpty)
        return RakNet::RakString();

    switch(columnType)
    {
        case NUMERIC:
            return RakNet::RakString("%f", i);
        case STRING:
            return RakNet::RakString(c);
        case BINARY:
            return RakNet::RakString("<Binary>");
        case POINTER:
            return RakNet::RakString("%p", ptr);
        default:
            return RakNet::RakString();
    }
}

Table::Cell::Cell(double numericValue, char *charValue, void *ptr, ColumnType type)
{
    SetByType(numericValue, charValue, ptr, type);
}

void Table::Cell::SetByType(double numericValue, char *charValue, void *ptr, ColumnType type)
{
    isEmpty = true;

    switch(type)
    {
        case NUMERIC:
            Set(numericValue);
            break;
        case STRING:
            Set(charValue);
            break;
        case BINARY:
            Set(charValue, (int) numericValue);
            break;
        case POINTER:
            SetPtr(ptr);
            break;
        default:
            ptr = (void *) charValue;
            break;
    }
}

Table::ColumnType Table::Cell::EstimateColumnType(void) const
{
    if (c != nullptr)
    {
        if (i != 0.0f)
            return BINARY;
        else
            return STRING;
    }

    if (ptr != nullptr)
        return POINTER;
    return NUMERIC;
}

void Table::Cell::Clear()
{
    if (!isEmpty)
    {
        free(c);
        c = nullptr;
    }
    isEmpty = true;
}

Table::ColumnDescriptor::ColumnDescriptor(const char cn[_TABLE_MAX_COLUMN_NAME_LENGTH], ColumnType ct)
{
    columnType = ct;
    strcpy(columnName, cn);
}

void Table::Row::UpdateCell(unsigned columnIndex, double value)
{
    cells[columnIndex]->Clear();
    cells[columnIndex]->Set(value);

//    cells[columnIndex]->i=value;
//    cells[columnIndex]->c=0;
//    cells[columnIndex]->isEmpty=false;
}

void Table::Row::UpdateCell(unsigned columnIndex, const char *str)
{
    cells[columnIndex]->Clear();
    cells[columnIndex]->Set(str);
}

void Table::Row::UpdateCell(unsigned columnIndex, int byteLength, const char *data)
{
    cells[columnIndex]->Clear();
    cells[columnIndex]->Set(data, byteLength);
}

Table::~Table()
{
    Clear();
}

unsigned Table::AddColumn(const char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH], ColumnType columnType)
{
    if (columnName[0] == 0)
        return (unsigned) -1;

    // Add this column.
    columns.Insert(Table::ColumnDescriptor(columnName, columnType));

    // Extend the rows by one
    rows.ForEachData(ExtendRows);

    return columns.Size() - 1;
}

void Table::RemoveColumn(unsigned columnIndex)
{
    if (columnIndex >= columns.Size())
        return;

    columns.RemoveAtIndex(columnIndex);

    // Remove this index from each row.
    DataStructures::Page<unsigned, Row *, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();
    while (cur != nullptr)
    {
        for (int i = 0; i < cur->size; i++)
        {
            delete cur->data[i]->cells[columnIndex];
            cur->data[i]->cells.RemoveAtIndex(columnIndex);
        }

        cur = cur->next;
    }
}

unsigned Table::ColumnIndex(const char *columnName) const
{
    for (unsigned columnIndex = 0; columnIndex < columns.Size(); columnIndex++)
        if (strcmp(columnName, columns[columnIndex].columnName) == 0)
            return columnIndex;
    return (unsigned) -1;
}

unsigned Table::ColumnIndex(char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH]) const
{
    return ColumnIndex((const char *) columnName);
}

char *Table::ColumnName(unsigned index) const
{
    if (index >= columns.Size())
        return nullptr;
    else
        return (char *) columns[index].columnName;
}

Table::ColumnType Table::GetColumnType(unsigned index) const
{
    if (index >= columns.Size())
        return (Table::ColumnType) 0;
    else
        return columns[index].columnType;
}

unsigned Table::GetColumnCount() const
{
    return columns.Size();
}

unsigned Table::GetRowCount() const
{
    return rows.Size();
}

Table::Row *Table::AddRow(unsigned rowId)
{
    Row *newRow = new Row;
    if (!rows.Insert(rowId, newRow))
    {
        delete newRow;
        return nullptr; // Already exists
    }

    for (unsigned rowIndex = 0; rowIndex < columns.Size(); rowIndex++)
        newRow->cells.Insert(new Table::Cell);
    return newRow;
}

Table::Row *Table::AddRow(unsigned rowId, DataStructures::List<Cell> &initialCellValues)
{
    Row *newRow = new Row;
    for (unsigned rowIndex = 0; rowIndex < columns.Size(); rowIndex++)
    {
        if (rowIndex < initialCellValues.Size() && !initialCellValues[rowIndex].isEmpty)
        {
            Table::Cell *c = new Table::Cell;
            c->SetByType(initialCellValues[rowIndex].i, initialCellValues[rowIndex].c, initialCellValues[rowIndex].ptr,
                         columns[rowIndex].columnType);
            newRow->cells.Insert(c);
        }
        else
            newRow->cells.Insert(new Table::Cell);
    }
    rows.Insert(rowId, newRow);
    return newRow;
}

Table::Row *Table::AddRow(unsigned rowId, DataStructures::List<Cell *> &initialCellValues, bool copyCells)
{
    Row *newRow = new Row;
    for (unsigned rowIndex = 0; rowIndex < columns.Size(); rowIndex++)
    {
        if (rowIndex < initialCellValues.Size() && initialCellValues[rowIndex] && !initialCellValues[rowIndex]->isEmpty)
        {
            if (!copyCells)
                newRow->cells.Insert(new Table::Cell(
                        initialCellValues[rowIndex]->i, initialCellValues[rowIndex]->c,
                        initialCellValues[rowIndex]->ptr, columns[rowIndex].columnType));
            else
            {
                Table::Cell *c = new Table::Cell;
                newRow->cells.Insert(c);
                *c = *(initialCellValues[rowIndex]);
            }
        }
        else
            newRow->cells.Insert(new Table::Cell);
    }
    rows.Insert(rowId, newRow);
    return newRow;
}

Table::Row *Table::AddRowColumns(unsigned rowId, Row *row, DataStructures::List<unsigned> columnIndices)
{
    Row *newRow = new Row;
    for (unsigned columnIndex = 0; columnIndex < columnIndices.Size(); columnIndex++)
    {
        if (row->cells[columnIndices[columnIndex]]->isEmpty == false)
        {
            newRow->cells.Insert(new Table::Cell(
                    row->cells[columnIndices[columnIndex]]->i, row->cells[columnIndices[columnIndex]]->c,
                    row->cells[columnIndices[columnIndex]]->ptr, columns[columnIndex].columnType));
        }
        else
            newRow->cells.Insert(new Table::Cell);
    }
    rows.Insert(rowId, newRow);
    return newRow;
}

bool Table::RemoveRow(unsigned rowId)
{
    Row *out;
    if (rows.Delete(rowId, out))
    {
        DeleteRow(out);
        return true;
    }
    return false;
}

void Table::RemoveRows(Table *tableContainingRowIDs)
{
    DataStructures::Page<unsigned, Row *, _TABLE_BPLUS_TREE_ORDER> *cur = tableContainingRowIDs->GetRows().GetListHead();
    while (cur != nullptr)
    {
        for (unsigned i = 0; i < (unsigned) cur->size; i++)
            rows.Delete(cur->keys[i]);
        cur = cur->next;
    }
    return;
}

bool Table::UpdateCell(unsigned rowId, unsigned columnIndex, int value)
{
    RakAssert(columns[columnIndex].columnType == NUMERIC);

    Row *row = GetRowByID(rowId);
    if (row != nullptr)
    {
        row->UpdateCell(columnIndex, value);
        return true;
    }
    return false;
}

bool Table::UpdateCell(unsigned rowId, unsigned columnIndex, char *str)
{
    RakAssert(columns[columnIndex].columnType == STRING);

    Row *row = GetRowByID(rowId);
    if (row != nullptr)
    {
        row->UpdateCell(columnIndex, str);
        return true;
    }
    return false;
}

bool Table::UpdateCell(unsigned rowId, unsigned columnIndex, int byteLength, char *data)
{
    RakAssert(columns[columnIndex].columnType == BINARY);

    Row *row = GetRowByID(rowId);
    if (row != nullptr)
    {
        row->UpdateCell(columnIndex, byteLength, data);
        return true;
    }
    return false;
}

bool Table::UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, int value)
{
    RakAssert(columns[columnIndex].columnType == NUMERIC);

    Row *row = GetRowByIndex(rowIndex, 0);
    if (row != nullptr)
    {
        row->UpdateCell(columnIndex, value);
        return true;
    }
    return false;
}

bool Table::UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, char *str)
{
    RakAssert(columns[columnIndex].columnType == STRING);

    Row *row = GetRowByIndex(rowIndex, 0);
    if (row != nullptr)
    {
        row->UpdateCell(columnIndex, str);
        return true;
    }
    return false;
}

bool Table::UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, int byteLength, char *data)
{
    RakAssert(columns[columnIndex].columnType == BINARY);

    Row *row = GetRowByIndex(rowIndex, 0);
    if (row)
    {
        row->UpdateCell(columnIndex, byteLength, data);
        return true;
    }
    return false;
}

void Table::GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, int *output)
{
    RakAssert(columns[columnIndex].columnType == NUMERIC);

    Row *row = GetRowByIndex(rowIndex, 0);
    if (row != nullptr)
    {
        row->cells[columnIndex]->Get(output);
    }
}

void Table::GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, char *output)
{
    RakAssert(columns[columnIndex].columnType == STRING);

    Row *row = GetRowByIndex(rowIndex, 0);
    if (row != nullptr)
    {
        row->cells[columnIndex]->Get(output);
    }
}

void Table::GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, char *output, int *outputLength)
{
    RakAssert(columns[columnIndex].columnType == BINARY);

    Row *row = GetRowByIndex(rowIndex, 0);
    if (row != nullptr)
    {
        row->cells[columnIndex]->Get(output, outputLength);
    }
}

Table::FilterQuery::FilterQuery(): columnIndex(0), cellValue(0), operation(QF_EQUAL)
{
    columnName[0] = 0;
}

Table::FilterQuery::~FilterQuery()
{

}

Table::FilterQuery::FilterQuery(unsigned column, Cell *cell, FilterQueryType op)
{
    columnName[0] = 0;
    columnIndex = column;
    cellValue = cell;
    operation = op;
}

Table::Row *Table::GetRowByID(unsigned rowId) const
{
    Row *row;
    if (rows.Get(rowId, row))
        return row;
    return nullptr;
}

Table::Row *Table::GetRowByIndex(unsigned rowIndex, unsigned *key) const
{
    DataStructures::Page<unsigned, Row *, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();
    while (cur != nullptr)
    {
        if (rowIndex < (unsigned) cur->size)
        {
            if (key != nullptr)
                *key = cur->keys[rowIndex];
            return cur->data[rowIndex];
        }
        if (rowIndex <= (unsigned) cur->size)
            rowIndex -= cur->size;
        else
            return nullptr;
        cur = cur->next;
    }
    return nullptr;
}

void Table::QueryTable(unsigned *columnIndicesSubset, unsigned numColumnSubset, FilterQuery *inclusionFilters,
                       unsigned numInclusionFilters, unsigned *rowIds, unsigned numRowIDs, Table *result)
{
    DataStructures::List<unsigned> columnIndicesToReturn;

    // Clear the result table.
    result->Clear();

    if ((columnIndicesSubset != nullptr) && numColumnSubset > 0)
    {
        for (unsigned i = 0; i < numColumnSubset; i++)
        {
            if (columnIndicesSubset[i] < columns.Size())
                columnIndicesToReturn.Insert(columnIndicesSubset[i]);
        }
    }
    else
    {
        for (unsigned i = 0; i < columns.Size(); i++)
            columnIndicesToReturn.Insert(i);
    }

    if (columnIndicesToReturn.Size() == 0)
        return; // No valid columns specified

    for (unsigned i = 0; i < columnIndicesToReturn.Size(); i++)
        result->AddColumn(columns[columnIndicesToReturn[i]].columnName, columns[columnIndicesToReturn[i]].columnType);

    // Get the column indices of the filter queries.
    DataStructures::List<unsigned> inclusionFilterColumnIndices;
    if ((inclusionFilters != nullptr) && numInclusionFilters > 0)
    {
        for (unsigned i = 0; i < numInclusionFilters; i++)
        {
            if (inclusionFilters[i].columnName[0])
                inclusionFilters[i].columnIndex = ColumnIndex(inclusionFilters[i].columnName);
            if (inclusionFilters[i].columnIndex < columns.Size())
                inclusionFilterColumnIndices.Insert(inclusionFilters[i].columnIndex);
            else
                inclusionFilterColumnIndices.Insert((unsigned) -1);
        }
    }

    if (rowIds == nullptr || numRowIDs == 0)
    {
        // All rows
        DataStructures::Page<unsigned, Row *, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();
        while (cur != nullptr)
        {
            for (unsigned i = 0; i < (unsigned) cur->size; i++)
            {
                QueryRow(inclusionFilterColumnIndices, columnIndicesToReturn, cur->keys[i], cur->data[i],
                         inclusionFilters, result);
            }
            cur = cur->next;
        }
    }
    else
    {
        // Specific rows
        Row *row;
        for (unsigned i = 0; i < numRowIDs; i++)
        {
            if (rows.Get(rowIds[i], row))
                QueryRow(inclusionFilterColumnIndices, columnIndicesToReturn, rowIds[i], row, inclusionFilters, result);
        }
    }
}

void Table::QueryRow(DataStructures::List<unsigned> &inclusionFilterColumnIndices,
                     DataStructures::List<unsigned> &columnIndicesToReturn, unsigned key, Table::Row *row,
                     FilterQuery *inclusionFilters, Table *result)
{
    bool pass = false;

    // If no inclusion filters, just add the row
    if (inclusionFilterColumnIndices.Size() != 0)
    {
        // Go through all inclusion filters.  Only add this row if all filters pass.
        for (unsigned j = 0; j < inclusionFilterColumnIndices.Size(); j++)
        {
            unsigned columnIndex = inclusionFilterColumnIndices[j];
            if (columnIndex != (unsigned) -1 && !row->cells[columnIndex]->isEmpty)
            {
                if (columns[inclusionFilterColumnIndices[j]].columnType == STRING &&
                    (row->cells[columnIndex]->c == 0 ||
                     inclusionFilters[j].cellValue->c == 0))
                    continue;

                switch (inclusionFilters[j].operation)
                {
                    case QF_EQUAL:
                        switch (columns[inclusionFilterColumnIndices[j]].columnType)
                        {
                            case NUMERIC:
                                pass = row->cells[columnIndex]->i == inclusionFilters[j].cellValue->i;
                                break;
                            case STRING:
                                pass = strcmp(row->cells[columnIndex]->c, inclusionFilters[j].cellValue->c) == 0;
                                break;
                            case BINARY:
                                pass = row->cells[columnIndex]->i == inclusionFilters[j].cellValue->i &&
                                       memcmp(row->cells[columnIndex]->c, inclusionFilters[j].cellValue->c,
                                              (int) row->cells[columnIndex]->i) == 0;
                                break;
                            case POINTER:
                                pass = row->cells[columnIndex]->ptr == inclusionFilters[j].cellValue->ptr;
                                break;
                        }
                        break;
                    case QF_NOT_EQUAL:
                        switch (columns[inclusionFilterColumnIndices[j]].columnType)
                        {
                            case NUMERIC:
                                pass = row->cells[columnIndex]->i != inclusionFilters[j].cellValue->i;
                                break;
                            case STRING:
                                pass = strcmp(row->cells[columnIndex]->c, inclusionFilters[j].cellValue->c) != 0;
                                break;
                            case BINARY:
                                pass = row->cells[columnIndex]->i == inclusionFilters[j].cellValue->i &&
                                       memcmp(row->cells[columnIndex]->c, inclusionFilters[j].cellValue->c,
                                              (int) row->cells[columnIndex]->i) == 0;
                                break;
                            case POINTER:
                                pass = row->cells[columnIndex]->ptr != inclusionFilters[j].cellValue->ptr;
                                break;
                        }
                        break;
                    case QF_GREATER_THAN:
                        switch (columns[inclusionFilterColumnIndices[j]].columnType)
                        {
                            case NUMERIC:
                                pass = row->cells[columnIndex]->i > inclusionFilters[j].cellValue->i;
                                break;
                            case STRING:
                                pass = strcmp(row->cells[columnIndex]->c, inclusionFilters[j].cellValue->c) > 0;
                                break;
                            case BINARY:
                                break;
                            case POINTER:
                                pass = row->cells[columnIndex]->ptr > inclusionFilters[j].cellValue->ptr;
                                break;
                        }
                        break;
                    case QF_GREATER_THAN_EQ:
                        switch (columns[inclusionFilterColumnIndices[j]].columnType)
                        {
                            case NUMERIC:
                                pass = row->cells[columnIndex]->i >= inclusionFilters[j].cellValue->i;
                                break;
                            case STRING:
                                pass = strcmp(row->cells[columnIndex]->c, inclusionFilters[j].cellValue->c) >= 0;
                                break;
                            case BINARY:
                                break;
                            case POINTER:
                                pass = row->cells[columnIndex]->ptr >= inclusionFilters[j].cellValue->ptr;
                                break;
                        }
                        break;
                    case QF_LESS_THAN:
                        switch (columns[inclusionFilterColumnIndices[j]].columnType)
                        {
                            case NUMERIC:
                                pass = row->cells[columnIndex]->i < inclusionFilters[j].cellValue->i;
                                break;
                            case STRING:
                                pass = strcmp(row->cells[columnIndex]->c, inclusionFilters[j].cellValue->c) < 0;
                                break;
                            case BINARY:
                                break;
                            case POINTER:
                                pass = row->cells[columnIndex]->ptr < inclusionFilters[j].cellValue->ptr;
                                break;
                        }
                        break;
                    case QF_LESS_THAN_EQ:
                        switch (columns[inclusionFilterColumnIndices[j]].columnType)
                        {
                            case NUMERIC:
                                pass = row->cells[columnIndex]->i <= inclusionFilters[j].cellValue->i;
                                break;
                            case STRING:
                                pass = strcmp(row->cells[columnIndex]->c, inclusionFilters[j].cellValue->c) <= 0;
                                break;
                            case BINARY:
                                break;
                            case POINTER:
                                pass = row->cells[columnIndex]->ptr <= inclusionFilters[j].cellValue->ptr;
                                break;
                        }
                        break;
                    case QF_IS_EMPTY:
                        pass = false;
                        break;
                    case QF_NOT_EMPTY:
                        pass = true;
                        break;
                    default:
                        pass = false;
                        RakAssert(0);
                        break;
                }
            }
            else
                pass = inclusionFilters[j].operation == QF_IS_EMPTY;

            if (!pass)
                break;
        }

        if (pass)
            result->AddRowColumns(key, row, columnIndicesToReturn);
    }
    else
        result->AddRowColumns(key, row, columnIndicesToReturn);
}

static Table::SortQuery *_sortQueries;
static unsigned _numSortQueries;
static DataStructures::List<unsigned> *_columnIndices;
static DataStructures::List<Table::ColumnDescriptor> *_columns;

int RowSort(Table::Row *const &first,
            Table::Row *const &second) // first is the one inserting, second is the one already there.
{
    for (unsigned i = 0; i < _numSortQueries; i++)
    {
        unsigned columnIndex = (*_columnIndices)[i];
        if (columnIndex == (unsigned) -1)
            continue;

        if (first->cells[columnIndex]->isEmpty && !second->cells[columnIndex]->isEmpty)
            return 1; // Empty cells always go at the end

        if (!first->cells[columnIndex]->isEmpty && second->cells[columnIndex]->isEmpty)
            return -1; // Empty cells always go at the end

        if (_sortQueries[i].operation == Table::QS_INCREASING_ORDER)
        {
            if ((*_columns)[columnIndex].columnType == Table::NUMERIC)
            {
                if (first->cells[columnIndex]->i > second->cells[columnIndex]->i)
                    return 1;
                if (first->cells[columnIndex]->i < second->cells[columnIndex]->i)
                    return -1;
            }
            else
            {
                // String
                if (strcmp(first->cells[columnIndex]->c, second->cells[columnIndex]->c) > 0)
                    return 1;
                if (strcmp(first->cells[columnIndex]->c, second->cells[columnIndex]->c) < 0)
                    return -1;
            }
        }
        else
        {
            if ((*_columns)[columnIndex].columnType == Table::NUMERIC)
            {
                if (first->cells[columnIndex]->i < second->cells[columnIndex]->i)
                    return 1;
                if (first->cells[columnIndex]->i > second->cells[columnIndex]->i)
                    return -1;
            }
            else
            {
                // String
                if (strcmp(first->cells[columnIndex]->c, second->cells[columnIndex]->c) < 0)
                    return 1;
                if (strcmp(first->cells[columnIndex]->c, second->cells[columnIndex]->c) > 0)
                    return -1;
            }
        }
    }

    return 0;
}

void Table::SortTable(Table::SortQuery *sortQueries, unsigned numSortQueries, Table::Row **out)
{
    DataStructures::List<unsigned> columnIndices;
    _sortQueries = sortQueries;
    _numSortQueries = numSortQueries;
    _columnIndices = &columnIndices;
    _columns = &columns;
    bool anyValid = false;

    for (unsigned i = 0; i < numSortQueries; i++)
    {
        if (sortQueries[i].columnIndex < columns.Size() && columns[sortQueries[i].columnIndex].columnType != BINARY)
        {
            columnIndices.Insert(sortQueries[i].columnIndex);
            anyValid = true;
        }
        else
            columnIndices.Insert((unsigned) -1); // Means don't check this column
    }

    DataStructures::Page<unsigned, Row *, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();
    if (!anyValid)
    {
        while (cur != nullptr)
        {
            for (unsigned i = 0; i < (unsigned) cur->size; i++)
                out[i] = cur->data[i];
            cur = cur->next;
        }
        return;
    }

    // Start adding to ordered list.
    DataStructures::OrderedList<Row *, Row *, RowSort> orderedList;
    while (cur != nullptr)
    {
        for (unsigned i = 0; i < (unsigned) cur->size; i++)
        {
            RakAssert(cur->data[i]);
            orderedList.Insert(cur->data[i], cur->data[i], true);
        }
        cur = cur->next;
    }

    for (unsigned i = 0; i < orderedList.Size(); i++)
        out[i] = orderedList[i];
}

void Table::PrintColumnHeaders(char *out, int outLength, char columnDelineator) const
{
    if (outLength <= 0)
        return;
    if (outLength == 1)
    {
        *out = 0;
        return;
    }
    out[0] = 0;

    for (unsigned i = 0; i < columns.Size(); i++)
    {
        if (i != 0)
        {
            int len = (int) strlen(out);
            if (len < outLength - 1)
                sprintf(out + len, "%c", columnDelineator);
            else
                return;
        }

        int len = (int) strlen(out);
        if (len < outLength - (int) strlen(columns[i].columnName))
            sprintf(out + len, "%s", columns[i].columnName);
        else
            return;
    }
}

void Table::PrintRow(char *out, int outLength, char columnDelineator, bool printDelineatorForBinary,
                     Table::Row *inputRow) const
{
    if (outLength <= 0)
        return;
    if (outLength == 1)
    {
        *out = 0;
        return;
    }

    if (inputRow->cells.Size() != columns.Size())
    {
        strncpy(out, "Cell width does not match column width.\n", outLength);
        out[outLength - 1] = 0;
        return;
    }

    char buff[512];

    int len;
    out[0] = 0;
    for (unsigned i = 0; i < columns.Size(); i++)
    {
        if (columns[i].columnType == NUMERIC)
        {
            if (!inputRow->cells[i]->isEmpty)
            {
                sprintf(buff, "%f", inputRow->cells[i]->i);
                len = (int) strlen(buff);
            }
            else
                len = 0;
            if (i + 1 != columns.Size())
            {
                buff[len] = columnDelineator;
                if(len + 1 != sizeof(buff))
                    len++;
            }
            buff[len] = 0;
        }
        else if (columns[i].columnType == STRING)
        {
            if (!inputRow->cells[i]->isEmpty && inputRow->cells[i]->c)
            {
                strncpy(buff, inputRow->cells[i]->c, 512 - 2);
                buff[512 - 2] = 0;
                len = (int) strlen(buff);
            }
            else
                len = 0;
            if (i + 1 != columns.Size())
            {
                buff[len] = columnDelineator;
                if(len + 1 != sizeof(buff))
                    len++;
            }
            buff[len] = 0;
        }
        else if (columns[i].columnType == POINTER)
        {
            if (!inputRow->cells[i]->isEmpty && inputRow->cells[i]->ptr)
            {
                sprintf(buff, "%p", inputRow->cells[i]->ptr);
                len = (int) strlen(buff);
            }
            else
                len = 0;
            if (i + 1 != columns.Size())
            {
                buff[len] = columnDelineator;
                if(len + 1 != sizeof(buff))
                    len++;
            }
            buff[len] = 0;
        }
        else
        {
            if (printDelineatorForBinary)
            {
                if (i + 1 != columns.Size())
                    buff[0] = columnDelineator;
                buff[1] = 0;
            }
            else
                buff[0] = 0;

        }

        len = (int) strlen(out);
        if (outLength == len + 1)
            break;
        strncpy(out + len, buff, outLength - len);
        out[outLength - 1] = 0;
    }
}

void Table::Clear()
{
    rows.ForEachData(FreeRow);
    rows.Clear();
    columns.Clear(true);
}

const List<Table::ColumnDescriptor> &Table::GetColumns() const
{
    return columns;
}

const DataStructures::BPlusTree<unsigned, Table::Row *, _TABLE_BPLUS_TREE_ORDER> &Table::GetRows() const
{
    return rows;
}

DataStructures::Page<unsigned, DataStructures::Table::Row *, _TABLE_BPLUS_TREE_ORDER> *Table::GetListHead()
{
    return rows.GetListHead();
}

unsigned Table::GetAvailableRowId() const
{
    bool setKey = false;
    unsigned key = 0;
    DataStructures::Page<unsigned, Row *, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();

    while (cur != nullptr)
    {
        for (int i = 0; i < cur->size; i++)
        {
            if (!setKey)
            {
                key = cur->keys[i] + 1;
                setKey = true;
            }
            else
            {
                if (key != cur->keys[i])
                    return key;
                key++;
            }
        }

        cur = cur->next;
    }
    return key;
}

void Table::DeleteRow(Table::Row *row)
{
    for (unsigned rowIndex = 0; rowIndex < row->cells.Size(); rowIndex++)
        delete row->cells[rowIndex];
    delete row;
}

Table &Table::operator=(const Table &input)
{
    Clear();
    for (unsigned i = 0; i < input.GetColumnCount(); i++)
        AddColumn(input.ColumnName(i), input.GetColumnType(i));

    DataStructures::Page<unsigned, Row *, _TABLE_BPLUS_TREE_ORDER> *cur = input.GetRows().GetListHead();
    while (cur != nullptr)
    {
        for (unsigned i = 0; i < (unsigned int) cur->size; i++)
            AddRow(cur->keys[i], cur->data[i]->cells, false);

        cur = cur->next;
    }

    return *this;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif
