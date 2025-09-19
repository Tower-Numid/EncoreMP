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

/// \file DS_Map.h
/// \internal
/// \brief Map
///


#ifndef __CRABNET_MAP_H
#define __CRABNET_MAP_H

#include "DS_OrderedList.h"
#include "Export.h"
#include "RakAssert.h"

// If I want to change this to a red-black tree, this is a good site: http://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
// This makes insertions and deletions faster.  But then traversals are slow, while they are currently fast.

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{
    /// The default comparison has to be first so it can be called as a default parameter.
    /// It then is followed by MapNode, followed by NodeComparisonFunc
    template <class key_type>
        int defaultMapKeyComparison(const key_type &a, const key_type &b)
    {
        if (a<b) return -1; if (a==b) return 0; return 1;
    }

    /// \note IMPORTANT! If you use defaultMapKeyComparison then call IMPLEMENT_DEFAULT_COMPARISON or you will get an unresolved external linker error.
    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&, const key_type&)=defaultMapKeyComparison<key_type> >
    class RAK_DLL_EXPORT Map
    {
    public:
        static void IMPLEMENT_DEFAULT_COMPARISON() {DataStructures::defaultMapKeyComparison<key_type>(key_type(),key_type());}

        struct MapNode
        {
            MapNode() = default;
            MapNode(key_type _key, data_type _data) : mapNodeKey(_key), mapNodeData(_data) {}
            MapNode& operator = ( const MapNode& input ) {mapNodeKey=input.mapNodeKey; mapNodeData=input.mapNodeData; return *this;}
            MapNode( const MapNode & input) {mapNodeKey=input.mapNodeKey; mapNodeData=input.mapNodeData;}
            key_type mapNodeKey;
            data_type mapNodeData;
        };

        // Has to be a static because the comparison callback for DataStructures::OrderedList is a C function
        static int NodeComparisonFunc(const key_type &a, const MapNode &b)
        {
#ifdef _MSC_VER
#pragma warning( disable : 4127 ) // warning C4127: conditional expression is constant
#endif
            return key_comparison_func(a, b.mapNodeKey);
        }

        Map();
        ~Map();
        Map( const Map& original_copy );
        Map& operator= ( const Map& original_copy );

        data_type& Get(const key_type &key) const;
        data_type Pop(const key_type &key);
        // Add if needed
        void Set(const key_type &key, const data_type &data);
        // Must already exist
        void SetExisting(const key_type &key, const data_type &data);
        // Must add
        void SetNew(const key_type &key, const data_type &data);
        bool Has(const key_type &key) const;
        bool Delete(const key_type &key);
        data_type& operator[] (unsigned int position) const;
        key_type GetKeyAtIndex(unsigned int position) const;
        unsigned GetIndexAtKey(const key_type &key);
        void RemoveAtIndex(unsigned index);
        void Clear();
        unsigned Size() const;

    protected:
        DataStructures::OrderedList< key_type,MapNode,&Map::NodeComparisonFunc > mapNodeList;

        unsigned lastSearchIndex;
        key_type lastSearchKey;
        bool lastSearchIndexValid;
    };

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    Map<key_type, data_type, key_comparison_func>::Map()
    {
        lastSearchIndexValid = false;
        lastSearchIndex = 0;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    Map<key_type, data_type, key_comparison_func>::~Map()
    {
        Clear();
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    Map<key_type, data_type, key_comparison_func>::Map( const Map& original_copy )
    {
        mapNodeList=original_copy.mapNodeList;
        lastSearchIndex=original_copy.lastSearchIndex;
        lastSearchKey=original_copy.lastSearchKey;
        lastSearchIndexValid=original_copy.lastSearchIndexValid;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    Map<key_type, data_type, key_comparison_func>& Map<key_type, data_type, key_comparison_func>::operator= ( const Map& original_copy )
    {
        mapNodeList=original_copy.mapNodeList;
        lastSearchIndex=original_copy.lastSearchIndex;
        lastSearchKey=original_copy.lastSearchKey;
        lastSearchIndexValid=original_copy.lastSearchIndexValid;
        return *this;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    data_type& Map<key_type, data_type, key_comparison_func>::Get(const key_type &key) const
    {
        bool objectExists;
        unsigned index = mapNodeList.GetIndexFromKey(key, &objectExists);
        RakAssert(objectExists);
        return mapNodeList[index].mapNodeData;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    unsigned Map<key_type, data_type, key_comparison_func>::GetIndexAtKey( const key_type &key )
    {
        bool objectExists;
        unsigned index = mapNodeList.GetIndexFromKey(key, &objectExists);
        RakAssert(objectExists);
        return index;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    void Map<key_type, data_type, key_comparison_func>::RemoveAtIndex(const unsigned index)
    {
        mapNodeList.RemoveAtIndex(index);
        lastSearchIndexValid = false;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
        data_type Map<key_type, data_type, key_comparison_func>::Pop(const key_type &key)
    {
        bool objectExists;
        unsigned index = mapNodeList.GetIndexFromKey(key, &objectExists);
        RakAssert(objectExists);

        data_type tmp = mapNodeList[index].mapNodeData;
        mapNodeList.RemoveAtIndex(index);
        lastSearchIndexValid = false;
        return tmp;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    void Map<key_type, data_type, key_comparison_func>::Set(const key_type &key, const data_type &data)
    {
        bool objectExists;
        unsigned index = mapNodeList.GetIndexFromKey(key, &objectExists);
        if (objectExists)
            mapNodeList[index].mapNodeData=data;
        else
            mapNodeList.Insert(key, MapNode(key, data), true);
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    void Map<key_type, data_type, key_comparison_func>::SetExisting(const key_type &key, const data_type &data)
    {
        bool objectExists;

        unsigned index = mapNodeList.GetIndexFromKey(key, &objectExists);
        RakAssert(objectExists);

        mapNodeList[index].mapNodeData=data;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    void Map<key_type, data_type, key_comparison_func>::SetNew(const key_type &key, const data_type &data)
    {
#ifdef _DEBUG
        bool objectExists;
        mapNodeList.GetIndexFromKey(key, &objectExists);
        RakAssert(!objectExists);
#endif
        mapNodeList.Insert(key, MapNode(key, data), true);
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    bool Map<key_type, data_type, key_comparison_func>::Has(const key_type &key) const
    {
        bool objectExists;
        unsigned index = mapNodeList.GetIndexFromKey(key, &objectExists);
        return objectExists;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    bool Map<key_type, data_type, key_comparison_func>::Delete(const key_type &key)
    {
        bool objectExists;
        unsigned index = mapNodeList.GetIndexFromKey(key, &objectExists);
        if (objectExists)
        {
            lastSearchIndexValid=false;
            mapNodeList.RemoveAtIndex(index);
            return true;
        }
        else
            return false;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    void Map<key_type, data_type, key_comparison_func>::Clear()
    {
        lastSearchIndexValid = false;
        mapNodeList.Clear(false);
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    data_type& Map<key_type, data_type, key_comparison_func>::operator[]( const unsigned int position ) const
    {
        return mapNodeList[position].mapNodeData;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
        key_type Map<key_type, data_type, key_comparison_func>::GetKeyAtIndex( const unsigned int position ) const
    {
        return mapNodeList[position].mapNodeKey;
    }

    template <class key_type, class data_type, int (*key_comparison_func)(const key_type&,const key_type&)>
    unsigned Map<key_type, data_type, key_comparison_func>::Size() const
    {
        return mapNodeList.Size();
    }
}

#endif
