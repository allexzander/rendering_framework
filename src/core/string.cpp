#include "string.h"
#include "commondefs.h"

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
		uint32 len = 0;

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

			for (uint32 i = 0; i < static_cast<uint32>(copy.size()); ++i)
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

	TCHAR String::charAt(uint32 at) const
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

	String::operator double() const
	{
		return toDouble(*this);
	}

	String::operator int() const
	{
		return toInt(*this);
	}

	bool String::operator == (const String& rhs)
	{
		return isEqual(*this, rhs);
	}

	bool String::operator<(const String& rhs)
	{
		return isLesser(*this, rhs);
	}

	bool String::operator>(const String& rhs)
	{
		return (!isEqual(*this, rhs) && !isLesser(*this, rhs));
	}

	bool String::isCharADigit(const TCHAR _ch)
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

		if (_string.size() > 0)
		{
			bool isNegative	= (_string.charAt(0) == '-');
			bool isFractionalPart = false;
			uint32 fracPart = 0;
			uint32 fractionalPartDivisor = 1;

			for (uint32 i = (isNegative) ? 1 : 0; i < static_cast<uint32>(_string.size()); ++i)
			{
				TCHAR ch = _string.charAt(i);

				if (ch == '.')
				{
					if (i == 0 || isFractionalPart)
					{
						return 0;
					}

					isFractionalPart = true;
					continue;
				}

				if (!isCharADigit(ch))
				{
					return 0;
				}

				if (isFractionalPart)
				{
					fracPart = (fracPart * 10) + (ch - '0');
					fractionalPartDivisor *= 10;
				}
				else
				{
					result = (result * 10) + (ch - '0');
				}
			}

			result += fracPart / static_cast<double>(fractionalPartDivisor);

			if (isNegative)
			{
				result = -result;
			}
		}

		return result;
	}

	int String::toInt(const String& _string)
	{
		return static_cast<int>(toDouble(_string));
	}

	bool String::isEqual(const String& _string1, const String& _string2)
	{
		if (_string1.size() == _string2.size())
		{
			for (uint32 i = 0; i < static_cast<uint32>(_string1.size()); ++i)
			{
				if (_string1.charAt(i) != _string2.charAt(i))
				{
					return false;
				}
			}
			
			return true;
		}

		return false;
	}

	bool String::isLesser(const String& _string1, const String& _string2)
	{
		/*if (_string1.size() == _string2.size())
		{
			for (uint32 i = 0; i < static_cast<uint32>(_string1.size()); ++i)
			{
				if (_string1.charAt(i) != _string2.charAt(i))
				{
					return false;
				}

				return true;
			}
		}*/

		return false;
	}
};
