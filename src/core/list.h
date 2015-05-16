#pragma once

#include <stdexcept>
#include <assert.h>
#include "commondefs.h"

namespace CORE_LIB
{
	//Forward declarations
	template <class T> class TList;

	//class Node
	template <class T>
	class Node
	{
	public:
		//default constructor
		Node() : Node(T(0), nullptr)
		{
		}
		//constructor with 1 argument
		Node(const T& _data) : Node(_data, nullptr)
		{
		}
		//constructor with 2 arguments
		Node(const T& _data, Node<T>* _next) : 
			m_Data(_data), m_pNext(_next)
		{
		}
		//copy constructor
		Node(const Node<T>& _source) : Node(_source.getData(), _source.getNext())
		{
		}

	public:
		void	 setNext(Node<T>* _next) { m_pNext = _next; }
		Node<T>* getNext() const { return m_pNext; }

		void	 setData(const T& _data) { m_Data = _data; }
		T&		 getData() { return m_Data; }

		operator T() const
		{
			return m_Data;
		}

	private:
		T	  m_Data;
		Node* m_pNext;
	}; //class Node

	//TList_iterator
	template <class T>
	class TList_iterator
	{
		friend class TList<T>;

	public:
		TList_iterator() : m_pCurrentNode(nullptr)
		{
		}

	private:
		TList_iterator(Node<T>* _node) : m_pCurrentNode(_node)
		{
		}

	public:
		Node<T>* getNode() { return m_pCurrentNode; }

		T& getData() 
		{
			assert(m_pCurrentNode && "Error m_pCurrentNode");
			return m_pCurrentNode->getData(); 
		}

		TList_iterator& operator=(const TList_iterator& _rhs)
		{
			m_pCurrentNode = _rhs.node();
			return *this;
		}

		//prefix operator
		TList_iterator& operator++()
		{
			assert(m_pCurrentNode->getNext() && "Error m_pCurrentNode->getNext()");

			if (m_pCurrentNode->getNext())
			{
				m_pCurrentNode = m_pCurrentNode->getNext();
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
			assert(m_pCurrentNode->getNext() && "Error m_pCurrentNode->getNext()");

			Node<T>* tempNode = m_pCurrentNode;

			if (m_pCurrentNode->getNext())
			{
				m_pCurrentNode = m_pCurrentNode->getNext();
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}

			return tempNode;
		}

		T& operator*()
		{
			return getData();
		}

		operator bool() const
		{
			return m_pCurrentNode && m_pCurrentNode->getNext();
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
		Node<T>* m_pCurrentNode;
	}; //class TList_iterator

	//TList_const_iterator
	template <class T>
	class TList_const_iterator
	{
		friend class TList<T>;

	public:
		TList_const_iterator() : m_pCurrentNode(nullptr)
		{
		}

	private:
		TList_const_iterator(Node<T>* _node) : m_pCurrentNode(_node)
		{
		}

	public:
		Node<T>* getNode() { return m_pCurrentNode; }

		const T& getData()
		{
			assert(m_pCurrentNode && "Error m_pCurrentNode");
			return m_pCurrentNode->getData();
		}

		TList_const_iterator& operator=(const TList_const_iterator& _rhs)
		{
			m_pCurrentNode = _rhs.node();
			return *this;
		}

		//prefix operator
		TList_const_iterator& operator++()
		{
			assert(m_pCurrentNode->getNext() && "Error m_pCurrentNode->getNext()");

			if (m_pCurrentNode->getNext())
			{
				m_pCurrentNode = m_pCurrentNode->getNext();
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
			assert(m_pCurrentNode->getNext() && "Error m_pCurrentNode->getNext()");

			Node<T>* tempNode = m_pCurrentNode;

			if (m_pCurrentNode->getNext())
			{
				m_pCurrentNode = m_pCurrentNode->getNext();
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}

			return tempNode;
		}

		const T& operator*()
		{
			return getData();
		}

		operator bool() const
		{
			return m_pCurrentNode && m_pCurrentNode->getNext();
		}

		friend bool operator==(const TList_const_iterator& _lhs, const TList_const_iterator& _rhs)
		{
			_lhs.m_pCurrentNode == _rhs.m_pCurrentNode;
		}

		friend bool operator!=(const TList_const_iterator& _lhs, const TList_const_iterator& _rhs)
		{
			return _lhs.m_pCurrentNode != _rhs.m_pCurrentNode;
		}

	private:
		Node<T>* m_pCurrentNode;
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
			//!!!TODO!!!
		}
		TList & operator=(const TList & _rhs)
		{
			clear();
			m_pHead = 0;
			m_pTail = 0;
			m_Size  = 0;
			for(TList_const_iterator<T> it = _rhs.begin(); it != _rhs.end(); it++)
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
		void pop_back();

		void clear();

		void erase(TList_iterator<T>& _pos);
		void insert(TList_iterator<T>& _after, const T& _data);

		const T& dataOf(uint32 _i) const;

		const T& back()  const;
		const T& front() const;

		TList_iterator<T>		  iterator()	  const;
		TList_const_iterator<T>	  constIterator() const;

		TList_iterator<T> begin();
		TList_iterator<T> end();

		TList_const_iterator<T> begin() const;
		TList_const_iterator<T> end() const;

		TList_iterator<T> find(const T& _key);

	private:
		Node<T>* m_pHead;
		Node<T>* m_pTail;
		size_t	 m_Size;
	};

	template <class T>
	void TList<T>::push_back(const T& _data)
	{
		Node<T>* newNode = new Node<T>(_data);

		if (m_Size == 0)
		{
			m_pHead = m_pTail = newNode;
		}
		else
		{
			m_pTail->setNext(newNode);
			m_pTail	= newNode;
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
				Node<T>* preTail = m_pHead;

				while (preTail->getNext() && preTail->getNext() != m_pTail)
				{
					preTail = preTail->getNext();
				}

				delete m_pTail;
				m_pTail = preTail;
				preTail->setNext(nullptr);
			}

			--m_Size;
		}
	}

	template <class T>
	void TList<T>::clear()
	{
		if (m_Size > 0)
		{
			Node<T>* nextNode = m_pHead;

			if (nextNode->getNext())
			{
				while (nextNode->getNext())
				{
					Node<T>* currentNode = nextNode;
					nextNode = nextNode->getNext();
					delete currentNode;
				}

				if (nextNode == m_pTail)
				{
					delete nextNode;
				}
			}
			else
			{
				delete nextNode;
			}

			m_pHead = m_pTail = nullptr;
			m_Size	= 0;
		}
	}

	template <class T>
	void TList<T>::erase(TList_iterator<T>& _pos)
	{
		/*if(_pos == begin())
		{
			Node<T>* tempNode = m_pHead->getNext();
			delete m_pHead;
			m_pHead = 0;
			m_pHead = tempNode;
			return;
		}
		TList_iterator<T> prevIt = begin();
		for(TList_iterator<T> it = begin(); it != end(); ++it)
		{
			if(*it == *_pos)
			{
				prevIt.m_pCurrentNode->setNext(it.m_pCurrentNode->getNext());
				delete it.m_pCurrentNode;
				break;
			}
			prevIt = it;
		}
		--m_Size;*/
	}

	template <class T>
	void TList<T>::insert(TList_iterator<T>& _after, const T& _data)
	{
		Node<T>* newNode = new Node<T>(_data, _after.getNode()->getNext());
		_after.getNode()->setNext(newNode);

		++m_Size;
	}

	//Non-effective
	template <class T>
	const T& TList<T>::dataOf(uint32 _i) const
	{
		/*if(m_Size > _i && m_pHead != 0)
		{
			Node<T> *currentNode = m_pHead;
			uint32 i = 0;
			while(i < _i && currentNode->getNext() != 0)
			{
				currentNode = currentNode->getNext();
				++i;
			}
			return currentNode->getData();
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}*/
	}

	template <class T>
	const T& TList<T>::front() const
	{
		return m_pHead->getData();
	}

	template <class T>
	const T& TList<T>::back() const
	{
		/*Node<T>* currenNode = m_pHead;
		Node<T>* previousNode = m_pHead;
		while(currenNode->getNext() != m_pTail)
		{
			currenNode = currenNode->getNext();
			previousNode = currenNode;
		}*/
		return m_pTail->getData();
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
	TList_iterator<T> TList<T>::find(const T& _key)
	{
		/*for(TList_iterator<T> it = begin(); it != end(); ++it)
		{
			if(*it == _key)
			{
				return it;
			}
		}*/
		return end();
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

}; //CORE_LIB