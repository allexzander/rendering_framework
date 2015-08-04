#pragma once

#include <math.h>

namespace ALZ_RENDERER
{
	template <class T>
	class Vector2D
	{
	public:
		Vector2D() : x(0), y(0)
		{}

		Vector2D(T _x, T _y) : x(_x), y(_y)
		{}

		Vector2D(const Vector2D<T>& _other)
		{
			*this = _other;
		}

		Vector2D& operator=(const Vector2D& _other)
		{
			x = _other.x;
			y = _other.y;
			return *this;
		}

		~Vector2D()
		{}

	public:
		Vector2D<T> operator-() const
		{
			return Vector2D<T>(-x, -y);
		}

		Vector2D<T> operator*(T _factor) const
		{
			return Vector2D<T>(x * _factor, y * _factor);
		}

		Vector2D<T> operator/(T _factor) const
		{
			return Vector3D<T>(x / _factor, y / _factor);
		}

		bool operator==(const Vector2D<T>& _other) const
		{
			return x == _other.x && y == _other.y;
		}

		bool operator!=(const Vector2D<T>& _other) const
		{
			return *this != _other;
		}

		Vector2D<T>& operator+=(const Vector2D<T> &_other)
		{
			x += _other.x; y += _other.y;
			return *this;
		}

		Vector2D<T>& operator-=(const Vector2D<T> &_other)
		{
			x -= _other.x; y -= _other.y;
			return *this;
		}

		Vector2D<T>& operator*=(const Vector2D<T> &_other)
		{
			x *= _other.x; y *= _other.y;
			return *this;
		}

		T length() const
		{
			return sqrt(x * x + y * y);
		}

		void normalize()
		{
			if (length() > 0)
			{
				T magnitude = 1 / length();
				x *= magnitude;
				y *= magnitude;
			}
		}

	public:
		T x, y;
	};//class Vector2D

	//Non-member functions
	template <class T>
	inline Vector2D<T> operator+(const Vector2D<T>& _v1, const Vector2D<T>& _v2)
	{
		return Vector2D<T>(_v1.x + _v2.x, _v1.y + _v2.y);
	}

	template <class T>
	inline Vector2D<T> operator-(const Vector2D<T>& _v1, const Vector2D<T>& _v2)
	{
		return Vector2D<T>(_v1.x - _v2.x, _v1.y - _v2.y);
	}

	template <class T>
	inline T operator*(const Vector2D<T>& _v1, const Vector2D<T>& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y;
	}

	template <class T>
	inline Vector2D<T> operator*(T _factor, const Vector2D<T>& _v)
	{
		return _v * _factor;
	}
};//ALZ_RENDERER