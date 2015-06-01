#pragma once

#include "commondefs.h"
#include "vector.h"
#include "list.h"
#include "map.h"

namespace CORE_LIB
{
	namespace UTILS
	{
		template <class TKey, class TData>
		static void vecToMap(const TVector<TKey>& _inVecKeys, const TVector<TData>& _inVecValues, TMap<TKey, TData>& _outMap)
		{
			_outMap.clear();

			for (size_t i = 0; i < _inVecKeys.size(); ++i)
			{
				_outMap.insert(_inVecKeys[i], _inVecValues[i]);
			}
		}

		template <class TKey, class TData>
		static void listToMap(const TList<TKey>& _inListKeys, const TList<TData>& _inListValues, TMap<TKey, TData>& _outMap)
		{
			_outMap.clear();
			TList_const_iterator<TKey> itKey = _inListKeys.constIterator(); 
			TList_const_iterator<TData> itValue = _inListValues.constIterator();

			for (; itKey, itValue; ++itKey, ++itValue)
			{
				_outMap.insert(*itKey, *itValue);
			}
		}

		template <class TData>
		static void listToVec(const TList<TData>& _inList, TVector<TData>& _outVec)
		{
			_outVec.clear();

			for (TList_const_iterator<TData> it = _inList.constIterator(); it; ++it)
			{
				_outVec.push_back(*it);
			}
		}

		template <class TData>
		static void vecToList(const TVector<TData>& _inVec, TList<TData>& _outList)
		{
			_outList.clear();

			for (TVector_const_iterator<TData> it = _inVec.constIterator(); it; ++it)
			{
				_outList.push_back(*it);
			}
		}

		template <class TKey, class TData>
		static void mapToVec(const TMap<TKey, TData>& _inMap, TVector<TData>& _outVec)
		{
			_outVec.clear();

			TData* pDataBuffer = new TData[_inMap.size()];
			_inMap.toArray(pDataBuffer);

			for (size_t i = 0; i < _inMap.size(); ++i)
			{
				_outVec.push_back(pDataBuffer[i]);
			}
		}

		template <class TKey, class TData>
		static void mapToList(const TMap<TKey, TData>& _inMap, TList<TData>& _outList)
		{
			_outList.clear();

			TData* pDataBuffer = new TData[_inMap.size()];
			_inMap.toArray(pDataBuffer);

			for (size_t i = 0; i < _inMap.size(); ++i)
			{
				_outList.push_back(pDataBuffer[i]);
			}
		}
	};
};