#ifndef _MATH_HPP
#define _MATH_HPP

class Vector2 {
	public:
		Vector2();
		Vector2(float x, float y);
		Vector2(const Vector2& v);
		Vector2& operator = (const Vector2& v);
		
		//accessors
		float x() const;
		float y() const;
		
		float* data();
		
		//operators
		Vector2 operator - ();
		Vector2 operator + (const Vector2& v);
		Vector2 operator - (const Vector2& v);
		
		Vector2& operator += (const Vector2& v);
		Vector2& operator -= (const Vector2& v);
		
		Vector2 operator * (const float& c);
		Vector2 operator / (const float& c);
		
		Vector2& operator *= (const float& c);
		Vector2& operator /= (const float& c);
		
		//inner product
		float operator* (const Vector2& v);
		
		//distance & length
		float norm();
		float distance(const Vector2& v);
		
	private:
		float data_[2];
};

class Vector3 {
	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& v);
		Vector3& operator = (const Vector3& v);
	
		//accessors
		float x() const;
		float y() const;
		float z() const;
		
		float* data();
		
		//operators
		Vector3 operator - ();
		Vector3 operator + (const Vector3& v);
		Vector3 operator - (const Vector3& v);
		
		Vector3& operator += (const Vector3& v);
		Vector3& operator -= (const Vector3& v);
		
		Vector3 operator * (const float& c);
		Vector3 operator / (const float& c);
		
		Vector3& operator *= (const float& c);
		Vector3& operator /= (const float& c);
		
		//inner product
		float operator* (const Vector3& v);
		
		//cross product
		Vector3 cross(const Vector3& v);
		
		//distance & length
		float norm();
		float distance(const Vector3& v);
		
	private:
		float data_[3];
};

class Matrix3 {
	public:
		static Matrix3 zero();
		static Matrix3 identity();
		
		Matrix3();
		Matrix3(const Matrix3& m);
		Matrix3& operator = (const Matrix3& m);
		
		float* data();
		
		float& operator () (int r, int c);
		
		Vector3 operator * (const Vector3& v);
		Matrix3 operator * (Matrix3& m);
		
	private:
		float data_[9];
		
};

Matrix3 rotationMatrix3(const Vector3& axis, const float& angle);

class Matrix4 {
	public:
		static Matrix4 zero();
		static Matrix4 identity();
		static Matrix4 transform(const Matrix3& rot, const Vector3& t);
		
		Matrix4();
		Matrix4(const Matrix4& m);
		Matrix4& operator = (const Matrix4& m);
		
		float* data();
		
		//Vector4 operator * (const Vector4& v);
		Matrix4 operator * (Matrix3& m);
		
	private:
		float data_[16];
};

typedef Vector2 Point2;
typedef Vector3 Point3;

#endif
