#pragma once

#ifdef __linux__
#include <stdexcept>
#endif //__linux__

//Basic singly-linked TList container

#include "commondefs.h"

namespace CORE_LIB
{
	//Forward declarations
	template <class T> class TList;
	template <class T> class TList_iterator;
	template <class T> class TList_const_iterator;

	//TList Node
	template <class T>
	class Node
	{
	private:
		//Node value(data)
		T m_Data;
		//Pointer to next node
		Node* m_pNext;
	public:
		Node()
		{
			m_pNext = 0;
		}
		//Copy constructor
		Node(const T& _data)
		{
			m_Data = _data;
			m_pNext = 0;
		}
		//Overloaded copy constructor
		Node(const T& _data, Node<T>* _next)
		{
			m_Data = _data;
			m_pNext = _next;
		}
	public:
		//Set pointer to next node
		void setNext(Node<T>* _next) { m_pNext = _next; }
		//Retreive pointer to next node
		Node<T>* getNext() { return m_pNext; }
		//Set node data
		void setData(const T& _data) { m_Data = _data; }
		//Get node data
		T& getData() { return m_Data; }
	};

	//Singly-linked list
	template <class T>
	class TList
	{
	private:
		Node<T>* m_pHead;
		Node<T>* m_pTail;
		uint32 m_Length;
	public:
		TList()
		{
			m_pHead = 0;
			m_pTail = 0;
			m_Length = 0;
		}
		TList(const TList<T>& _source)
		{
			m_pHead = 0;
			m_pTail = 0;
			m_Length = 0;
			//TODO
			/*for(TList_const_iterator<T> it = _source.begin(); it != _source.end(); it++)
			{
			push_back(*it);
			}*/
		}
		TList & operator=(const TList & _rhs)
		{
			clear();
			m_pHead = 0;
			m_pTail = 0;
			m_Length = 0;
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
		uint32 length() const{ return m_Length; }

		void push_back(const T& _data);
		void pop_back();

		void clear();

		void erase(TList_iterator<T>& _pos);
		void insert(TList_iterator<T>& _after, const T& _data);

		const T& dataOf(uint32 _i) const;

		const T& back() const;
		const T& front() const;

		TList_iterator<T> begin();
		TList_iterator<T> end();

		TList_const_iterator<T> begin() const;
		TList_const_iterator<T> end() const;

		TList_iterator<T> find(const T& _key);
	};

	//TList Iterator
	template <class T>
	class TList_iterator
	{
	private:
		//Pointer to current iterable node
		Node<T>* m_pCurrentNode;
	public:
		//Constructor( from list node)
		TList_iterator(Node<T>* _node)
		{
			m_pCurrentNode = _node;
		}
	public:
		//Get node's adress
		Node<T>* node() { return m_pCurrentNode; }
		//Get node's data
		const T& data() { return m_pCurrentNode->m_Data; }
		//Copy operator=
		TList_iterator & operator=(TList_iterator & _rhs)
		{
			m_pCurrentNode = _rhs.node();
			return *this;
		}
		//Copy operator= fron list's node
		TList_iterator & operator=(Node<T>* _rhs)
		{
			m_pCurrentNode = _rhs;
			return *this;
		}
		//Incriment operators
		TList_iterator  operator++()
		{
			if(m_pCurrentNode->getNext() != 0)
			{
				m_pCurrentNode = m_pCurrentNode->getNext();
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}
			return *this;
		}
		TList_iterator  operator++(int)
		{
			Node<T>* tempNode = m_pCurrentNode;
			if(m_pCurrentNode->getNext() != 0)
			{
				m_pCurrentNode = m_pCurrentNode->getNext();
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}
			return tempNode;
		}

		//Operator*(returns current node's data)
		T & operator*()
		{
			return m_pCurrentNode->getData();
		}

		bool operator!=(TList_iterator & _rhs)
		{
			return m_pCurrentNode != _rhs.node();
		}

		bool operator==(TList_iterator & _rhs)
		{
			return m_pCurrentNode == _rhs.node();
		}
	};

	//TList Const Iterator
	template <class T>
	class TList_const_iterator
	{
	private:
		Node<T>* m_pCurrentNode;
	public:
		TList_const_iterator(Node<T>* _node)
		{
			m_pCurrentNode = _node;
		}
	public:
		Node<T>* node() { return m_pCurrentNode; }
		const T& data() { return m_pCurrentNode->m_Data; }
		const TList_const_iterator & operator=(TList_const_iterator & _rhs)
		{
			m_pCurrentNode = _rhs.node();
			return *this;
		}
		const TList_const_iterator & operator=(Node<T>* _rhs)
		{
			m_pCurrentNode = _rhs;
			return *this;
		}
		const TList_const_iterator  operator++()
		{
			if(m_pCurrentNode->getNext() != 0)
			{
				m_pCurrentNode = m_pCurrentNode->getNext();
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");
			}
			return *this;
		}
		const TList_const_iterator  operator++(int)
		{
			Node<T>* tempNode = m_pCurrentNode;
			if(m_pCurrentNode->getNext() != 0)
			{
				m_pCurrentNode = m_pCurrentNode->getNext();
			}
			else
			{
				throw std::out_of_range("Iterator out of range!");

			}
			return tempNode;
		}
		const T & operator*()
		{
			return m_pCurrentNode->getData();
		}

		bool operator!=(TList_const_iterator & _rhs)
		{
			return m_pCurrentNode != _rhs.node();
		}
		bool operator==(TList_const_iterator & _rhs)
		{
			return m_pCurrentNode == _rhs.node();
		}
	};

	//TList member functions definition
	template <class T>
	void TList<T>::push_back(const T& _data)
	{
		Node<T> *newNode = new Node<T>(_data);

		if(m_pHead != 0)
		{
			Node<T> *lastNode = m_pHead;
			while(lastNode->getNext() != m_pTail)
			{
				lastNode = lastNode->getNext();
			}

			newNode->setNext(m_pTail);
			lastNode->setNext(newNode);
		}
		else
		{
			m_pHead = newNode;
			m_pTail = new Node<T>;

			m_pHead->setNext(m_pTail);
		}
		++m_Length;
	}

	template <class T>
	void TList<T>::pop_back()
	{
		if(m_pHead != 0 && m_Length > 0)
		{
			Node<T>* currentNode = m_pHead;
			Node<T>* previousNode = m_pHead;
			while(currentNode->getNext() != m_pTail)
			{
				previousNode = currentNode;
				currentNode = currentNode->getNext();
			}

			if(currentNode == m_pHead)
			{
				//Delete last node and clear pointers
				m_pHead = 0;
				delete currentNode;
				currentNode = 0;

				delete m_pTail;
				m_pTail = 0;
				return;
			}
			delete currentNode;
			currentNode = 0;

			previousNode->setNext(m_pTail);
		}
	}

	template <class T>
	void TList<T>::clear()
	{
		if(m_Length > 0)
		{
			Node<T>* currentNode = m_pHead;

			while(currentNode->getNext() != 0)
			{
				Node<T>* tempNode = currentNode;
				currentNode = currentNode->getNext();
				delete tempNode;
			}
			if(currentNode == m_pTail)
			{
				delete currentNode;
				m_pTail = 0;
			}
			m_pHead = 0;
		}
	}

	template <class T>
	void TList<T>::erase(TList_iterator<T>& _pos)
	{
		if(_pos == begin())
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
		--m_Length;
	}

	template <class T>
	void TList<T>::insert(TList_iterator<T>& _after, const T& _data)
	{
		Node<T>* newNode = new Node<T>(_data, _after.node()->getNext());

		_after.node()->setNext(newNode);

		++m_Length;
	}

	//Non-effective
	template <class T>
	const T& TList<T>::dataOf(uint32 _i) const
	{
		if(m_Length > _i && m_pHead != 0)
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
		}
	}
	//**

	template <class T>
	const T& TList<T>::front() const
	{
		return m_pHead->getData();
	}

	template <class T>
	const T& TList<T>::back() const
	{
		Node<T>* currenNode = m_pHead;
		Node<T>* previousNode = m_pHead;
		while(currenNode->getNext() != m_pTail)
		{
			currenNode = currenNode->getNext();
			previousNode = currenNode;
		}
		return previousNode->getData();
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
		for(TList_iterator<T> it = begin(); it != end(); ++it)
		{
			if(*it == _key)
			{
				return it;
			}
		}
		return end();
	}
}