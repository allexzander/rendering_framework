#include "string.h"

namespace CORE_LIB
{
	String::String() : m_Buffer(nullptr), m_Size(0)
	{
		m_Buffer = new TCHAR[1];
		m_Buffer[0] = 0;
		m_Size = 0;
	}

	String::String(const TCHAR* string) : m_Buffer(nullptr), m_Size(0)
	{
		unsigned int len = 0;

		while (string[len] != '\0')
		{
			++len;
		}

		if (len > 0)
		{
			m_Buffer = new TCHAR[len + 1];

			for (unsigned i = 0; i < len; ++i)
			{
				m_Buffer[i] = string[i];
			}

			m_Buffer[len] = '\0';

			m_Size = len;
		}
	}

	String::String(const String& copy) :String()
	{
		if (copy.size() > 0)
		{
			m_Size = 0;

			if (m_Buffer != nullptr)
			{
				delete[] m_Buffer;
			}

			m_Buffer = new TCHAR[copy.size() + 1];

			for (unsigned int i = 0; i < copy.size(); ++i)
			{
				m_Buffer[i] = copy.charAt(i);
			}

			m_Size = copy.size();

			m_Buffer[m_Size] = '\0';
		}
	}

	String::~String()
	{
		if (m_Size > 0)
		{
			delete[] m_Buffer;
			m_Size = 0;
		}
	}

	const String& String::operator=(const String& copy)
	{
		return *this;
	}

	const TCHAR* String::toConstChar() const
	{
		return m_Buffer;
	}

	TCHAR String::charAt(unsigned int at) const
	{
		if (m_Buffer != nullptr && at >= 0 && at < m_Size)
		{
			return m_Buffer[at];
		}

		return 0;
	}

	String::operator const TCHAR*() const
	{
		return toConstChar();
	}

	bool String::isCharADigit(const char _ch)
	{
		if(_ch == '0' || _ch == '1' || _ch == '2' || _ch == '3' || _ch == '4' || _ch == '5'
			|| _ch == '6' || _ch == '7' || _ch == '8' || _ch == '9')
		{
			return true;
		}
		return false;
	}

	double String::toDouble(const String& _string)
	{
		double result = 0.0;
		return result;
	}
};
