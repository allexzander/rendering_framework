#pragma once

#include <stdexcept>
#include <assert.h>
#include "..\commondefs.h"

namespace CORE_LIB
{
	//forward declarations
	template <class T> class TVectorArray;
	template <class T> class TVectorArray_iterator;

	//TVectorArray_const_iterator
	template <class T>
	class TVectorArray_const_iterator
	{
		//allow TVectorArray to create TVectorArray_const_iterator instances
		friend class TVectorArray<T>;
		friend class TVectorArray_iterator<T>;

	public:
		TVectorArray_const_iterator() : m_pBegin(nullptr),
			m_pEnd(nullptr), m_pCurrentElement(nullptr)
		{
		}

		TVectorArray_const_iterator(const TVectorArray_const_iterator& it) : TVectorArray_const_iterator(it.begin(), it.end())
		{
		}

	private:
		TVectorArray_const_iterator(T* _begin, T* _end) : m_pBegin(_begin),
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

		const TVectorArray_const_iterator& operator=(const TVectorArray_const_iterator& _rhs)
		{
			m_pCurrentElement = m_pBegin = _rhs.begin();
			m_pEnd = _rhs.end();
			return *this;
		}

		/*++prefix operator*/
		TVectorArray_const_iterator& operator++()
		{
			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVectorArray_const_iterator operator++()");

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
		TVectorArray_const_iterator operator++(int)
		{
			TVectorArray_const_iterator copySelf = *this;

			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVectorArray_const_iterator operator++(int)");

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

		TVectorArray_const_iterator& operator+=(int32 _value)
		{
			bool isValid = m_pCurrentElement && m_pBegin && m_pEnd;

			assert(isValid && "TVectorArray_const_iterator operator++(int)");

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

		TVectorArray_const_iterator operator+(int32 _value)
		{
			TVectorArray_const_iterator copy = *this;

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

		bool operator!=(const TVectorArray_const_iterator& _rhs) const
		{
			return !(*this == _rhs);
		}

		bool operator==(const TVectorArray_const_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && m_pCurrentElement == _rhs.current();
		}

		bool operator<(const TVectorArray_const_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && m_pCurrentElement < _rhs.current();
		}

		bool operator>(const TVectorArray_const_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && m_pCurrentElement > _rhs.current();
		}

		bool operator>=(const TVectorArray_const_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && (*this == _rhs || *this > _rhs);
		}

		bool operator<=(const TVectorArray_const_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && (*this == _rhs || *this < _rhs);
		}

		operator bool() const
		{
			return (m_pBegin != nullptr && m_pEnd != nullptr
				&& m_pCurrentElement != nullptr);
		}

	private:
		//pointing to same vector
		bool _areCompatible(const TVectorArray_const_iterator& _a, const TVectorArray_const_iterator& _b) const
		{
			return _a.begin() == _b.begin() && _a.end() == _b.end();
		}

	private:
		T* m_pBegin;
		T* m_pEnd;
		T* m_pCurrentElement;
	}; //TVectorArray_const_iterator

	//Vector_iterator
	template <class T>
	class TVector_iterator
	{
		//allow TVectorArray to create TVector_iterator instances
		friend class TVectorArray <T>;

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
			**Constructor can be invoked only inside TVectorArray
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

		bool operator!=(const TVector_iterator& _rhs) const
		{
			return !(*this == _rhs);
		}

		bool operator==(const TVector_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && m_pCurrentElement == _rhs.current();
		}

		bool operator<(const TVector_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && m_pCurrentElement < _rhs.current();
		}

		bool operator>(const TVector_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && m_pCurrentElement > _rhs.current();
		}

		bool operator>=(const TVector_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && (*this == _rhs || *this > _rhs);
		}

		bool operator<=(const TVector_iterator& _rhs) const
		{
			return _areCompatible(*this, _rhs) && (*this == _rhs || *this < _rhs);
		}

		operator bool() const
		{
			return (m_pBegin != nullptr && m_pEnd != nullptr
				&& m_pCurrentElement != nullptr);
		}

		operator TVectorArray_const_iterator<T>()
		{
			return TVectorArray_const_iterator<T>(m_pBegin, m_pEnd);
		}

	private:
		//pointing to same vector
		bool _areCompatible(const TVector_iterator<T>& _a, const TVector_iterator<T>& _b) const
		{
			return _a.begin() == _b.begin() && _a.end() == _b.end();
		}

	private:
		T* m_pBegin;
		T* m_pEnd;
		T* m_pCurrentElement;
	}; //Vector_iterator

	//TVectorArray declaration
	template <class T>
	class TVectorArray 
	{
	private:
		T* m_pElements;
		size_t m_Capacity;
		size_t m_Size;

	public:
		TVectorArray();
		TVectorArray(size_t _initialCapacity);
		TVectorArray(const TVectorArray<T>& _source);
		TVectorArray(const T* _pDataArray, size_t _numData);
		const TVectorArray & operator=(const TVectorArray & _rhs);
		~TVectorArray();

	public:
		void push_back(const T& _data);
		void pop_back();

		size_t size()	  const { return m_Size; }
		size_t capacity() const	{ return m_Capacity; }

		const T& front();
		const T& back();

		TVector_iterator<T>		  iterator()	  const;
		TVectorArray_const_iterator<T> constIterator() const;

		void reserve(size_t _newCap);

		T&		 operator[](int32 _index);
		const T& operator[](int32 _index) const;

		T&		 at(int32 _index);
		const T& at(int32 _index) const;

		/*
		**Erases element at given position, reducing size by 1, in case of incorrect _pos throws out_of_range
		@_pos = element position
		*/
		void erase(int32 _index)
		{
			TVector_iterator<T> it = TVector_iterator<T>(&m_pElements[0], (&m_pElements[m_Size]));
			it += _index;
			erase(it);
		}

		void erase(const TVector_iterator<T>& _pos);
		void clear();
		friend bool operator==(const TVectorArray& _lhs, const TVectorArray& _rhs)
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

		friend bool operator!=(const TVectorArray& _lhs, const TVectorArray& _rhs)
		{
			return !_lhs == _rhs;
		}
	}; //TVectorArray declaration

	//TVectorArray definition
	template <class T>
	TVectorArray<T>::TVectorArray()
	{
		m_pElements = nullptr;
		m_Capacity	= 0;
		m_Size		= 0;
	}

	template <class T>
	TVectorArray<T>::TVectorArray(size_t _initialCapacity) : TVectorArray()
	{
		if (_initialCapacity > 0)
		{
			m_Capacity = _initialCapacity;
			m_pElements = new T[m_Capacity];
		}
	}

	template <class T>
	TVectorArray<T>::TVectorArray(const TVectorArray<T>& _source) : TVectorArray(_source.capacity())
	{
		for (size_t i = 0; i < _source.size(); ++i)
		{
			push_back(_source[i]);
		}
	}

	template <class T>
	TVectorArray<T>::TVectorArray(const T* _pDataArray, size_t _numData) : TVectorArray()
	{
		for (size_t i = 0; i < _numData; ++i)
		{
			push_back(_pDataArray[i]);
		}
	}

	template <class T>
	const TVectorArray<T> & TVectorArray<T>::operator=(const TVectorArray<T> & _rhs)
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
	TVectorArray<T>::~TVectorArray()
	{
		clear();
	}

	template <class T>
	/*
		**Add new element to the end
	*/
	void TVectorArray<T>::push_back(const T& _data)
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
	void TVectorArray<T>::pop_back()
	{
		assert(m_Size > 0 && "Vector is empty!!!!");

		if (m_Size > 0)
		{
			--m_Size;
			m_pElements[m_Size].~T();
		}
	}

	template <class T>
	const T& TVectorArray<T>::front()
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
	const T& TVectorArray<T>::back()
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
	TVector_iterator<T> TVectorArray<T>::iterator() const
	{
		TVector_iterator<T> it;

		if (m_Size > 0)
		{
			it = TVector_iterator<T>(&m_pElements[0], (&m_pElements[m_Size]));
		}
		
		return it;
	}

	template <class T>
	TVectorArray_const_iterator<T> TVectorArray<T>::constIterator() const
	{
		TVectorArray_const_iterator<T> it;

		if (m_Size > 0)
		{
			it = TVectorArray_const_iterator<T>(&m_pElements[0], (&m_pElements[m_Size]));
		}

		return it;
	}

	template <class T>
	void TVectorArray<T>::reserve(size_t _newCap)
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
	T& TVectorArray<T>::operator[](int32 _index)
	{
		assert(_index >= 0 && (static_cast<size_t>(_index) < m_Size));
		return m_pElements[_index];
	}

	template <class T>
	const T& TVectorArray<T>::operator[](int32 _index) const
	{
		assert(_index >= 0 && (static_cast<size_t>(_index) < m_Size));
		return m_pElements[_index];
	}

	template <class T>
	/*
		**Returns element by index, in case of incorrect index throws out_of_range
		@_index = element location
	*/
	T& TVectorArray<T>::at(int32 _index)
	{
		if (!(_index >= 0 && (static_cast<size_t>(_index) < m_Size)))
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
	const T& TVectorArray<T>::at(int32 _index) const
	{
		if (!(_index >= 0 && (static_cast<size_t>(_index) < m_Size)))
		{
			throw std::out_of_range("Index out of range!");
		}

		return m_pElements[_index];
	}

	template <class T>
	/*
		**Erases element at given iterator position, reducing size by 1, in case of incorrect _pos throws out_of_range
		@_pos = element position
	*/
	void TVectorArray<T>::erase(const TVector_iterator<T>& _pos)
	{
		int a = 5;
		if (_pos >= iterator())
		{
			a = 6;
		}

		if (_pos && _pos >= iterator() && _pos.current() < iterator().end())
		{
			auto tempBuffer = new T[m_Capacity];
			size_t i = 0;
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
	void TVectorArray<T>::clear()
	{
		if (m_Capacity > 0 && m_pElements != nullptr)
		{
			delete[] m_pElements;
			m_pElements = nullptr;
			m_Capacity	= 0;
			m_Size		= 0;
		}
	}
}; //CORE_LIB