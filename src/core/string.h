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
		unsigned int size() const { return m_Size; }
		operator const TCHAR*() const;
		//Statics
	public:
		static bool   isCharADigit(const char _ch);
		static double toDouble(const String& _string);
	private:
		TCHAR* m_Buffer;
		unsigned int m_Size;
	};
}; //CORE_LIB