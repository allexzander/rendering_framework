#pragma once

#include <stdexcept>
#include <assert.h>
#include "commondefs.h"

namespace CORE_LIB
{
	//TMapNode
	template <class TKey, class TData>
	class TMapNode
	{
	public:
		TMapNode() : m_pLeft(nullptr), m_pRight(nullptr)
		{
		}

		TMapNode(const TKey& _key, const TData& _data) : m_pLeft(nullptr), m_pRight(nullptr),
			m_Key(_key), m_Data(_data)
		{
		}

		TMapNode(const TKey& _key, const TData& _data, TMapNode<TKey, TData>* _pLeft, TMapNode<TKey, TData>* _pRight)
			: TMapNode(_key, _data), m_pLeft(_pLeft), m_pRight(_pRight)
		{
		}

		//copy constructor
		TMapNode(const TMapNode<TKey, TData>& _other) : m_Key(_other.getKey), m_Data(_other.getData()),
			m_pLeft(_other.getLeftChild()), m_pRight(_other.getRightChild())
		{
		}

	public:
		const TMapNode<TKey, TData>& operator=(TMapNode<TKey, TData>& _rhs)
		{
			m_pLeft  = _rhs.getLeftChild();
			m_pRight = _rhs.getRightChild();
			m_Key	 = _rhs.getKey();
			m_Data	 = _rhs.getData();

			return *this;
		}

	public:
		TMapNode<TKey, TData>* getLeftChild()
		{
			return m_pLeft;
		}

		TMapNode<TKey, TData>* getRightChild()
		{
			return m_pRight;
		}

		const TMapNode<TKey, TData>* getLeftChild() const
		{
			return m_pLeft;
		}

		const TMapNode<TKey, TData>* getRightChild() const
		{
			return m_pRight;
		}

		void setLeftChild(TMapNode<TKey, TData>* _pLeft)
		{
			m_pLeft = _pLeft;
		}

		void setRightChild(TMapNode<TKey, TData>* _pRight)
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
		TKey	  m_Key;
		TData	  m_Data;
		TMapNode* m_pLeft;
		TMapNode* m_pRight;
	};

	//TMap
	template <class TKey, class TData>
	class TMap
	{
	public:
		TMap() : m_pRoot(nullptr), m_Size(0)
		{
		}

		TMap(const TKey* _keys, const TData* _values, size_t _numKeys, size_t _numValues) : TMap()
		{
			for (size_t i = 0; i < _numKeys; ++i)
			{
				insert(_keys[i], _values[i]);
			}
		}

		//copy constructor
		TMap(const TMap<TKey, TData>& _copy) : TMap()
		{
			if (_copy.size() > 0)
			{
				_copyFromPreOrder(_copy.getRoot());
			}
		}

	public:
		const TMap<TKey, TData>& operator=(const TMap<TKey, TData>& _rhs)
		{
			if (_copy.size() > 0)
			{
				_copyFromPreOrder(_copy.getRoot());
			}

			return *this;
		}

	public:
		/**create and insert new Node, given it's key and data
			@_key  = new Node key
			@_data = new Node data
		*/
		void insert(const TKey& _key, const TData& _data)
		{
			auto pNewNode = new TMapNode<TKey, TData>(_key, _data);
			_insert(m_pRoot, pNewNode);
		}


		/**returns const Node*, if found in a tree
		nullptr, otherwise
		*/
		const TMapNode<TKey, TData>* find(const TKey& _key, TMapNode<TKey, TData>* _currentNode = nullptr) const;

		const TMapNode<TKey, TData>* getRoot() const { return m_pRoot; }
		size_t						 size()	   const { return m_Size;  }

		/*
		**Converts entire tree into array, pointed by argument, specified
		@_pOut  = pointer to array, to be filled
		*/
		void toArray(TData* _pOut) const
		{
			_toArray(_pOut, m_pRoot);
		}

		//Deletes all tree leafs
		void clear()
		{
			_clear(m_pRoot);
		}

	private:
		/**Converts tree to array
		@_pOut = pointer to a resulting array
		*/
		void _toArray(TData* _pOut, const TMapNode<TKey, TData>* _pRoot) const;

		/**Copies all nodes from given subtree
		*/
		void _copyFromPreOrder(const TMapNode<TKey, TData>* _pRoot);

		void _clear(TMapNode<TKey, TData>* _pRoot);
		void _insert(TMapNode<TKey, TData>* _pParent, TMapNode<TKey, TData>* _pNewNode);

	private:
		TMapNode<TKey, TData>* m_pRoot;
		size_t				   m_Size;
	};

	//class TMap methods definition
	template <class TKey, class TData>
	void TMap<TKey, TData>::_insert(TMapNode<TKey, TData>* _pParent, TMapNode<TKey, TData>* _pNewNode)
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
					_insert(_pParent->getLeftChild(), _pNewNode);
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
					_insert(_pParent->getRightChild(), _pNewNode);
				}
			}
		}
	}

	template <class TKey, class TData>
	const TMapNode<TKey, TData>* TMap<TKey, TData>::find(const TKey& _key, TMapNode<TKey, TData>* _currentNode = nullptr) const
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
	void TMap<TKey, TData>::_copyFromPreOrder(const TMapNode<TKey, TData>* _pRoot)
	{
		if (_pRoot != nullptr)
		{
			insert(_pRoot->getKey(), _pRoot->getData());
			_copyFromPreOrder(_pRoot->getLeftChild());
			_copyFromPreOrder(_pRoot->getRightChild());
		}
	}

	template <class TKey, class TData>
	void TMap<TKey, TData>::_toArray(TData* _pOut, const TMapNode<TKey, TData>* _pRoot) const
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
	void TMap<TKey, TData>::_clear(TMapNode<TKey, TData>* _pRoot)
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