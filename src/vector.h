#pragma once

namespace ALZ_RENDERER
{
	//2D Vector---------------------------------------
	template <class T>
	class Vector2D
	{
	public:
		Vector2D()
		{}
		Vector2D(T _x, T _y) : x(_x), y(_y)
		{}
		Vector2D(const Vector2D<T>& _other)
		{
			this = _other;
		}
		const Vector2D& operator=(const Vector2D& _other)
		{
			x = _other.x; 
			y = _other.y;
			return *this;
		}
		~Vector2D()
		{}

	public:
		Vector2D<T> operator-()
		{
			return Vector2D<T>(-x, -y);
		}
		const Vector2D<T>& operator*(T _factor)
		{
			x *= _factor;
			y *= _factor;
			return *this;
		}

	public:
		static T Dot(const Vector2D<T>& v1, const Vector2D<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		static Vector2D UnitX()
		{
			return Vector2D(1.0f, 0.0f);
		}

		static Vector2D UnitY()
		{
			return Vector2D(0.0f, 1.0f);
		}

	public:
		T x;
		T y;
	};

	//3D Vector---------------------------------------
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
		const Vector3D& operator=(const Vector3D& _other)
		{
			x = _other.x;
			y = _other.y;
			z = _other.z;
			return *this;
		}
		Vector3D(Vector2D<T> _2dVec, T _z) : x(_2dVec.x), y(_2dVec.y), z(_z)
		{}
		~Vector3D()
		{}

	public:
		Vector3D<T> operator-()
		{
			return Vector3D<T>(-x, -y, -z);
		}
		const Vector3D<T>& operator*(T _factor)
		{
			x *= _factor;
			y *= _factor;
			z *= _factor;
			return *this;
		}

	public:
		static T Dot(const Vector3D<T>& v1, const Vector3D<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		static Vector3D<T> Cross(const Vector3D<T>& v1, const Vector3D<T>& v2)
		{
			return Vector3D<T>
				((v1.y * v2.z - v1.z * v2.y), 
				(v1.z * v2.x - v1.x * v2.z), 
				(v1.x * v2.y - v1.y * v2.x));
		}

		static Vector3D UnitX()
		{
			return Vector3D(1.0f, 0.0f, 0.0f);
		}

		static Vector3D UnitY()
		{
			return Vector3D(0.0f, 1.0f, 0.0f);
		}

		static Vector3D UnitZ()
		{
			return Vector3D(0.0f, 0.0f, 1.0f);
		}

	public:
		T x;
		T y;
		T z;
	};

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
		const Vector4D& operator=(const Vector4D& _other)
		{
			x = _other.x;
			y = _other.y;
			z = _other.z;
			w = _other.w;
			return *this;
		}
		Vector4D(const Vector3D<T>& _v3D, T _w) : x(_v3D.x), y(_v3D.y), z(_v3D.z), w(_w)
		{}
		~Vector4D()
		{}

	public:
		Vector4D<T> operator-()
		{
			return Vector4D<T>(-x, -y, -z, w);
		}
		const Vector4D<T>& operator*(T _factor)
		{
			x *= _factor;
			y *= _factor;
			z *= _factor;
			return *this;
		}

	public:
		static T Dot(const Vector4D<T>& v1, const Vector4D<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
		}

		static Vector4D<T> Cross(const Vector4D<T>& v1, const Vector4D<T>& v2)
		{
			return Vector4D<T>
				((v1.y * v2.z - v1.z * v2.y),
				(v1.z * v2.x - v1.x * v2.z),
				(v1.x * v2.y - v1.y * v2.x),
				T(0));
		}

		static Vector4D UnitX()
		{
			return Vector4D(Vector3D<T>::UnitX(), 0.0f);
		}

		static Vector4D UnitY()
		{
			return Vector4D(Vector3D<T>::UnitY(), 0.0f);
		}

		static Vector4D UnitZ()
		{
			return Vector4D(Vector3D<T>::UnitZ(), 0.0f);
		}

	public:
		T x;
		T y;
		T z;
		T w;
	};
	//-------------------------------------------------
}; //ALZ_RENDERER