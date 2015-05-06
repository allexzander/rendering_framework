#pragma once

#ifdef __linux__
#include <stdexcept>
#endif //__linux__

#include "commondefs.h"

namespace CORE_LIB
{
	template <typename T> class TVector;

	template <typename T>
	class TVector_iterator
	{
	private:
		T* m_pCurrentElement;
	public:
		TVector_iterator(T* _element)
		{
			m_pCurrentElement = _element;
		}
	public:
		T* currentElement() { return m_pCurrentElement; }
		TVector_iterator & operator=(TVector_iterator & _rhs)
		{
			m_pCurrentElement = _rhs.currentElement();
			return *this;
		}

		TVector_iterator  operator++()
		{
			++m_pCurrentElement;
			return *this;
		}
		TVector_iterator  operator++(int)
		{
			++m_pCurrentElement;
			return *this;
		}

		TVector_iterator  operator--()
		{
			--m_pCurrentElement;
			return *this;
		}
		TVector_iterator  operator--(int)
		{
			--m_pCurrentElement;
			return *this;
		}

		TVector_iterator  operator+=(int _value)
		{
			m_pCurrentElement += _value;
			return *this;
		}

		TVector_iterator  operator-=(int _value)
		{
			m_pCurrentElement -= _value;
			return *this;
		}

		TVector_iterator  operator-(int _value)
		{
			return TVector_iterator(m_pCurrentElement - _value);
		}

		T & operator*()
		{
			return *m_pCurrentElement;
		}

		bool operator!=(TVector_iterator & _rhs)
		{
			return m_pCurrentElement != _rhs.currentElement();
		}
		bool operator==(TVector_iterator & _rhs)
		{
			return m_pCurrentElement == _rhs.currentElement();
		}
		bool operator<(TVector_iterator & _rhs)
		{
			return m_pCurrentElement < _rhs.currentElement();
		}
		bool operator>(TVector_iterator & _rhs)
		{
			return m_pCurrentElement > _rhs.currentElement();
		}
		bool operator>=(TVector_iterator & _rhs)
		{
			return m_pCurrentElement > _rhs.currentElement() || m_pCurrentElement == _rhs.currentElement();
		}
		bool operator<=(TVector_iterator & _rhs)
		{
			return m_pCurrentElement < _rhs.currentElement() || m_pCurrentElement == _rhs.currentElement();
		}
		friend class TVector<T>;
	};
	//Const Iterator
	template <typename T>
	class TVector_const_iterator
	{
	private:
		T* m_pCurrentElement;
	public:
		TVector_const_iterator(T* _element)
		{
			m_pCurrentElement = _element;
		}
	public:
		T* currentElement() { return m_pCurrentElement; }
		TVector_const_iterator & operator=(TVector_const_iterator & _rhs)
		{
			m_pCurrentElement = _rhs.currentElement();
			return *this;
		}

		TVector_const_iterator  operator++()
		{
			++m_pCurrentElement;
			return *this;
		}
		TVector_const_iterator  operator++(int)
		{
			++m_pCurrentElement;
			return *this;
		}

		TVector_const_iterator  operator--()
		{
			--m_pCurrentElement;
			return *this;
		}
		TVector_const_iterator  operator--(int)
		{
			--m_pCurrentElement;
			return *this;
		}

		TVector_const_iterator  operator+=(int _value)
		{
			m_pCurrentElement += _value;
			return *this;
		}

		TVector_const_iterator  operator-=(int _value)
		{
			m_pCurrentElement -= _value;
			return *this;
		}

		TVector_const_iterator  operator-(int _value)
		{
			return TVector_iterator<T>(m_pCurrentElement - _value);
		}

		const T & operator*()
		{
			return *m_pCurrentElement;
		}

		bool operator!=(TVector_const_iterator & _rhs)
		{
			return m_pCurrentElement != _rhs.currentElement();
		}
		bool operator==(TVector_const_iterator & _rhs)
		{
			return m_pCurrentElement == _rhs.currentElement();
		}
		bool operator<(TVector_const_iterator & _rhs)
		{
			return m_pCurrentElement < _rhs.currentElement();
		}
		bool operator>(TVector_const_iterator & _rhs)
		{
			return m_pCurrentElement > _rhs.currentElement();
		}
		bool operator>=(TVector_const_iterator & _rhs)
		{
			return m_pCurrentElement > _rhs.currentElement() || m_pCurrentElement == _rhs.currentElement();
		}
		bool operator<=(TVector_const_iterator & _rhs)
		{
			return m_pCurrentElement < _rhs.currentElement() || m_pCurrentElement == _rhs.currentElement();
		}
		friend class TVector<T>;
	};

	template <typename T>
	class TVector {
	private:
		T* m_pElements;

		uint32 m_Capacity;
		uint32 m_Size;
	public:
		TVector();
		TVector(uint32 _initialSize);
		TVector(TVector<T>& _source);
		TVector & operator=(TVector & _rhs);
		~TVector();
	public:
		void push_back(const T& _data);
		void pop_back();

		uint32 size() { return m_Size; }

		uint32 capacity() { return m_Capacity; }

		const T& front();
		const T& back();

		TVector_iterator<T> begin();
		TVector_iterator<T> end();

		TVector_const_iterator<T> begin() const;
		TVector_const_iterator<T> end() const;

		TVector_iterator<T> rbegin();
		TVector_iterator<T> rend();

		TVector_const_iterator<T> rbegin() const;
		TVector_const_iterator<T> rend() const;

		void reserve(uint32 _newCap);

		T & operator[](uint32 _index);

		const T & operator[](uint32 _index) const;

		T & at(uint32 _index);

		void erase(uint32 _pos);
		void erase(TVector_iterator<T> _pos);
	};

	template <typename T>
	TVector<T>::TVector()
	{
		m_pElements = NULL;
		m_Capacity = 0;
		m_Size = 0;
	}

	template <typename T>
	TVector<T>::TVector(uint32 _initialSize)
	{
		m_pElements = new T[_initialSize];
		m_Capacity = _initialSize;
	}

	template <typename T>
	TVector<T>::TVector(TVector<T>& _source)
	{
		m_pElements = new T[_source.capacity()];
		m_Capacity = _source.capacity();
		m_Size = 0;
		for(uint32 i = 0; i < _source.size(); ++i)
		{
			push_back(_source[i]);
		}
	}

	template <typename T>
	TVector<T>::~TVector()
	{
		if(m_Capacity > 0)
		{
			delete[] m_pElements;
		}
	}

	template <typename T>
	TVector<T> & TVector<T>::operator=(TVector<T> & _rhs)
	{
		if(m_Capacity > 0)
		{
			delete[] m_pElements;
		}

		m_pElements = new T[_rhs.capacity()];

		for(uint32 i = 0; i < _rhs.size(); ++i)
		{
			push_back(_rhs[i]);
		}
		return *this;
	}

	template <typename T>
	void TVector<T>::push_back(const T& _data)
	{
		if(m_Capacity < 1)
		{
			m_pElements = new T[1];
			m_Capacity = 1;
			m_pElements[0] = _data;
			m_Size = 1;
		}
		else
		{
			if(m_Size == m_Capacity)
			{
				T* tempElements = new T[m_Size+1];
				uint32 i = 0;
				for(; i < m_Size; ++i)
				{
					tempElements[i] = m_pElements[i];
				}
				delete[] m_pElements;
				tempElements[i] = _data;
				m_pElements = tempElements;
				++m_Capacity;
			}
			else
			{
				m_pElements[m_Size] = _data;
			}
			++m_Size;
		}
	}

	template <typename T>
	void TVector<T>::pop_back()
	{
		T* tempElements = new T[m_Size-1];

		for(int i = 0; i < m_Size-1; ++i)
		{
			tempElements[i] = m_pElements[i];
		}

		delete[] m_pElements;

		m_pElements = tempElements;

		--m_Size;
	}

	template <typename T>
	const T& TVector<T>::front()
	{
		if(m_Size > 0)
		{
			return m_pElements[0];
		}
		else
		{
			throw std::out_of_range("Out of range!");
		}
	}

	template <typename T>
	const T& TVector<T>::back()
	{
		if(m_Size > 0)
		{
			return m_pElements[m_Size-1];
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}
	}

	template <typename T>
	TVector_iterator<T> TVector<T>::begin()
	{
		TVector_iterator<T> it(&m_pElements[0]);
		return it;
	}

	template <typename T>
	TVector_iterator<T> TVector<T>::end()
	{
		TVector_iterator<T> it(&m_pElements[m_Size]);
		if(m_Size < 1)
		{
			it = TVector_iterator<T>(begin());
		}
		return it;
	}

	template <typename T>
	TVector_iterator<T> TVector<T>::rbegin()
	{
		TVector_iterator<T> it(&m_pElements[m_Size-1]);
		if(m_Size < 1)
		{
			it = TVector_iterator<T>(begin());
		}
		return it;
	}

	template <typename T>
	TVector_iterator<T> TVector<T>::rend()
	{
		TVector_iterator<T> it(begin()-1);
		return it;
	}

	template <typename T>
	TVector_const_iterator<T> TVector<T>::begin() const
	{
		TVector_const_iterator<T> it(&m_pElements[0]);
		return it;
	}

	template <typename T>
	TVector_const_iterator<T> TVector<T>::end() const
	{
		TVector_const_iterator<T> it(&m_pElements[m_Size]);
		if(m_Size < 1)
		{
			it = TVector_const_iterator<T>(begin());
		}
		return it;
	}

	template <typename T>
	TVector_const_iterator<T> TVector<T>::rbegin() const
	{
		TVector_const_iterator<T> it(&m_pElements[m_Size-1]);
		if(m_Size < 1)
		{
			it = TVector_const_iterator<T>(begin());
		}
		return it;
	}

	template <typename T>
	TVector_const_iterator<T> TVector<T>::rend() const
	{
		TVector_const_iterator<T> it(begin()-1);
		return it;
	}

	template <typename T>
	void TVector<T>::reserve(uint32 _newCap)
	{
		if(m_Capacity < 1)
		{
			m_pElements = new T[_newCap];
			m_Capacity = _newCap;
		}
		else
		{
			if(_newCap > m_Capacity)
			{
				T* tempElements = new T[_newCap];
				for(uint32 i = 0; i < m_Size; ++i)
				{
					tempElements[i] = m_pElements[i];
				}
				delete[] m_pElements;

				m_pElements = tempElements;

				m_Capacity = _newCap;
			}
		}
	}

	template <typename T>
	T & TVector<T>::operator[](uint32 _index)
	{
		return m_pElements[_index];
	}

	template <typename T>
	const T & TVector<T>::operator[](uint32 _index) const
	{
		return m_pElements[_index];
	}

	template <typename T>
	T & TVector<T>::at(uint32 _index)
	{
		if(_index > (m_Size - 1))
		{
			throw std::out_of_range("Index out of range!");
		}

		return m_pElements[_index];
	}

	template <typename T>
	void TVector<T>::erase(uint32 _pos)
	{
		if(m_Size > 0 && _pos < m_Size)
		{
			T* tempElements = new T[m_Size - 1];
			uint32 i = 0;
			uint32 j = 0;
			while(j < m_Size)
			{
				if(j != _pos)
				{
					tempElements[i++] = m_pElements[j++];
				}
				else
				{
					++j;
				}
			}
			delete [] m_pElements;
			m_pElements = tempElements;

			--m_Size;
			--m_Capacity;
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}
	}

	template <typename T>
	void TVector<T>::erase(TVector_iterator<T> _pos)
	{
		if(_pos >= begin() && _pos < end())
		{
			T* tempElements = new T[m_Size - 1];
			int i = 0;
			for(TVector_iterator<T> it = begin(); it != end(); ++it)
			{
				if(it != _pos)
				{
					tempElements[i++] = *it;
				}
			}
			delete[] m_pElements;
			m_pElements = tempElements;
			--m_Size;
			--m_Capacity;
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}
	}
} //CORE_LIB