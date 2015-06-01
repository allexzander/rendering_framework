#pragma once

#include <stdexcept>
#include <assert.h>
#include "commondefs.h"

namespace CORE_LIB
{
	//forward declarations
	template <class T> class TVector;
	template <class T> class TVector_terator;

	//TVector_const_iterator
	template <class T>
	class TVector_const_iterator
	{
		//allow TVector to create TVector_const_iterator instances
		friend class TVector<T>;
		friend class TVector_terator<T>;

	public:
		TVector_const_iterator() : m_pBegin(nullptr),
			m_pEnd(nullptr), m_pCurrentElement(nullptr)
		{
		}

		TVector_const_iterator(const TVector_const_iterator& it) : TVector_const_iterator(it.begin(), it.end())
		{
		}

	private:
		TVector_const_iterator(T* _begin, T* _end) : m_pBegin(_begin),
			m_pEnd(_end), m_pCurrentElement(_begin)
		{
		}

	public:
		T* begin()	 const { return m_pBegin; }
		T* end()	 const { return m_pEnd; }
		T* current() const { return m_pCurrentElement; }

		void reset()
		{
			if (m_pBegin && m_pEnd)
			{
				m_pCurrentElement = m_pBegin;
			}
		}

		const TVector_const_iterator& operator=(const TVector_const_iterator& _rhs)
		{
			m_pCurrentElement = m_pBegin = _rhs.begin();
			m_pEnd = _rhs.end();
			return *this;
		}

		/*++prefix operator*/
		TVector_const_iterator& operator++()
		{
			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVector_const_iterator operator++()");

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
		TVector_const_iterator operator++(int)
		{
			TVector_const_iterator copySelf = *this;

			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVector_const_iterator operator++(int)");

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

		TVector_const_iterator& operator+=(int32 _value)
		{
			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVector_const_iterator operator++(int)");

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

		TVector_const_iterator operator+(int32 _value)
		{
			TVector_const_iterator copy = *this;

			copy += value;

			return copy;
		}

		const T& operator*()
		{
			return *m_pCurrentElement;
		}

		const T& operator->()
		{
			return *m_pCurrentElement;
		}

		bool operator!=(const TVector_const_iterator& _rhs)
		{
			return !(*this == _rhs);
		}

		bool operator==(const TVector_const_iterator& _rhs)
		{
			return (m_pBegin == _rhs.begin() && m_pEnd == _rhs.end()
				&& m_pCurrentElement == _rhs.current());
		}

		bool operator<(const TVector_const_iterator& _rhs)
		{
			return (m_pBegin < _rhs.begin() && m_pEnd < _rhs.end()
				&& m_pCurrentElement < _rhs.current());
		}

		bool operator>(const TVector_const_iterator& _rhs)
		{
			return (m_pBegin < _rhs.begin() && m_pEnd < _rhs.end()
				&& m_pCurrentElement < _rhs.current());
		}

		bool operator>=(const TVector_const_iterator& _rhs)
		{
			return *this == _rhs || *this > _rhs;
		}

		bool operator<=(const TVector_const_iterator& _rhs)
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
	}; //TVector_const_iterator

	//Vector_iterator
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

		TVector_iterator(const TVector_iterator& it) : TVector_iterator(it.begin(), it.end())
		{
		}

	private:
		/*
			**Constructor can be invoked only inside TVector
		*/
		TVector_iterator(T* _begin, T* _end) : m_pBegin(_begin),
			m_pEnd(_end), m_pCurrentElement(_begin)
		{
		}

		T* begin()	 const { return m_pBegin; }
		T* end()	 const { return m_pEnd;	  }

	public:
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

		/*++operator*/
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

		/*operator++*/
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

		T& operator->()
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

		operator TVector_const_iterator()
		{
			return TVector_const_iterator(m_pBegin, m_pEnd);
		}

	private:
		T* m_pBegin;
		T* m_pEnd;
		T* m_pCurrentElement;
	}; //Vector_iterator

	//TVector declaration
	template <class T>
	class TVector 
	{
	private:
		T* m_pElements;
		size_t m_Capacity;
		size_t m_Size;

	public:
		TVector();
		TVector(size_t _initialCapacity);
		TVector(const TVector<T>& _source);
		TVector(const T* _pDataArray, size_t _numData);
		const TVector & operator=(const TVector & _rhs);
		~TVector();

	public:
		void push_back(const T& _data);
		void pop_back();

		size_t size()	  const { return m_Size; }
		size_t capacity() const	{ return m_Capacity; }

		const T& front();
		const T& back();

		TVector_iterator<T>		  iterator()	  const;
		TVector_const_iterator<T> constIterator() const;

		void reserve(size_t _newCap);

		T&		 operator[](uint32 _index);
		const T& operator[](uint32 _index) const;

		T&		 at(uint32 _index);
		const T& at(uint32 _index) const;

		void erase(uint32 _pos);
		void erase(const TVector_iterator<T>& _pos);
		void clear();
		friend bool operator==(const TVector& _lhs, const TVector& _rhs)
		{
			if (_lhs.m_Size != _rhs.m_Size)
			{
				return false;
			}

			for (size_t i = 0; i < _lhs.size(); ++i)
			{
				if (_lhs[i] != _rhs[i])
				{
					return false;
				}
			}

			return true;
		}

		friend bool operator!=(const TVector& _lhs, const TVector& _rhs)
		{
			return !_lhs == _rhs;
		}
		//CORE_LIB::String glue(CORE_LIB::String& _delimiter);

	}; //TVector declaration

	//TVector definition
	template <class T>
	TVector<T>::TVector()
	{
		m_pElements = nullptr;
		m_Capacity	= 0;
		m_Size		= 0;
	}

	template <class T>
	TVector<T>::TVector(size_t _initialCapacity) : TVector()
	{
		if (_initialCapacity > 0)
		{
			m_Capacity = _initialCapacity;
			m_pElements = new T[m_Capacity];
		}
	}

	template <class T>
	TVector<T>::TVector(const TVector<T>& _source) : TVector(_source.capacity())
	{
		for (size_t i = 0; i < _source.size(); ++i)
		{
			push_back(_source[i]);
		}
	}

	template <class T>
	TVector<T>::TVector(const T* _pDataArray, size_t _numData) : TVector()
	{
		for (size_t i = 0; i < _numData; ++i)
		{
			push_back(_pDataArray[i]);
		}
	}

	template <class T>
	const TVector<T> & TVector<T>::operator=(const TVector<T> & _rhs)
	{
		clear();

		m_Capacity	= _rhs.capacity();
		m_pElements = new T[m_Capacity];

		for (size_t i = 0; i < _rhs.size(); ++i)
		{
			push_back(_rhs[i]);
		}

		return *this;
	}

	template <class T>
	TVector<T>::~TVector()
	{
		clear();
	}

	template <class T>
	/*
		**Add new element to the end
	*/
	void TVector<T>::push_back(const T& _data)
	{
		if (m_Capacity == 0)
		{
			//Very first element is being pushed
			m_Capacity	   = 2;
			m_pElements	   = new T[m_Capacity];
			m_pElements[0] = _data;
			m_Size		   = 1;

			return;
		}

		if (m_Size != 0 && m_Size == m_Capacity)
		{
			//Reserve 1 place for current T _data, and 1 more for future push
			m_Capacity += 2;

			auto newBuffer = new T[m_Capacity];

			//Copy m_pElements to new buffer
			size_t i = 0;
			for (; i < m_Size; ++i)
			{
				newBuffer[i] = m_pElements[i];
			}

			//add new element to the end
			newBuffer[i] = _data;

			//replace m_pElements with new buffer
			delete[] m_pElements;
			m_pElements = newBuffer;
			++m_Size;

			return;
		}

		m_pElements[m_Size] = _data;
		++m_Size;

		return;
	}

	template <class T>
	void TVector<T>::pop_back()
	{
		assert(m_Size > 0 && "Vector is empty!!!!");

		if (m_Size > 0)
		{
			--m_Size;
			m_pElements[m_Size].~T();
		}
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
	TVector_iterator<T> TVector<T>::iterator() const
	{
		TVector_iterator<T> it;

		if (m_Size > 0)
		{
			it = TVector_iterator<T>(&m_pElements[0], (&m_pElements[m_Size]));
		}
		
		return it;
	}

	template <class T>
	TVector_const_iterator<T> TVector<T>::constIterator() const
	{
		TVector_const_iterator<T> it;

		if (m_Size > 0)
		{
			it = TVector_const_iterator<T>(&m_pElements[0], (&m_pElements[m_Size]));
		}

		return it;
	}

	template <class T>
	void TVector<T>::reserve(size_t _newCap)
	{
		if (_newCap > 0 && _newCap <= m_Size)
		{
			if (m_Size > 0)
			{
				//Copy elements to tempBuffer
				m_Capacity	  = _newCap;
				T* tempBuffer = new T[m_Capacity];
				for (size_t i = 0; i < m_Size; ++i)
				{
					tempBuffer[i] = m_pElements[i];
				}
				delete[] m_pElements;
				m_pElements = tempBuffer;
			}
		}
	}

	template <class T>
	T& TVector<T>::operator[](uint32 _index)
	{
		return m_pElements[_index];
	}

	template <class T>
	const T& TVector<T>::operator[](uint32 _index) const
	{
		return m_pElements[_index];
	}

	template <class T>
	/*
		**Returns element by index, in case of incorrect index throws out_of_range
		@_index = element location
	*/
	T& TVector<T>::at(uint32 _index)
	{
		if (_index > (m_Size - 1))
		{
			throw std::out_of_range("Index out of range!");
		}

		return m_pElements[_index];
	}

	template <class T>
	/*
		**Returns const reference to an element by index, in case of incorrect index throws out_of_range
		@_index = element location
	*/
	const T& TVector<T>::at(uint32 _index) const
	{
		if (_index > (m_Size - 1))
		{
			throw std::out_of_range("Index out of range!");
		}

		return m_pElements[_index];
	}

	template <class T>
	/*
		**Erases element at given position, reducing size by 1, in case of incorrect _pos throws out_of_range
		@_pos = element position
	*/
	void TVector<T>::erase(uint32 _pos)
	{
		if (m_Size > 0 && _pos < m_Size)
		{
			auto tempBuffer = new T[m_Capacity];
			uint32 i = 0;
			uint32 j = 0;
			while (j < m_Size)
			{
				if (j != _pos)
				{
					tempBuffer[i++] = m_pElements[j];
				}
				++j;
			}
			delete[] m_pElements;
			m_pElements = tempBuffer;

			--m_Size;
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}
	}

	template <class T>
	/*
		**Erases element at given iterator position, reducing size by 1, in case of incorrect _pos throws out_of_range
		@_pos = element position
	*/
	void TVector<T>::erase(const TVector_iterator<T>& _pos)
	{
		if (_pos >= begin() && _pos < end())
		{
			auto tempBuffer = new T[m_Capacity];
			int32 i = 0;
			for (TVector_iterator<T> it = iterator(); it; ++it)
			{
				if (it != _pos)
				{
					tempBuffer[i++] = *it;
				}
			}
			delete[] m_pElements;
			m_pElements = tempBuffer;
			--m_Size;
		}
		else
		{
			throw std::out_of_range("Index out of range!");
		}
	}

	template <class T>
	void TVector<T>::clear()
	{
		if (m_Capacity > 0 && m_pElements != nullptr)
		{
			delete[] m_pElements;
			m_pElements = nullptr;
			m_Capacity	= 0;
			m_Size		= 0;
		}
	}

	/*template <class T>
	/*
		**Returns CORE_LIB::String of T elements, delimited with specified character
		@_delimiter = delimiting character
	
	CORE_LIB::String TVector<T>::glue(CORE_LIB::String& _delimiter)
	{
		CORE_LIB::String result = _T("");

		if (m_Size > 0)
		{
			for (size_t i = 0; i < m_Size; ++i)
			{
				result += m_pElements[i];

				if (i < m_Size - 1)
				{
					result += _delimiter;
				}
			}
		}

		return result;
	}*/

	//TVector definition

}; //CORE_LIB