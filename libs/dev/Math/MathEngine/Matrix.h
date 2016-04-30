#pragma once

#include "Vect.h"

class Quat;

class Matrix final : public Align16 {
public:
	Matrix();
	Matrix( const Vect &v0, const Vect &v1, const Vect &v2, const Vect &v3 );
	Matrix( const __m128 &m0, const __m128 &m1, const __m128 &m2, const __m128 &m3 );
	Matrix( const float m0, const float m1, const float m2, const float m3,
			const float m4, const float m5, const float m6, const float m7,
			const float m8, const float m9, const float m10, const float m11,
			const float m12, const float m13, const float m14, const float m15 );
	Matrix( const MatrixSpecialType in );
	Matrix( const MatrixTransType, const float f0, const float f1, const float f2 );
	Matrix( const MatrixTransType, const Vect &v0 );
	Matrix( const MatrixScaleType, const float f0, const float f1, const float f2 );
	Matrix( const MatrixScaleType, const Vect &v0 );
	Matrix( const RotType in, const float f );
	Matrix( const RotAxisAngleType, const Vect &v0, const float f0 );
	Matrix( const Rot3AxisType, const float f0, const float f1, const float f2 );
	Matrix( const RotOrientType in, const Vect &v0, const Vect &v1 );
	Matrix( const Matrix &m0 );
	Matrix( const Quat &q0 );

	~Matrix();

	void set( const MatrixSpecialType in );
	void set( const MatrixTransType, const float f0, const float f1, const float f2 );
	void set( const MatrixTransType, const Vect &v0 );
	void set( const MatrixScaleType, const float f0, const float f1, const float f2 );
	void set( const MatrixScaleType, const Vect &v0 );
	void set( const RotType in, const float f );
	void set( const Rot3AxisType, const float f0, const float f1, const float f2 );
	void set( const RotAxisAngleType, const Vect &v0, const float f0 );
	void set( const RotOrientType in, const Vect &v0, const Vect &v1 );
	void set( const MatrixRowType in, const Vect &v );
	void set( const Vect &v0, const Vect &v1, const Vect &v2, const Vect &v3 );
	void set( const __m128 &m0, const __m128 &m1, const __m128 &m2, const __m128 &m3 );
	void set(const Matrix &m0);
	void set( const Quat &q0 );

	Vect get( const MatrixRowType in )const;

	// unary
	Matrix operator+()const;
	Matrix operator-()const;

	void operator=(const Matrix &t);
	Matrix operator+(const Matrix &t)const;
	void operator+=(const Matrix &t);
	Matrix operator-(const Matrix &t)const;
	void operator-=(const Matrix &t);
	Matrix operator*(const Matrix &t)const;
	void operator*=(const Matrix &t);
	void operator*=(const float f);
	friend Matrix operator*(const float f, const Matrix &t);
	friend Matrix operator*(const Matrix &t, const float f);

	operator float*() { return *m; }

	Vect operator[]( const MatrixRowType )const;
	inline float operator[](const m0_enum)const { return this->_m0; }
	inline float operator[](const m1_enum)const { return this->_m1; }
	inline float operator[](const m2_enum)const { return this->_m2; }
	inline float operator[](const m3_enum)const { return this->_m3; }
	inline float operator[](const m4_enum)const { return this->_m4; }
	inline float operator[](const m5_enum)const { return this->_m5; }
	inline float operator[](const m6_enum)const { return this->_m6; }
	inline float operator[](const m7_enum)const { return this->_m7; }
	inline float operator[](const m8_enum)const { return this->_m8; }
	inline float operator[](const m9_enum)const { return this->_m9; }
	inline float operator[](const m10_enum)const { return this->_m10; }
	inline float operator[](const m11_enum)const { return this->_m11; }
	inline float operator[](const m12_enum)const { return this->_m12; }
	inline float operator[](const m13_enum)const { return this->_m13; }
	inline float operator[](const m14_enum)const { return this->_m14; }
	inline float operator[](const m15_enum)const { return this->_m15; }
	Vect& operator[]( const MatrixRowType );
	inline float& operator[](const m0_enum) { return this->_m0; }
	inline float& operator[](const m1_enum) { return this->_m1; }
	inline float& operator[](const m2_enum) { return this->_m2; }
	inline float& operator[](const m3_enum) { return this->_m3; }
	inline float& operator[](const m4_enum) { return this->_m4; }
	inline float& operator[](const m5_enum) { return this->_m5; }
	inline float& operator[](const m6_enum) { return this->_m6; }
	inline float& operator[](const m7_enum) { return this->_m7; }
	inline float& operator[](const m8_enum) { return this->_m8; }
	inline float& operator[](const m9_enum) { return this->_m9; }
	inline float& operator[](const m10_enum) { return this->_m10; }
	inline float& operator[](const m11_enum) { return this->_m11; }
	inline float& operator[](const m12_enum) { return this->_m12; }
	inline float& operator[](const m13_enum) { return this->_m13; }
	inline float& operator[](const m14_enum) { return this->_m14; }
	inline float& operator[](const m15_enum) { return this->_m15; }

	bool isEqual( const Matrix &t )const;
	bool isIdentity( const float f = MATH_TOLERANCE )const;

	float det()const;
	void T();
	Matrix getT()const;
	void inv();
	Matrix getInv()const;
	Matrix getAdj()const;

private:
	friend Vect;
	friend Quat;
	// Level 4 complains nameless struct/union ...
#pragma warning( disable : 4201)

	union {
		struct {
			__m128 xm0;
			__m128 xm1;
			__m128 xm2;
			__m128 xm3;
		};

		struct {
			Vect v0;
			Vect v1;
			Vect v2;
			Vect v3;
		};

		struct {
			float _m0;
			float _m1;
			float _m2;
			float _m3;

			float _m4;
			float _m5;
			float _m6;
			float _m7;

			float _m8;
			float _m9;
			float _m10;
			float _m11;

			float _m12;
			float _m13;
			float _m14;
			float _m15;
		};

		float m[4][4];
	};
};