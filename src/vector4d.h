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
			this = _other;
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
			return Vector4D<T>(-x, -y, -z, w);
		}

		Vector4D<T> operator*(T _factor) const
		{
			return Vector4D<T>(x * _factor, y * _factor, z * _factor.z, 0.0f);
		}

		Vector4D<T> operator/(T _factor) const
		{
			return Vector4D<T>(x / _factor, y / _factor, z / _factor.z, 0.0f);
		}

		bool operator==(const Vector4D<T>& _other) const
		{
			return x == _other.x && y == _other.y && z = _other.z;
		}

		bool operator!=(const Vector4D<T>& _other) const
		{
			return *this != _other;
		}

		Vector4D<T>& operator+=(const Vector4D<T> &_other)
		{
			x += _other.x; y += _other.y; z += _other.z;
			return *this;
		}

		Vector4D<T>& operator-=(const Vector4D<T> &_other)
		{
			x -= _other.x; y -= _other.y; z -= _other.z;
			return *this;
		}

		Vector4D<T>& operator*=(const Vector4D<T> &_other)
		{
			x *= _other.x; y *= _other.y; z *= _other.z;
			return *this;
		}

		float length() const
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
	inline Vector4D<T> operator+(const Vector4D<T>& v1, const Vector4D<T>& v2)
	{
		return Vector4D<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, 0.0f);
	}

	template <class T>
	inline Vector4D<T> operator-(const Vector4D<T>& v1, const Vector4D<T>& v2)
	{
		return Vector4D<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, 0.0f);
	}

	template <class T>
	inline T operator*(const Vector4D<T>& v1, const Vector4D<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template <class T>
	inline Vector4D<T> operator*(T _factor, const Vector4D<T>& v)
	{
		return v * _factor;
	}

	template <class T>
	inline Vector4D<T> Cross(const Vector4D<T>& v1, const Vector4D<T>& v2)
	{
		return Vector4D<T>
			((v1.y * v2.z - v1.z * v2.y),
			(v1.z * v2.x - v1.x * v2.z),
			(v1.x * v2.y - v1.y * v2.x),
			T(0));
	}
	//-------------------------------------------------
}; //ALZ_RENDERER