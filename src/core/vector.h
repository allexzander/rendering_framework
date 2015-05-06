#pragma once

#include <stdexcept>
#include <assert.h>

#include "commondefs.h"

namespace CORE_LIB
{
	//forward declarations
	template <class T> class TVector;

	template <class T>
	class TVector_iterator
	{
		//allow TVector to create TVector_iterator instances
		friend class TVector <T>;

	public:
		TVector_iterator() : m_pBegin(nullptr),
			m_pEnd(nullptr), m_pCurrentElement(nullptr)
		{
		}

		TVector_iterator(const TVector_iterator& it) : TVector_iterator()
		{
			m_pCurrentElement = m_pBegin = it.begin();
			m_pEnd = it.end();
		}

	private:
		TVector_iterator(T* _begin, T* _end) : m_pBegin(_begin),
			m_pEnd(_end), m_pCurrentElement(nullptr)
		{
			m_pCurrentElement = m_pBegin;
		}

	public:
		T* begin()	 const { return m_pBegin; }
		T* end()	 const { return m_pEnd;	  }
		T* current() const { return m_pCurrentElement; }

		void reset()
		{
			if (m_pBegin && m_pEnd)
			{
				m_pCurrentElement = m_pBegin;
			}
		}

		const TVector_iterator& operator=(const TVector_iterator& _rhs)
		{
			m_pCurrentElement = m_pBegin = _rhs.begin();
			m_pEnd = _rhs.end();
			return *this;
		}

		/*++prefix operator*/
		TVector_iterator& operator++()
		{
			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVector_iterator operator++()");

			if (isValid)
			{
				++m_pCurrentElement;
				if (m_pCurrentElement == m_pEnd)
				{
					m_pCurrentElement = nullptr;
				}
			}

			return *this;
		}

		/*postfix++ operator*/
		TVector_iterator operator++(int)
		{
			TVector_iterator copySelf = *this;

			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVector_iterator operator++(int)");

			if (isValid)
			{
				++m_pCurrentElement;
				if (m_pCurrentElement >= m_pEnd)
				{
					m_pCurrentElement = nullptr;
				}
			}

			return copySelf;
		}

		TVector_iterator& operator+=(int32 _value)
		{
			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVector_iterator operator++(int)");

			if (isValid)
			{
				m_pCurrentElement += _value;

				if (m_pCurrentElement >= m_pEnd)
				{
					m_pCurrentElement = nullptr;

				}
			}

			return *this;
		}

		TVector_iterator operator+(int32 _value)
		{
			TVector_iterator copy = *this;

			copy += value;

			return copy;
		}

		T& operator*()
		{
			return *m_pCurrentElement;
		}

		bool operator!=(const TVector_iterator& _rhs)
		{
			return !(*this == _rhs);
		}

		bool operator==(const TVector_iterator& _rhs)
		{
			return (m_pBegin == _rhs.begin() && m_pEnd == _rhs.end()
				&& m_pCurrentElement == _rhs.current());
		}

		bool operator<(const TVector_iterator& _rhs)
		{
			return (m_pBegin < _rhs.begin() && m_pEnd < _rhs.end()
				&& m_pCurrentElement < _rhs.current());
		}

		bool operator>(const TVector_iterator& _rhs)
		{
			return (m_pBegin < _rhs.begin() && m_pEnd < _rhs.end()
				&& m_pCurrentElement < _rhs.current());
		}

		bool operator>=(const TVector_iterator& _rhs)
		{
			return *this == _rhs || *this > _rhs;
		}

		bool operator<=(const TVector_iterator& _rhs)
		{
			return *this == _rhs || *this < _rhs;
		}

		operator bool()
		{
			return (m_pBegin != nullptr && m_pEnd != nullptr
				&& m_pCurrentElement != nullptr);
		}

	private:
		T* m_pBegin;
		T* m_pEnd;
		T* m_pCurrentElement;
	};

	template <class T>
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

		TVector_iterator<T> getIterator();

		void reserve(uint32 _newCap);

		T & operator[](uint32 _index);

		const T & operator[](uint32 _index) const;

		T & at(uint32 _index);

		void erase(uint32 _pos);
		void erase(TVector_iterator<T> _pos);
	};

	template <class T>
	TVector<T>::TVector()
	{
		m_pElements = NULL;
		m_Capacity = 0;
		m_Size = 0;
	}

	template <class T>
	TVector<T>::TVector(uint32 _initialSize)
	{
		m_pElements = new T[_initialSize];
		m_Capacity = _initialSize;
	}

	template <class T>
	TVector<T>::TVector(TVector<T>& _source)
	{
		m_pElements = new T[_source.capacity()];
		m_Capacity = _source.capacity();
		m_Size = 0;
		for (uint32 i = 0; i < _source.size(); ++i)
		{
			push_back(_source[i]);
		}
	}

	template <class T>
	TVector<T>::~TVector()
	{
		if (m_Capacity > 0)
		{
			delete[] m_pElements;
		}
	}

	template <class T>
	TVector<T> & TVector<T>::operator=(TVector<T> & _rhs)
	{
		if (m_Capacity > 0)
		{
			delete[] m_pElements;
		}

		m_pElements = new T[_rhs.capacity()];

		for (uint32 i = 0; i < _rhs.size(); ++i)
		{
			push_back(_rhs[i]);
		}
		return *this;
	}

	template <class T>
	void TVector<T>::push_back(const T& _data)
	{
		if (m_Capacity < 1)
		{
			m_pElements = new T[1];
			m_Capacity = 1;
			m_pElements[0] = _data;
			m_Size = 1;
		}
		else
		{
			if (m_Size == m_Capacity)
			{
				T* tempElements = new T[m_Size + 1];
				uint32 i = 0;
				for (; i < m_Size; ++i)
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

	template <class T>
	void TVector<T>::pop_back()
	{
		T* tempElements = new T[m_Size - 1];

		for (int i = 0; i < m_Size - 1; ++i)
		{
			tempElements[i] = m_pElements[i];
		}

		delete[] m_pElements;

		m_pElements = tempElements;

		--m_Size;
	}

	template <class T>
	const T& TVector<T>::front()
	{
		if (m_Size > 0)
		{
			return m_pElements[0];
		}
		else
		{
			throw std::out_of_range("Out of range!");
		}
	}

	template <class T>
	const T& TVector<T>::back()
	{
		if (m_Size > 0)
		{
			return m_pElements[m_Size - 1];
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}
	}

	template <class T>
	TVector_iterator<T> TVector<T>::getIterator()
	{
		TVector_iterator<T> it;

		if (m_Size > 0)
		{
			it = TVector_iterator<T>(&m_pElements[0], (&m_pElements[m_Size]));
		}
		
		return it;
	}

	template <class T>
	void TVector<T>::reserve(uint32 _newCap)
	{
		if (m_Capacity < 1)
		{
			m_pElements = new T[_newCap];
			m_Capacity = _newCap;
		}
		else
		{
			if (_newCap > m_Capacity)
			{
				T* tempElements = new T[_newCap];
				for (uint32 i = 0; i < m_Size; ++i)
				{
					tempElements[i] = m_pElements[i];
				}
				delete[] m_pElements;

				m_pElements = tempElements;

				m_Capacity = _newCap;
			}
		}
	}

	template <class T>
	T & TVector<T>::operator[](uint32 _index)
	{
		return m_pElements[_index];
	}

	template <class T>
	const T & TVector<T>::operator[](uint32 _index) const
	{
		return m_pElements[_index];
	}

	template <class T>
	T & TVector<T>::at(uint32 _index)
	{
		if (_index > (m_Size - 1))
		{
			throw std::out_of_range("Index out of range!");
		}

		return m_pElements[_index];
	}

	template <class T>
	void TVector<T>::erase(uint32 _pos)
	{
		if (m_Size > 0 && _pos < m_Size)
		{
			T* tempElements = new T[m_Size - 1];
			uint32 i = 0;
			uint32 j = 0;
			while (j < m_Size)
			{
				if (j != _pos)
				{
					tempElements[i++] = m_pElements[j++];
				}
				else
				{
					++j;
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

	template <class T>
	void TVector<T>::erase(TVector_iterator<T> _pos)
	{
		if (_pos >= begin() && _pos < end())
		{
			T* tempElements = new T[m_Size - 1];
			int i = 0;
			for (TVector_iterator<T> it = begin(); it != end(); ++it)
			{
				if (it != _pos)
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