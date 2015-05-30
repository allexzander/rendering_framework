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
		/**insert new Node
			@_pParent  = _parent of new inserted Node
			@_pNewNode = Node to insert
		*/
		void insert(MapNode<TKey, TData>* _pParent, MapNode<TKey, TData>* _pNewNode);
		
		/**create and insert new Node, given it's key and data
			@_key  = new Node key
			@_data = new Node data
		*/
		void insert(const TKey& _key, const TData& _data)
		{
			MapNode<TKey, TData>* pNewNode = new MapNode<TKey, TData>(_key, _data);
			insert(m_pRoot, pNewNode);
		}

		/*
		**returns const Node*, if found in a tree
		nullptr, otherwise
		*/
		const MapNode<TKey, TData>* find(const TKey& _key, MapNode<TKey, TData>* _currentNode = nullptr) const;

	private:
		MapNode<TKey,TData>* m_pRoot;
		size_t				 m_Size;
	};

	//class Map methods definition
	template <class TKey, class TData>
	void Map<TKey, TData>::insert(MapNode<TKey, TData>* _pParent, MapNode<TKey, TData>* _pNewNode)
	{
		if (m_Size == 0)
		{
			m_pRoot = _pNewNode;
			++m_Size;
		}
		else
		{
			if (_pNewNode->getKey() == _pParent->getKey())
			{
				return;
			}

			if (_pNewNode->getKey() < _pParent->getKey())
			{
				if (!_pParent->getLeftChild())
				{
					_pParent->setLeftChild(_pNewNode);
					++m_Size;
				}
				else
				{
					insert(_pParent->getLeftChild(), _pNewNode);
				}
			}
			else
			{
				if (!_pParent->getRightChild())
				{
					_pParent->setRightChild(_pNewNode);
					++m_Size;
				}
				else
				{
					insert(_pParent->getRightChild(), _pNewNode);
				}
			}
		}
	}

	template <class TKey, class TData>
	const MapNode<TKey, TData>* Map<TKey,TData>::find(const TKey& _key, MapNode<TKey, TData>* _currentNode = nullptr) const
	{
		if (m_Size > 0)
		{
			if (_currentNode == nullptr)
			{
				_currentNode = m_pRoot;
			}

			if (_currentNode->getKey() == _key)
			{
				return _currentNode;
			}

			if (_key < _currentNode->getKey())
			{
				//search in left subtree
				if (_currentNode->getLeftChild() != nullptr)
				{
					return find(_key, _currentNode->getLeftChild());
				}
			}
			else
			{
				//search in right subtree
				if (_currentNode->getRightChild() != nullptr)
				{
					return find(_key, _currentNode->getRightChild());
				}
			}
		}
		return nullptr;
	}

}; //CORE_LIB