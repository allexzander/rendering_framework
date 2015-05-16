#pragma once

#if _WIN32
//for TCHAR
#include <tchar.h>
#else
typedef char TCHAR;
#endif
#include "commondefs.h"

namespace CORE_LIB
{
	class String
	{
	public:
		String() : m_pBuffer(nullptr), m_Length(0)
		{}

		String(const TCHAR* _string);

		String(const String& _copy);

		const String& operator=(const String& _copy);

		const String& operator=(const TCHAR* _string);

		~String();

	public:
		const TCHAR* toConstChar() const;
		/*
			**Return single character
			@_at = character position
		*/
		TCHAR charAt(uint32 _at) const;
		size_t legth() const { return m_Length; }
		/* 
		**Remove characters in range specified
			@_count = number of characters, to remove
			@_at	   = position of the first character
		*/
		const String& erase(uint32 _at, uint32 _count = 1);
		/*
			**Remove spaces from the beginning of the string
		*/
		String trim();

		void clear();

		bool startsWith(const String& _pattern) const;

		bool endsWith(const String& _pattern) const;

		operator const TCHAR*() const;

		const TCHAR operator[](uint32 _at) const
		{
			return m_pBuffer[_at];
		}
		operator double() const;

		operator int() const;

		friend bool operator==(const String& _lhs, const String& _rhs)
		{
			return isEqual(_lhs, _rhs);
		}

		friend bool operator==(const String& _lhs, const TCHAR* _string)
		{
			return _lhs == String(_string);
		}

		friend bool operator==(const TCHAR* _string, const String& _rhs)
		{
			return _rhs == String(_string);
		}

		friend bool operator<(const String& _lhs, const String& _rhs)
		{
			return isLesser(_lhs, _rhs);
		}

		friend bool operator<(const String& _lhs, const TCHAR* _string)
		{
			return _lhs < String(_string);
		}

		friend bool operator<(const TCHAR* _string, const String& _rhs)
		{
			return String(_string) < _rhs;
		}

		friend bool operator>(const String& _lhs, const String& _rhs)
		{
			return (!(_lhs < _rhs) && !(_lhs == _rhs));
		}

		friend bool operator>(const String& _lhs, const TCHAR* _string)
		{
			return _lhs > String(_string);
		}

		friend bool operator>(const TCHAR* _string, const String& _rhs)
		{
			return String(_string) > _rhs;
		}

		friend String operator+(const String& _lhs, const String& _rhs);

		friend String operator+(const TCHAR* _string, const String& _rhs)
		{
			return String(_string) + _rhs;
		}

		friend String operator+(const String& _lhs, const TCHAR* _string)
		{
			return _lhs + String(_string);
		}

		friend String operator+(const String& _lhs, const TCHAR _c)
		{
			TCHAR* string = new TCHAR[2];
			string[0] = _c;
			string[1] = '\0';
			String rhs = string;
			delete[] string;
			return (_lhs + rhs);
		}

		friend String operator+(const TCHAR _c, const String& _rhs)
		{
			TCHAR* string = new TCHAR[2];
			string[0] = _c;
			string[1] = '\0';
			String lhs = string;
			delete[] string;
			return (lhs + _rhs);
		}

		String operator+=(const String& _rhs)
		{
			*this = *this + _rhs;
			return *this;
		}

	public:
		/*
			**Returns true, if @_ch is equal to int in range [0..9]
		*/
		static bool   isCharADigit(const TCHAR _ch);

		static double toDouble(const String& _string);

		static int	  toInt(const String& _string);
		/*
			**Returns true, if strings are equal
		*/
		static bool	  isEqual(const String& _string1, const String& _string2);

		/*
		**Returns true, if @_string1 < @_string2
		*/
		static bool	  isLesser(const String& _string1, const String& _string2);

	private:
		TCHAR* m_pBuffer;
		size_t m_Length;
	}; //class String
}; //CORE_LIB