#pragma once

#include <stdexcept>
#include <assert.h>
#include "commondefs.h"

namespace CORE_LIB
{
	//MapNode
	template <class TKey, class TData>
	class MapNode
	{
	public:
		//default constructor
		MapNode() : m_pLeft(nullptr), m_pRight(nullptr)
		{
		}
		//constructor with 2 arguments
		MapNode(const TKey& _key, const TData& _data) : MapNode()
		{
			m_Data = _data;
			m_Key = _key;
		}
		//constructor with 4 arguments
		MapNode(const TKey& _key, const TData& _data, MapNode<TKey, TData>* _left, MapNode<TKey, TData>* _right) : 
			m_Key(_key), m_Data(_data),
			m_pLeft(_left), m_pRight(_right)
		{
		}
		//copy constructor
		MapNode(const MapNode<TKey, TData>& _copy) : 
			m_Key(_copy.getKey), m_Data(_copy.getData()),
			m_pLeft(_copy.getLeftChild()), m_pRight(_copy.getRightChild())
		{
		}
	public:
		MapNode<TKey,TData>* getLeftChild()
		{
			return m_pLeft;
		}
		MapNode<TKey,TData>* getRightChild()
		{
			return m_pRight;
		}
		void setLeftChild(MapNode<TKey,TData>* _pLeft)
		{
			m_pLeft = _pLeft;
		}
		void setRightChild(MapNode<TKey,TData>* _pRight)
		{
			m_pRight = _pRight;
		}
		const TData& getData() const
		{
			return m_Data;
		}
		void setData(const TData& _data)
		{
			m_Data = _data;
		}
		const TKey& getKey() const
		{
			return m_Key;
		}
		void setKey(const TKey& _key)
		{
			m_Key = _key;
		}
	private:
		TData m_Data;
		TKey m_Key;
		MapNode* m_pLeft;
		MapNode* m_pRight;
	};

	//Map
	template <class TKey, class TData>
	class Map
	{
	public:
		//default constructor
		Map() : m_pRoot(nullptr), m_Size(0)
		{
		}
		/*TODO--/
		constructors
		/-----*/
	public:
		void insert(MapNode<TKey,TData>* _parent, MapNode<TKey,TData>* _pNewNode)
		{
			if (m_Size == 0)
			{
				m_pRoot = _pNewNode;
				++m_Size;
			}
			else
			{
				if (_pNewNode->getData() < _parent->getData())
				{
					if (!_parent->getLeftChild())
					{
						_parent->setLeftChild(_pNewNode);
						++m_Size;
					}
					else
					{
						insert(_parent->getLeftChild(), _pNewNode);
					}
				}
				else
				{
					if (!_parent->getRightChild())
					{
						_parent->setRightChild(_pNewNode);
						++m_Size;
					}
					else
					{
						insert(_parent->getRightChild(), _pNewNode);
					}
				}
			}
		}
		void insert(const TKey& _key, const TData& _data)
		{
			MapNode<TKey, TData>* pNewNode = new MapNode<TKey, TData>(_key, _data);
			insert(m_pRoot, pNewNode);
		}
		bool find(const TKey& _inKey, MapNode<TKey, TData>* _currentNode, TData& _outFoundData)
		{
			/*if (_inKey == _currentNode)
			if (_inKey < _currentNode->getData())
			{
				return find(_inKey, _currentNode->getLeftChild(), _outFoundData);
			}
			else
			{
				return find(_inKey, _currentNode->getRightChild(), _outFoundData);
			}*/
			assert("Implement me!!!!");
			return false;
		}
	private:
		MapNode<TKey,TData>* m_pRoot;
		size_t				 m_Size;
	};

}; //CORE_LIB