#pragma once

#include <math.h>

namespace ALZ_RENDERER
{
	template <class T>
	class Vector3D
	{
	public:
		Vector3D()
		{}
		Vector3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
		{}
		Vector3D(const Vector3D<T>& _other)
		{
			this = _other;
		}
		Vector3D& operator=(const Vector3D& _other)
		{
			x = _other.x;
			y = _other.y;
			z = _other.z;
			return *this;
		}
		~Vector3D()
		{}

	public:
		Vector3D<T> operator-() const
		{
			return Vector3D<T>(-x, -y, -z);
		}

		Vector3D<T> operator*(T _factor) const
		{
			return Vector3D<T>(x * _factor, y * _factor, z * _factor.z);
		}

		Vector3D<T> operator/(T _factor) const
		{
			return Vector3D<T>(x / _factor, y / _factor, z / _factor.z, 0.0f);
		}

		bool operator==(const Vector3D<T>& _other) const
		{
			return x == _other.x && y == _other.y && z = _other.z;
		}

		bool operator!=(const Vector3D<T>& _other) const
		{
			return *this != _other;
		}

		Vector3D<T>& operator+=(const Vector3D<T> &_other)
		{
			x += _other.x; y += _other.y; z += _other.z;
			return *this;
		}

		Vector3D<T>& operator-=(const Vector3D<T> &_other)
		{
			x -= _other.x; y -= _other.y; z -= _other.z;
			return *this;
		}

		Vector3D<T>& operator*=(const Vector3D<T> &_other)
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
			}
		}

	public:
		T x, y, z;
	};//class Vector3D

	//Non-member functions
	template <class T>
	inline Vector3D<T> operator+(const Vector3D<T>& v1, const Vector3D<T>& v2)
	{
		return Vector3D<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	template <class T>
	inline Vector3D<T> operator-(const Vector3D<T>& v1, const Vector3D<T>& v2)
	{
		return Vector3D<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	template <class T>
	inline T operator*(const Vector3D<T>& v1, const Vector3D<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template <class T>
	inline Vector3D<T> operator*(T _factor, const Vector3D<T>& v)
	{
		return v * _factor;
	}

	template <class T>
	inline Vector3D<T> Cross(const Vector3D<T>& v1, const Vector3D<T>& v2)
	{
		return Vector3D<T>
			((v1.y * v2.z - v1.z * v2.y),
			(v1.z * v2.x - v1.x * v2.z),
			(v1.x * v2.y - v1.y * v2.x));
	}
}; //ALZ_RENDERER