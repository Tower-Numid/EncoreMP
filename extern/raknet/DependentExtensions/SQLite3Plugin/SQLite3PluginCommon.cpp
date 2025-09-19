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

#include "SQLite3PluginCommon.h"


SQLite3Table::SQLite3Table()
{

}
SQLite3Table::~SQLite3Table()
{
	for (unsigned int i=0; i < rows.Size(); i++)
		RakNet::OP_DELETE(rows[i]);
}

void SQLite3Table::Serialize(RakNet::BitStream *bitStream)
{
	bitStream->Write(columnNames.Size());
	unsigned int idx1, idx2;
	for (idx1=0; idx1 < columnNames.Size(); idx1++)
		bitStream->Write(columnNames[idx1]);
	bitStream->Write(rows.Size());
	for (idx1=0; idx1 < rows.Size(); idx1++)
	{
		for (idx2=0; idx2 < rows[idx1]->entries.Size(); idx2++)
		{
			bitStream->Write(rows[idx1]->entries[idx2]);
		}
	}
}
void SQLite3Table::Deserialize(RakNet::BitStream *bitStream)
{
	for (unsigned int i=0; i < rows.Size(); i++)
		RakNet::OP_DELETE(rows[i]);
	rows.Clear(true);
	columnNames.Clear(true  );

	unsigned int numColumns, numRows;
	bitStream->Read(numColumns);
	unsigned int idx1,idx2;
	RakNet::RakString inputStr;
	for (idx1=0; idx1 < numColumns; idx1++)
	{
		bitStream->Read(inputStr);
		columnNames.Push(inputStr );
	}
	bitStream->Read(numRows);
	for (idx1=0; idx1 < numRows; idx1++)
	{
		SQLite3Row *row = RakNet::OP_NEW<SQLite3Row>();
		rows.Push(row);
		for (idx2=0; idx2 < numColumns; idx2++)
		{
			bitStream->Read(inputStr);
			row->entries.Push(inputStr );
		}
	}
}