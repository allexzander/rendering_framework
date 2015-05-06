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
		~String();
	public:
		const TCHAR* toConstChar() const;
		TCHAR charAt(unsigned int at) const;
		size_t size() const { return m_Size; }
		operator const TCHAR*() const;
		operator double() const;
		operator int() const;
		//Statics
	public:
		static bool   isCharADigit(const TCHAR _ch);
		static double toDouble(const String& _string);
		static int toInt(const String& _string);
	private:
		TCHAR* m_Buffer;
		size_t m_Size;
	};
}; //CORE_LIB