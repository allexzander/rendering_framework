#pragma once

#include <stdexcept>
#include <assert.h>
#include "commondefs.h"

namespace CORE_LIB
{
	//Forward declarations
	template <class T> class TList;
	template <class T> class TList_const_iterator;
	template <class T> class TList_iterator;

	//TList Node
	template <class T>
	class TNode
	{
		friend class TList_iterator <T> ;
		friend class TList_const_iterator <T>;
		friend class TList<T>;

	public:
		//default constructor
		TNode() : m_pNext(nullptr)
		{
		}
		//constructor with 1 argument
		TNode(const T& _data) : TNode(_data, nullptr)
		{
		}
		//constructor with 2 arguments
		TNode(const T& _data, TNode<T>* _pNext) : 
			m_Data(_data), m_pNext(_pNext)
		{
		}
		//copy constructor
		TNode(const TNode<T>& _source) :
			TNode(_source.m_Data, _source.m_pNext)
		{
		}

	private:
		T	   m_Data;
		TNode* m_pNext;
	};

	//TList_iterator
	template <class T>
	class TList_iterator
	{
		friend class TList<T>;

	public:
		TList_iterator() : m_pCurrentNode(nullptr)
		{
		}

		TList_iterator(const TList_iterator& _copy) : m_pCurrentNode(_copy.getNode())
		{
		}

	private:
		TList_iterator(TNode<T>* _pNode) : m_pCurrentNode(_pNode)
		{
		}

	public:
		TNode<T>* getNode() const { return m_pCurrentNode; }

		T& getData() const
		{
			assert(m_pCurrentNode && "Error m_pCurrentNode");
			return m_pCurrentNode->m_Data; 
		}

		const TList_iterator& operator=(const TList_iterator& _rhs)
		{
			m_pCurrentNode = _rhs.getNode();
			return *this;
		}

		//prefix operator
		TList_iterator& operator++()
		{
			if (m_pCurrentNode)
			{
				m_pCurrentNode = m_pCurrentNode->m_pNext;
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}

			return *this;
		}

		//postfix operator
		TList_iterator operator++(int)
		{
			auto pTempNode = m_pCurrentNode;

			if (m_pCurrentNode)
			{
				m_pCurrentNode = m_pCurrentNode->m_pNext;
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}

			return pTempNode;
		}

		T& operator*() const
		{
			return getData();
		}

		operator bool() const
		{
			return m_pCurrentNode != nullptr;
		}

		operator TList_const_iterator<T>() const
		{
			return TList_const_iterator<T>(m_pCurrentNode);
		}

		friend bool operator==(const TList_iterator& _lhs, const TList_iterator& _rhs)
		{
			_lhs.m_pCurrentNode == _rhs.m_pCurrentNode;
		}

		friend bool operator!=(const TList_iterator& _lhs, const TList_iterator& _rhs)
		{
			return _lhs.m_pCurrentNode != _rhs.m_pCurrentNode;
		}

	private:
		TNode<T>* m_pCurrentNode;
	}; //class TList_iterator

	//TList_const_iterator
	template <class T>
	class TList_const_iterator
	{
		friend class TList<T>;
		friend class TList_iterator<T>;

	public:
		TList_const_iterator() : m_pCurrentNode(nullptr)
		{
		}

		TList_const_iterator(const TList_const_iterator& _copy) : m_pCurrentNode(_copy.getNode())
		{
		}

	private:
		TList_const_iterator(TNode<T>* _pNode) : m_pCurrentNode(_pNode)
		{
		}

	public:
		TNode<T>* const getNode() const { return m_pCurrentNode; }

		const T& getData() const
		{
			assert(m_pCurrentNode && "Error m_pCurrentNode");
			return m_pCurrentNode->m_Data;
		}

		const TList_const_iterator& operator=(const TList_const_iterator& _rhs)
		{
			m_pCurrentNode = _rhs.getNode();
			return *this;
		}

		//prefix operator
		TList_const_iterator& operator++()
		{
			if (m_pCurrentNode)
			{
				m_pCurrentNode = m_pCurrentNode->m_pNext;
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}

			return *this;
		}

		//postfix operator
		TList_const_iterator operator++(int)
		{
			auto pTempNode = m_pCurrentNode;

			if (m_pCurrentNode)
			{
				m_pCurrentNode = m_pCurrentNode->m_pNext;
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}

			return pTempNode;
		}

		const T& operator*() const
		{
			return getData();
		}

		operator bool() const
		{
			return m_pCurrentNode != nullptr;
		}

		friend bool operator==(const TList_const_iterator& _lhs, const TList_const_iterator& _rhs)
		{
			return _lhs.m_pCurrentNode == _rhs.m_pCurrentNode;
		}

		friend bool operator!=(const TList_const_iterator& _lhs, const TList_const_iterator& _rhs)
		{
			return _lhs.m_pCurrentNode != _rhs.m_pCurrentNode;
		}

	private:
		TNode<T>* m_pCurrentNode;
	}; //class TList_const_iterator

	//TList
	template <class T>
	class TList
	{
	public:
		//default constructor
		TList() : m_pHead(nullptr), m_pTail(nullptr), m_Size(0)
		{
		}

		//copy constructor
		TList(const TList<T>& _source) : TList()
		{
			*this = _source;
		}

		//constructor from array
		TList(const T* _pData, size_t _numData) : TList()
		{
			for (size_t i = 0; i < _numData; ++i)
			{
				push_back(_pData[i]);
			}
		}

		const TList& operator=(const TList & _rhs)
		{
			clear();
			for (TList_const_iterator<T> it = _rhs.constIterator(); it; ++it)
			{
				push_back(*it);
			}
			return *this;
		}

		~TList()
		{
			clear();
		}

	public:
		size_t size() const { return m_Size; }

		void push_back(const T& _data);
		void push_front(const T& _data);
		void pop_back();
		void pop_front();

		void clear();

		void erase(const TList_const_iterator<T>& _pos);
		void erase(const T& _data);
		void insert(TList_iterator<T>& _after, const T& _data);

		const T& at(size_t _index) const;

		const T& back()  const;
		const T& front() const;

		TList_iterator<T>		  iterator()	  const;
		TList_const_iterator<T>	  constIterator() const;

		TList_iterator<T> begin();
		TList_iterator<T> end();

		TList_const_iterator<T> begin() const;
		TList_const_iterator<T> end() const;

		TList_iterator<T>		findFirst(const T& _key);
		TList_const_iterator<T> findFirst(const T& _key) const;

		TList_iterator<T>		findIter(const TList_const_iterator<T>& _it);
		TList_const_iterator<T> findIter(const TList_const_iterator<T>& _it) const;

	private:
		TNode<T>* m_pHead;
		TNode<T>* m_pTail;
		size_t	  m_Size;
	};

	template <class T>
	void TList<T>::push_back(const T& _data)
	{
		auto pNewNode = new TNode<T>(_data);

		if (m_Size == 0)
		{
			m_pHead = m_pTail = pNewNode;
		}
		else
		{
			m_pTail->m_pNext = pNewNode;
			m_pTail = pNewNode;
		}

		++m_Size;
	}

	template <class T>
	void TList<T>::push_front(const T& _data)
	{
		auto pNewNode = new TNode<T>(_data);

		if (m_Size == 0)
		{
			m_pHead = m_pTail = pNewNode;
		}
		else
		{
			pNewNode->m_pNext = m_pHead;
			m_pHead = pNewNode;
		}

		++m_Size;
	}

	template <class T>
	void TList<T>::pop_back()
	{
		assert(m_Size > 0 && "List is empty!!!!");

		if (m_Size > 0)
		{
			if (m_Size == 1)
			{
				delete m_pTail;
				m_pHead = m_pTail = nullptr;
			}
			else
			{
				auto pPreTail = m_pHead;

				while (pPreTail->m_pNext && pPreTail->m_pNext != m_pTail)
				{
					pPreTail = pPreTail->m_pNext;
				}

				delete m_pTail;
				m_pTail = pPreTail;
				pPreTail->m_pNext = nullptr;
			}

			--m_Size;
		}
	}

	template <class T>
	void TList<T>::pop_front()
	{
		assert(m_Size > 0 && "List is empty!!!!");

		if (m_Size > 0)
		{
			if (m_Size == 1)
			{
				delete m_pHead;
				m_pHead = m_pTail = nullptr;
			}
			else
			{
				auto pHead = m_pHead;
				m_pHead	   = m_pHead->m_pNext;
				delete pHead;
			}
			--m_Size;
		}
	}

	template <class T>
	void TList<T>::clear()
	{
		if (m_Size > 0)
		{
			if (m_Size > 1)
			{
				auto pNextNode = m_pHead;

				while (pNextNode != nullptr)
				{
					auto currentNode = pNextNode;
					pNextNode = pNextNode->m_pNext;
					delete currentNode;
				}
			}
			else
			{
				if (m_pHead != nullptr)
				{
					delete m_pHead;
				}
			}

			m_pHead = m_pTail = nullptr;
			m_Size	= 0;
		}
	}

	template <class T>
	void TList<T>::erase(const TList_const_iterator<T>& _pos)
	{
		if (m_Size > 0)
		{
			if (_pos.getNode() == m_pHead)
			{
				pop_front();
				return;
			}
			else if (_pos.getNode() == m_pTail)
			{
				pop_back();
				return;
			}
			else
			{
				auto pPreNodeToDelete = m_pHead;

				while (pPreNodeToDelete && pPreNodeToDelete->m_pNext != _pos.getNode())
				{
					pPreNodeToDelete = pPreNodeToDelete->m_pNext;
				}

				if (pPreNodeToDelete != nullptr)
				{
					auto pNodeToDelete = pPreNodeToDelete->m_pNext;

					if (pNodeToDelete)
					{
						pPreNodeToDelete->m_pNext = pNodeToDelete->m_pNext;
						delete pNodeToDelete;
						--m_Size;
						return;
					}
				}
			}
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}
	}

	template <class T>
	void TList<T>::erase(const T& _data)
	{
		TList_const_iterator<T> it = findFirst(_data);
		erase(it);
	}

	template <class T>
	void TList<T>::insert(TList_iterator<T>& _after, const T& _data)
	{
		if (findIter(_after))
		{
			auto pNewNode = new TNode<T>(_data, _after.getNode()->m_pNext);
			_after.getNode()->m_pNext = pNewNode;

			++m_Size;
		}
		else
		{
			throw std::invalid_argument("Invalid insertion position argument!");
		}
	}

	template <class T>
	/*
		**Linear complicity traversal, by given index
		@_index = index of node
	*/
	const T& TList<T>::at(size_t _index) const
	{
		if (_index > 0 && static_cast<size_t>(_index) < m_Size)
		{
			auto pCurrentNode = m_pHead;
			size_t i = 0;
			for (size_t i = 0; i < _index; ++i)
			{
				if (!pCurrentNode->m_pNext)
				{
					break;
				}

				pCurrentNode = pCurrentNode->m_pNext;
			}
			return pCurrentNode->m_Data;
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}
	}

	template <class T>
	const T& TList<T>::front() const
	{
		return m_pHead->m_Data;
	}

	template <class T>
	const T& TList<T>::back() const
	{
		return m_pTail->m_Data;
	}

	template <class T>
	TList_iterator<T> TList<T>::begin()
	{
		TList_iterator<T> it(m_pHead);
		return it;
	}

	template <class T>
	TList_const_iterator<T> TList<T>::begin() const
	{
		TList_const_iterator<T> it(m_pHead);
		return it;
	}

	template <class T>
	TList_iterator<T> TList<T>::end()
	{
		TList_iterator<T> it(m_pTail);
		return it;
	}

	template <class T>
	TList_const_iterator<T> TList<T>::end() const
	{
		TList_const_iterator<T> it(m_pTail);
		return it;
	}

	template <class T>
	TList_iterator<T> TList<T>::findFirst(const T& _key)
	{
		TList_iterator<T> it = iterator();

		for (; it; ++it)
		{
			if(*it == _key)
			{
				break;
			}
		}

		return it;
	}

	template <class T>
	TList_const_iterator<T> TList<T>::findFirst(const T& _key) const
	{
		TList_iterator<T> it = findFirst(_key);
		return it;
	}

	template <class T>
	TList_iterator<T> TList<T>::iterator() const
	{
		TList_iterator<T> it(m_pHead);
		return it;
	}

	template <class T>
	TList_const_iterator<T> TList<T>::constIterator() const
	{
		TList_const_iterator<T> it(m_pHead);
		return it;
	}

	template <class T>
	TList_iterator<T> TList<T>::findIter(const TList_const_iterator<T>& _it)
	{
		TList_iterator<T> foundIt;

		for (TList_iterator<T> it = iterator(); it; ++it)
		{
			if (it == _it)
			{
				foundIt = it;
				break;
			}
		}

		return foundIt;
	}

	template <class T>
	TList_const_iterator<T> TList<T>::findIter(const TList_const_iterator<T>& _it) const
	{
		TList_const_iterator<T> foundIt = findIter(it);
	}

}; //CORE_LIB