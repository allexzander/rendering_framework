#pragma once

#include <math.h>

namespace ALZ_RENDERER
{
	//4D Vector---------------------------------------
	template <class T>
	class Vector4D
	{
	public:
		Vector4D()
		{}

		Vector4D(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w)
		{}

		Vector4D(const Vector4D<T>& _other)
		{
			*this = _other;
		}

		Vector4D& operator=(const Vector4D& _other)
		{
			x = _other.x;
			y = _other.y;
			z = _other.z;
			w = _other.w;
			return *this;
		}

		~Vector4D()
		{}

	public:
		Vector4D<T> operator-() const
		{
			return Vector4D<T>(-x, -y, -z, -w);
		}

		Vector4D<T> operator*(T _factor) const
		{
			return Vector4D<T>(x * _factor, y * _factor, z * _factor, w * _factor);
		}

		Vector4D<T> operator/(T _factor) const
		{
			return Vector4D<T>(x / _factor, y / _factor, z / _factor, w / _factor);
		}

		bool operator==(const Vector4D<T>& _other) const
		{
			return x == _other.x && y == _other.y && z == _other.z && w == _other.w; 
		}

		bool operator!=(const Vector4D<T>& _other) const
		{
			return *this != _other;
		}

		Vector4D<T>& operator+=(const Vector4D<T> &_other)
		{
			x += _other.x; y += _other.y; z += _other.z; w += _other.w;
			return *this;
		}

		Vector4D<T>& operator-=(const Vector4D<T> &_other)
		{
			x -= _other.x; y -= _other.y; z -= _other.z; w -= _other.w;
			return *this;
		}

		Vector4D<T>& operator*=(const Vector4D<T> &_other)
		{
			x *= _other.x; y *= _other.y; z *= _other.z; w *= _other.w;
			return *this;
		}

		T length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		void normalize()
		{
			if (length() > 0)
			{
				T magnitude = 1 / length();
				x *= magnitude;
				y *= magnitude;
				z *= magnitude;
				w *= magnitude;
			}
		}

	public:
		T x, y, z, w;
	};//class Vector4D

	//Non-member functions
	template <class T>
	inline Vector4D<T> operator+(const Vector4D<T>& _v1, const Vector4D<T>& _v2)
	{
		return Vector4D<T>(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z, _v1.w + _v2.w);
	}

	template <class T>
	inline Vector4D<T> operator-(const Vector4D<T>& _v1, const Vector4D<T>& _v2)
	{
		return Vector4D<T>(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z, _v1.w - _v2.w);
	}

	template <class T>
	inline T operator*(const Vector4D<T>& _v1, const Vector4D<T>& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z + _v1.w * _v2.w;
	}

	template <class T>
	inline Vector4D<T> operator*(T _factor, const Vector4D<T>& _v)
	{
		return _v * _factor;
	}

	template <class T>
	inline Vector4D<T> Cross(const Vector4D<T>& _v1, const Vector4D<T>& _v2)
	{
		return Vector4D<T>
			((_v1.y * _v2.z - _v1.z * _v2.y),
			(_v1.z * _v2.x - _v1.x * _v2.z),
			(_v1.x * _v2.y - _v1.y * _v2.x),
			T(0));
	}
	//-------------------------------------------------
}; //ALZ_RENDERER