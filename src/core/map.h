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
			m_Key  = _key;
			m_Data = _data;
		}

		//constructor with 4 arguments
		MapNode(const TKey& _key, const TData& _data, MapNode<TKey, TData>* _left, MapNode<TKey, TData>* _right)
			: MapNode(_key, _data), m_pLeft(_left), m_pRight(_right)
		{
		}

		//copy constructor
		MapNode(const MapNode<TKey, TData>& _copy) : m_Key(_copy.getKey), m_Data(_copy.getData()),
			m_pLeft(_copy.getLeftChild()), m_pRight(_copy.getRightChild())
		{
		}

	public:
		MapNode<TKey, TData>* getLeftChild()
		{
			return m_pLeft;
		}

		MapNode<TKey, TData>* getRightChild()
		{
			return m_pRight;
		}

		const MapNode<TKey, TData>* getLeftChild() const
		{
			return m_pLeft;
		}

		const MapNode<TKey, TData>* getRightChild() const
		{
			return m_pRight;
		}

		void setLeftChild(MapNode<TKey, TData>* _pLeft)
		{
			m_pLeft = _pLeft;
		}

		void setRightChild(MapNode<TKey, TData>* _pRight)
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
		TKey	 m_Key;
		TData	 m_Data;
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

		//constructor from arrays
		Map(const TKey* _keys, const TData* _values, size_t _numKeys, size_t _numValues) : Map()
		{
			for (size_t i = 0; i < _numKeys; ++i)
			{
				insert(_keys[i], _values[i]);
			}
		}

		//copy constructor
		Map(const Map<TKey, TData>& _copy) : Map()
		{
			if (_copy.getSize() > 0)
			{
				_copyFromPreOrder(_copy.getRoot());
			}
		}

	public:
		const Map<TKey, TData>& operator=(const Map<TKey, TData>& _rhs)
		{
			if (_copy.getSize() > 0)
			{
				_copyFromPreOrder(_copy.getRoot());
			}

			return *this;
		}

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
			auto pNewNode = new MapNode<TKey, TData>(_key, _data);
			insert(m_pRoot, pNewNode);
		}

		/*
		**returns const Node*, if found in a tree
		nullptr, otherwise
		*/
		const MapNode<TKey, TData>* find(const TKey& _key, MapNode<TKey, TData>* _currentNode = nullptr) const;

		const MapNode<TKey, TData>* getRoot() const { return m_pRoot; }
		size_t						getSize() const { return m_Size; }
		/*
		**Puts entire tree into array, pointed by argument, specified
		@_pOut  = pointer to array, to be filled
		*/
		void						toArray(TData* _pOut) const
		{
			_toArray(_pOut, m_pRoot);
		}

		/*
		**Removes all leafs and sets m_Size to 0
		*/
		void clear()
		{
			_clear(m_pRoot);
		}

	private:
		void _toArray(TData* _pOut, const MapNode<TKey, TData>* _pRoot) const;
		void _copyFromPreOrder(const MapNode<TKey, TData>* _pRoot);
		void _clear(MapNode<TKey, TData>* _pRoot);
	private:
		MapNode<TKey, TData>* m_pRoot;
		size_t				  m_Size;
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
	const MapNode<TKey, TData>* Map<TKey, TData>::find(const TKey& _key, MapNode<TKey, TData>* _currentNode = nullptr) const
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

	template <class TKey, class TData>
	void Map<TKey, TData>::_copyFromPreOrder(const MapNode<TKey, TData>* _pRoot)
	{
		if (_pRoot != nullptr)
		{
			insert(_pRoot->getKey(), _pRoot->getData());
			_copyFromPreOrder(_pRoot->getLeftChild());
			_copyFromPreOrder(_pRoot->getRightChild());
		}
	}

	template <class TKey, class TData>
	void Map<TKey, TData>::_toArray(TData* _pOut, const MapNode<TKey, TData>* _pRoot) const
	{
		static uint32 index = 0;
		if (m_Size > 0)
		{
			if (_pRoot != nullptr)
			{
				_pOut[index] = _pRoot->getData();
				++index;
				_toArray(_pOut, _pRoot->getLeftChild());
				_toArray(_pOut, _pRoot->getRightChild());
			}
		}

		if (index >= m_Size)
		{
			index = 0;
		}
	}

	template <class TKey, class TData>
	void Map<TKey, TData>::_clear(MapNode<TKey, TData>* _pRoot)
	{
		if (_pRoot == nullptr)
		{
			return;
		}

		if (_pRoot->getLeftChild() != nullptr)
		{
			_clear(_pRoot->getLeftChild());
		}

		if (_pRoot->getRightChild() != nullptr)
		{
			_clear(_pRoot->getRightChild());
		}

		delete _pRoot;
		_pRoot = nullptr;
		--m_Size;
	}

}; //CORE_LIB