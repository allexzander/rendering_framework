#pragma once

#include <stdexcept>
#include <assert.h>
#include "commondefs.h"

namespace CORE_LIB
{
	//TStack class declaration
	template <class T>
	class TStack
	{
	public:
		TStack() : m_pElements(nullptr), m_Size(0),
			m_Capacity(0), m_StackPointer(-1)
		{
		}

		TStack(int32 _cap) : TStack()
		{
			if (_cap > 0)
			{
				m_pElements = new T[_cap];
				m_Capacity	= static_cast<size_t>(_cap);
			}
		}

		~TStack()
		{
			_clear();
		}

		TStack(const TStack& _other) : TStack()
		{
			*this = _other;
		}

		TStack& operator=(const TStack& _other)
		{
			_clear();

			if (_other.size() > 0)
			{
				for (size_t i = 0; i < _other.size(); ++i)
				{
					push(_other.at(i));
				}
			}

			return *this;
		}

	public:
		void push(const T& _element);
		T	 pop();

		T& at(int32 _index) const;

		size_t size() const
		{
			return m_Size;
		}

	private:
		void _clear()
		{
			if (m_Capacity && m_pElements)
			{
				delete m_pElements;
				m_pElements = nullptr;
				m_Capacity = m_Size = 0;
				m_StackPointer = -1;
			}
		}

	private:
		T*	   m_pElements;
		size_t m_Size;
		size_t m_Capacity;
		int32  m_StackPointer;
	};
	//TStack class declaration


	//*********************************
	//TStack class methods definition
	//*********************************
	template <class T>
	/*
	**Add element into stack's tail, expanding memory, if required
	*/
	void TStack<T>::push(const T& _element)
	{
		if (m_pElements == nullptr)
		{
			m_Capacity = 2;
			m_pElements = new T[m_Capacity];
		}

		if (m_Capacity <= m_Size)
		{
			auto pTempElements = new T[m_Size + 2];

			for (size_t i = 0; i < m_Size; ++i)
			{
				pTempElements[i] = m_pElements[i];
			}

			delete m_pElements;
			m_pElements = pTempElements;
			m_Capacity = m_Size + 2;
		}

		m_pElements[++m_StackPointer] = _element;

		++m_Size;
	}

	template <class T>
	/*
	**Remove element from stack, returning it
	*/
	T TStack<T>::pop()
	{
		if (m_Size > 0)
		{
			--m_Size;
			return m_pElements[m_StackPointer--];
		}
		else
		{
			throw::std::out_of_range("Stack is empty!");
			return m_pElements[m_StackPointer];
		}
	}

	template <class T>
	/*
	**Return element at given index, thows std::out_of_range exception
	*/
	T& TStack<T>::at(int32 _index) const
	{
		if (_index >= 0 && static_cast<size_t>(_index) < m_Size)
		{
			return m_pElements[_index];
		}
		else
		{
			throw std::out_of_range("Stack index out of range!");
			return m_pElements[_index];
		}
	}

}; //CORE_LIB