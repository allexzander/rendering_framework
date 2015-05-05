#include "string.h"

namespace CORE_LIB
{
	String::String() : m_Buffer(""), m_Size(0)
	{
	}

	String::String(const TCHAR* string) : m_Buffer(nullptr), m_Size(0)
	{
		unsigned int len = 0;

		while (string[size] != '\0')
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
	
	String::operator const char*() const
	{
		return toConstChar();
	}
};
