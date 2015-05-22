#pragma once

#include <stdexcept>
#include <assert.h>
#include "commondefs.h"

namespace CORE_LIB
{
	//MapNode
	template <class T, class U>
	class MapNode
	{
	public:
		//default constructor
		MapNode() : m_pLeft(nullptr), m_pRight(nullptr)
		{
		}
		//constructor with 2 arguments
		MapNode(const T& _data, const U& _key) : MapNode()
		{
			m_Data = _data;
			m_Key = _key;
		}
		//constructor with 4 arguments
		MapNode(MapNode<T, U>* _left, MapNode<T, U>* _right, const T& _data, const U& _key) : m_pLeft(_left),
			m_pRight(_right), m_Data(_data), m_Key(_key)
		{
		}
		//copy constructor
		MapNode(const MapNode<T,U>& _copy) : m_pLeft(_copy.getLeftChild()),
			m_pRight(_copy.getRightChild()), m_Data(_copy.getData())
		{
		}
	public:
		MapNode<T,U>* getLeftChild()
		{
			return m_pLeft;
		}
		MapNode<T,U>* getRightChild()
		{
			return m_pRight;
		}
		void setLeftChild(MapNode<T,U>* _pLeft)
		{
			m_pLeft = _pLeft;
		}
		void setRightChild(MapNode<T,U>* _pRight)
		{
			m_pRight = _pRight;
		}
		const T& getData() const
		{
			return m_Data;
		}
		void setData(const T& _data)
		{
			m_Data = _data;
		}
		const U& getKey() const
		{
			return m_Key;
		}
		void setKey(const T& _key)
		{
			m_Key = _key;
		}
	private:
		T m_Data;
		U m_Key;
		MapNode* m_pLeft;
		MapNode* m_pRight;
	};

	//Map
	template <class T, class U>
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
		void insert(MapNode<T,U>* _parent, MapNode<T,U>* _pNewNode)
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
		void insert(const U& _key, const T& _data)
		{
			MapNode<T,U>* pNewNode = new MapNode<T,U>(_data, _key);
			insert(m_pRoot, pNewNode);
		}
	private:
		MapNode<T,U>* m_pRoot;
		size_t m_Size;
	};

}; //CORE_LIB