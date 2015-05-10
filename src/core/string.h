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
		String() :m_Buffer(nullptr), m_Length(0)
		{}
		String(const TCHAR* string);
		String(const String& copy);
		const String& operator=(const String& copy);
		const String& operator=(const TCHAR* string);
		~String();

	public:
		const TCHAR* toConstChar() const;
		TCHAR charAt(uint32 at) const;
		size_t legth() const { return m_Length; }
		const String& erase(uint32 at, uint32 count = 1);
		String trim();
		void clear();
		operator const TCHAR*() const;
		const TCHAR operator[](uint32 at) const
		{
			return m_Buffer[at];
		}
		operator double() const;
		operator int() const;

		friend bool operator==(const String& lhs, const TCHAR* string)
		{
			String rhs = String(string);
			return lhs == rhs;
		}

		friend bool operator==(const String& lhs, const String& rhs)
		{
			return isEqual(lhs, rhs);
		}

		friend bool operator==(const TCHAR* string, const String& rhs)
		{
			return String::isEqual(String(string), rhs);
		}

		friend bool operator<(const String& lhs, const String& rhs)
		{
			return String::isLesser(lhs, rhs);
		}

		friend bool operator<(const TCHAR* string, const String& rhs)
		{
			String lhs = string;
			return lhs < rhs;
		}

		friend bool operator<(const String& lhs, const TCHAR* string)
		{
			String rhs = string;
			return lhs < rhs;
		}

		friend bool operator>(const String& lhs, const String& rhs)
		{
			return !(lhs < rhs) && !(lhs == rhs);
		}

		friend bool operator>(const String& lhs, const TCHAR* string)
		{
			String rhs = string;
			return lhs > rhs;
		}

		friend bool operator>(const TCHAR* string, const String& rhs)
		{
			String lhs = string;
			return lhs > rhs;
		}

		friend String operator+(const String& lhs, const String& rhs);

		friend String operator+(const TCHAR* string, const String& rhs)
		{
			String lhs = string;
			return (lhs + rhs);
		}

		friend String operator+(const String& lhs, const TCHAR* string)
		{
			String rhs = string;
			return (lhs + rhs);
		}

		friend String operator+(const String& lhs, const TCHAR c)
		{
			TCHAR* string = new TCHAR[2];
			string[0] = c;
			string[1] = '\0';
			String rhs = string;
			delete[] string;
			return (lhs + rhs);
		}

		friend String operator+(const TCHAR c, const String& rhs)
		{
			TCHAR* string = new TCHAR[2];
			string[0] = c;
			string[1] = '\0';
			String lhs = string;
			delete[] string;
			return (lhs + rhs);
		}

		String operator+=(const String& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

	public:
		static bool   isCharADigit(const TCHAR _ch);
		static double toDouble(const String& _string);
		static int	  toInt(const String& _string);
		static bool	  isEqual(const String& _string1, const String& _string2);
		static bool	  isLesser(const String& _string1, const String& _string2);

	private:
		TCHAR* m_Buffer;
		size_t m_Length;
	};
}; //CORE_LIB