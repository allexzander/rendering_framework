#pragma once

#if _WIN32
//for TCHAR
#include <tchar.h>
#else
typedef char TCHAR;
#endif

namespace CORE_LIB
{
	class String
	{
	public:
		String();
		String(const TCHAR* string);
		String(const String& copy);
		const String& operator=(const String& copy);
		const String& operator=(const TCHAR* string);
		~String();
	public:
		const TCHAR* toConstChar() const;
		TCHAR charAt(unsigned int at) const;
		size_t size() const { return m_Size; }
		operator const TCHAR*() const;
		operator double() const;
		operator int() const;
		bool operator==(const String& rhs);
		bool operator<(const String& rhs);
		bool operator>(const String& rhs);
		String operator+(const String& rhs);
		String operator+=(const String& rhs);
		//Statics
	public:
		static bool   isCharADigit(const TCHAR _ch);
		static double toDouble(const String& _string);
		static int	  toInt(const String& _string);
		static bool	  isEqual(const String& _string1, const String& _string2);
		static bool	  isLesser(const String& _string1, const String& _string2);
	private:
		TCHAR* m_Buffer;
		size_t m_Size;
	};
}; //CORE_LIB