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
		{
		}

		explicit String(const TCHAR* string);
		String(const String& copy);
		const String& operator=(const String& copy);
		const String& operator=(const TCHAR* string);
		~String();

	public:
		const TCHAR* toConstChar() const;
		TCHAR charAt(uint32 at) const;
		size_t legth() const { return m_Length; }
		const String& erase(uint32 at, uint32 count = 1);
		operator const TCHAR*() const;
		const TCHAR operator[](uint32 at) const
		{
			return m_Buffer[at];
		}
		operator double() const;
		operator int() const;
		bool operator==(const String& rhs);
		bool operator<(const String& rhs);
		bool operator>(const String& rhs);
		const String operator+(const String& rhs);
		String operator+=(const String& rhs);

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