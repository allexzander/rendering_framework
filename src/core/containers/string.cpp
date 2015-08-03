#include "../../../include/core/containers/string.h"
#include <assert.h>

namespace CORE_LIB
{
	String::String(const TCHAR* string) : m_pBuffer(nullptr), m_Length(0)
	{
		size_t len = 0;

		while (string[len] != '\0')
		{
			++len;
		}

		if (len > 0)
		{
			m_pBuffer = new TCHAR[len + 1];

			for (size_t i = 0; i < len; ++i)
			{
				m_pBuffer[i] = string[i];
			}

			m_pBuffer[len] = '\0';
			m_Length	   = len;
		}
	}

	String::String(const String& _copy) : String()
	{
		if (_copy.legth() > 0)
		{
			m_Length  = _copy.legth();
			m_pBuffer = new TCHAR[m_Length + 1];

			for (size_t i = 0; i < m_Length; ++i)
			{
				m_pBuffer[i] = _copy[i];
			}

			m_pBuffer[m_Length] = '\0';
		}
	}

	String::~String()
	{
		clear();
	}

	const String& String::operator=(const String& _copy)
	{
		if (_copy.legth() > 0)
		{
			if (m_pBuffer)
			{
				delete[] m_pBuffer;
			}

			m_Length  = _copy.legth();
			m_pBuffer = new TCHAR[m_Length + 1];

			for (size_t i = 0; i < m_Length; ++i)
			{
				m_pBuffer[i] = _copy[i];
			}

			m_pBuffer[m_Length] = '\0';
		}

		return *this;
	}

	const String& String::operator=(const TCHAR* _string)
	{
		size_t len = 0;

		while (_string[len] != '\0')
		{
			++len;
		}

		if (len > 0)
		{
			if (m_pBuffer)
			{
				delete[] m_pBuffer;
			}

			m_pBuffer = new TCHAR[len + 1];

			for (size_t i = 0; i < len; ++i)
			{
				m_pBuffer[i] = _string[i];
			}

			m_pBuffer[len] = '\0';

			m_Length	   = len;
		}
		else
		{
			clear();
		}

		return *this;
	}

	String operator+(const String& _lhs, const String& _rhs)
	{
		String result;

		if (_lhs.m_Length > 0 || _rhs.m_Length > 0)
		{
			TCHAR* buffer = new TCHAR[_lhs.m_Length + _rhs.m_Length];

			size_t i = 0;

			while (i < _lhs.m_Length)
			{
				buffer[i] = _lhs.m_pBuffer[i];
				++i;
			}

			for (size_t j = 0; j < _rhs.m_Length; ++j)
			{
				buffer[i] = _rhs[j];
				++i;
			}

			buffer[i] = '\0';

			result = buffer;
		}

		return result;
	}

	const TCHAR* String::toConstChar() const
	{
		assert(m_pBuffer != nullptr && "m_pBuffer != nullptr");
		return m_pBuffer;
	}

	TCHAR String::charAt(uint32 _at) const
	{
		assert(m_pBuffer != nullptr && "m_pBuffer != nullptr");
		assert(_at >= 0 && _at < m_Length && "Index out of range!!!");

		return m_pBuffer[_at];
	}

	const String& String::erase(uint32 _at, uint32 _count)
	{
		assert(m_Length > 0 && "String is empty!!!");

		if(_count == m_Length)
		{
			clear();
			return *this;
		}

		if (_count < m_Length)
		{
			TCHAR* erasedBuffer = new TCHAR[(m_Length - _count) + 1];

			size_t j = 0;

			size_t lowerBound =  _at;
			size_t upperBound = _at + _count - 1;

			for (size_t i = 0; i < m_Length; ++i)
			{
				if (i < lowerBound || i > upperBound)
				{
					erasedBuffer[j] = m_pBuffer[i];
					++j;
				}
			}

			erasedBuffer[j] = '\0';

			if (m_pBuffer)
			{
				delete[] m_pBuffer;
			}

			m_pBuffer = erasedBuffer;
			m_Length  = j;
		}

		return *this;
	}

	String String::trim()
	{
		if (m_Length > 0 && m_pBuffer[0] == _T(' '))
		{
			size_t trimCount = 0;

			while (m_pBuffer[trimCount] == _T(' ') && trimCount < m_Length)
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

	/*
		**Clears and deletes m_pBuffer
	*/
	void String::clear()
	{
		if (m_Length > 0 && m_pBuffer != nullptr)
		{
			delete[] m_pBuffer;
			m_pBuffer = nullptr;
			m_Length  = 0;
		}
	}

	bool String::startsWith(const String& _pattern) const
	{
		if (m_Length > 0 && _pattern.legth() > 0 && _pattern.legth() <= m_Length)
		{
			for (size_t i = 0; i < _pattern.legth(); ++i)
			{
				if (m_pBuffer[i] != _pattern[i])
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}

	bool String::endsWith(const String& _pattern) const
	{
		if (m_Length > 0 && _pattern.legth() > 0 && _pattern.legth() <= m_Length)
		{
			for (int i = m_Length - 1, j = _pattern.legth() - 1; i >= 0, j >= 0; --i, --j)
			{
				if (m_pBuffer[i] != _pattern[static_cast<size_t>(j)])
				{
					return false;
				}
			}

			return true;
		}

		return false;
	}

	CORE_LIB::TVectorArray<String> String::split(TCHAR _splitter) const
	{
		CORE_LIB::TVectorArray<String> result;

		if (m_Length > 0)
		{
			String currentWord = _T("");

			size_t index = 0;

			while (index < m_Length)
			{
				if (m_pBuffer[index] != _splitter)
				{
					currentWord += m_pBuffer[index];
				}
				else
				{
					result.push_back(currentWord);
					currentWord = _T("");
				}
				++index;
			}

			result.push_back(currentWord);
		}

		return result;
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
		assert(_string.legth() > 0 && "_string.legth() > 0");

		double result = 0.0;

		if (_string.legth() > 0)
		{
			auto copy		= _string;
			bool isNegative = copy.charAt(0) == _T('-');

			if (isNegative)
			{
				copy.erase(0, 1);
			}

			bool isFractionalPart		 = false;
			uint32 fracPart				 = 0;
			uint32 fractionalPartDivisor = 1;

			for (size_t i = 0; i < copy.legth(); ++i)
			{
				auto ch = copy[i];

				if (ch == '.')
				{
					if (i == 0 || isFractionalPart)
					{
						assert(false && "Error! Incorrect string!!!");
						return 0;
					}

					isFractionalPart = true;
					continue;
				}

				if (!isCharADigit(ch))
				{
					assert(false && "Error! Incorrect string!!!");
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

			//add fractional part to result, by dividing fracPart by (1 * (10 * n)), where n = number of fractional digits
			result += (fracPart / static_cast<double>(fractionalPartDivisor));

			if (isNegative)
			{
				result = -result;
			}
		}

		return result;
	}

	int String::toInt(const String& _string)
	{
		assert(_string.legth() > 0 && "_string.legth() > 0");

		int32 result = 0;

		if (_string.legth() > 0)
		{
			auto copy		= _string;
			bool isNegative = copy.charAt(0) == _T('-');

			if (isNegative)
			{
				copy.erase(0, 1);
			}

			for (size_t i = 0; i < copy.legth(); ++i)
			{
				auto ch = copy[i];

				if (!isCharADigit(ch))
				{
					if (!(ch == '.' && i != 0))
					{
						result = 0;
						assert(false && "Incorrect string!!!");
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
		if (_string1.legth() == _string2.legth() && _string1.legth() != 0 && _string2.legth() != 0)
		{
			for (size_t i = 0; i < _string1.legth(); ++i)
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
		if (_string1.legth() > _string2.legth() || _string1.legth() == 0 && _string2.legth() == 0)
		{
			return false;
		}

		if (_string2.legth() > _string1.legth())
		{
			return true;
		}

		for (size_t i = 0; i < _string1.legth(); ++i)
		{
			if (_string1.charAt(i) < _string2.charAt(i))
			{
				return true;
			}
		}
		
		return false;
	}
};
