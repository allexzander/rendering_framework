#include "string.h"
#include <assert.h>

namespace CORE_LIB
{
	String::String(const TCHAR* string) : m_Buffer(nullptr), m_Length(0)
	{
		size_t len = 0;

		while (string[len] != '\0')
		{
			++len;
		}

		if (len > 0)
		{
			m_Buffer = new TCHAR[len + 1];

			for (size_t i = 0; i < len; ++i)
			{
				m_Buffer[i] = string[i];
			}

			m_Buffer[len] = '\0';
			m_Length	  = len;
		}
	}

	String::String(const String& copy) :String()
	{
		if (copy.legth() > 0)
		{
			m_Length = copy.legth();
			m_Buffer = new TCHAR[m_Length + 1];

			for (size_t i = 0; i < m_Length; ++i)
			{
				m_Buffer[i] = copy[i];
			}

			m_Buffer[m_Length] = '\0';
		}
	}

	String::~String()
	{
		if (legth() > 0)
		{
			delete[] m_Buffer;
			m_Length = 0;
		}
	}

	const String& String::operator=(const String& copy)
	{
		if (copy.legth() > 0)
		{
			if (m_Buffer)
			{
				delete[] m_Buffer;
			}

			m_Length = copy.legth();
			m_Buffer = new TCHAR[m_Length + 1];

			for (size_t i = 0; i < m_Length; ++i)
			{
				m_Buffer[i] = copy[i];
			}

			m_Buffer[m_Length] = '\0';
		}

		return *this;
	}

	const String& String::operator=(const TCHAR* string)
	{
		size_t len = 0;

		while (string[len] != '\0')
		{
			++len;
		}

		if (len > 0)
		{
			if (m_Buffer)
			{
				delete[] m_Buffer;
			}

			m_Buffer = new TCHAR[len + 1];

			for (size_t i = 0; i < len; ++i)
			{
				m_Buffer[i] = string[i];
			}

			m_Buffer[len] = '\0';

			m_Length = len;
		}

		return *this;
	}

	String operator+(const String& lhs, const String& rhs)
	{
		String result;

		if (lhs.m_Length > 0 || rhs.m_Length > 0)
		{
			TCHAR* resChar = new TCHAR[lhs.m_Length + rhs.m_Length];

			uint32 i = 0;

			while (i < lhs.m_Length)
			{
				resChar[i] = lhs.m_Buffer[i];
				++i;
			}

			for (size_t j = 0; j < rhs.m_Length; ++j)
			{
				resChar[i] = rhs[j];
				++i;
			}

			resChar[i] = '\0';

			result = resChar;
		}

		return result;
	}

	const TCHAR* String::toConstChar() const
	{
		return m_Buffer;
	}

	TCHAR String::charAt(uint32 at) const
	{
		if (m_Buffer != nullptr && at >= 0 && at < m_Length)
		{
			return m_Buffer[at];
		}
		else
		{
			assert("Wrong index 'at' charAt");
		}

		return 0;
	}

	const String& String::erase(uint32 at, uint32 count)
	{
		if (m_Length > 0)
		{
			if (count < m_Length)
			{
				TCHAR* erased = new TCHAR[m_Length - count + 1];

				size_t j = 0;

				for (size_t i = 0; i < m_Length; ++i)
				{
					if (i < at || i >(at + count - 1))
					{
						erased[j] = m_Buffer[i];
						++j;
					}
				}

				erased[j] = '\0';

				if (m_Buffer)
				{
					delete[] m_Buffer;
				}

				m_Buffer = erased;
				m_Length = j;
			}
			else if (count == m_Length)
			{
				delete[] m_Buffer;
				m_Length = 0;
			}
		}
		
		return *this;
	}

	String String::trim()
	{
		if (m_Length > 0 && m_Buffer[0] == _T(' '))
		{
			size_t trimCount = 0;

			while (m_Buffer[trimCount] == _T(' ') && trimCount < m_Length)
			{
				++trimCount;
			}

			if (trimCount == m_Length)
			{
				clear();
			}
			else
			{
				erase(0, trimCount);
			}
		}

		return *this;
	}

	void String::clear()
	{
		if (m_Length > 0 && m_Buffer != nullptr)
		{
			delete[] m_Buffer;
			m_Buffer = nullptr;
			m_Length = 0;
		}
	}

	bool String::startsWith(const String& pattern) const
	{
		if (m_Length > 0 && pattern.legth() > 0 && pattern.legth() <= m_Length)
		{
			for (size_t i = 0; i < pattern.legth(); ++i)
			{
				if (m_Buffer[i] != pattern[i])
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}

	bool String::endsWith(const String& pattern) const
	{
		if (m_Length > 0 && pattern.legth() > 0 && pattern.legth() <= m_Length)
		{
			for (int i = m_Length - 1, j = pattern.legth() - 1; i >= 0, j >= 0; --i, --j)
			{
				if (m_Buffer[i] != pattern[static_cast<size_t>(j)])
				{
					return false;
				}
			}

			return true;
		}

		return false;
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

		if (_string.legth() > 0)
		{
			String copy = _string;

			bool isNegative = copy.charAt(0) == _T('-');

			if (isNegative)
			{
				copy.erase(0, 1);
			}

			bool isFractionalPart = false;
			uint32 fracPart = 0;
			uint32 fractionalPartDivisor = 1;

			for (size_t i = 0; i < copy.legth(); ++i)
			{
				TCHAR ch = copy[i];

				if (ch == '.')
				{
					if (i == 0 || isFractionalPart)
					{
						assert(false && "Error! Convert String to double failed!!!");
						return 0;
					}

					isFractionalPart = true;
					continue;
				}

				if (!isCharADigit(ch))
				{
					assert(false && "Error! Convert String to double failed!!!");
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
		int32 result = 0;

		if (_string.legth() > 0)
		{
			String copy = _string;

			bool isNegative = copy.charAt(0) == _T('-');

			if (isNegative)
			{
				copy.erase(0, 1);
			}

			for (size_t i = 0; i < copy.legth(); ++i)
			{
				TCHAR ch = copy[i];

				if (!isCharADigit(ch))
				{
					if (!(ch == '.' && i != 0))
					{
						result = 0;
						assert(false && "Error! Convert String to int failed!!!");
					}

					break;
				}

				result = (result * 10) + (ch - '0');
			}

			if (isNegative)
			{
				result = -result;
			}
		}

		return result;
	}

	bool String::isEqual(const String& _string1, const String& _string2)
	{
		if (_string1.legth() == _string2.legth())
		{
			for (uint32 i = 0; i < static_cast<uint32>(_string1.legth()); ++i)
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
		if((_string1.legth() == 0 && _string2.legth() == 0) || _string2.legth() <= _string1.legth())
		{
			return false;
		}
		
		if(_string1.legth() < _string2.legth())
		{
			//Left sting is shorter. Return without further comparison.
			return true;
		}
		
	
		for (uint32 i = 0; i < static_cast<uint32>(_string1.legth()); ++i)
		{
			if (_string1.charAt(i) < _string2.charAt(i))
			{
				return true;
			}
		}
		
		return false;
	}
};
