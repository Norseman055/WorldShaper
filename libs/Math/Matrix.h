#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include "Vect.h"

class Quat;

class Matrix final : public Align16 {
public:
	// ctors
	Matrix();
	Matrix(const Vect &v0, const Vect &v1, const Vect &v2, const Vect &v3);
	Matrix(const MatrixSpecialType in);
	Matrix(const MatrixTransType, const float x, const float y, const float z);
	Matrix(const MatrixTransType, const Vect &v);
	Matrix(const MatrixScaleType, const float x, const float y, const float z);
	Matrix(const MatrixScaleType, const Vect &v);
	Matrix(const RotType type, const float angle);
	Matrix(const RotOrientType type, const Vect &direction, const Vect &up);
	Matrix(const RotAxisAngleType, const Vect &axis, const float angle);
	Matrix(const Rot3AxisType, const float x, const float y, const float z);
	Matrix(const Quat &q0);

	// copy
	Matrix(const Matrix &m0);

	// assignment
	Matrix& operator=(const Matrix &t);

	// dtor
	~Matrix();

	// equality
	bool isEqual(const Matrix &t, const float f = MATH_TOLERANCE)const;
	bool isIdentity(const float f = MATH_TOLERANCE)const;

	// set
	void set(const MatrixSpecialType in);
	void set(const MatrixTransType, const float x, const float y, const float z);
	void set(const MatrixTransType, const Vect &v);
	void set(const MatrixScaleType, const float x, const float y, const float z);
	void set(const MatrixScaleType, const Vect &v);
	void set(const RotType type, const float angle);
	void set(const RotOrientType type, const Vect &direction, const Vect &up);
	void set(const Rot3AxisType, const float x, const float y, const float z);
	void set(const RotAxisAngleType, const Vect &axis, const float angle);
	void set(const MatrixRowType in, const Vect &v);
	void set(const Vect &v0, const Vect &v1, const Vect &v2, const Vect &v3);
	void set(const Quat &q0);

	// [] get operators
	Vect operator[](const MatrixRowType row)const;
	inline float operator[](const m0_enum)const { return v0[X]; }
	inline float operator[](const m1_enum)const { return v0[Y]; }
	inline float operator[](const m2_enum)const { return v0[Z]; }
	inline float operator[](const m3_enum)const { return v0[W]; }
	inline float operator[](const m4_enum)const { return v1[X]; }
	inline float operator[](const m5_enum)const { return v1[Y]; }
	inline float operator[](const m6_enum)const { return v1[Z]; }
	inline float operator[](const m7_enum)const { return v1[W]; }
	inline float operator[](const m8_enum)const { return v2[X]; }
	inline float operator[](const m9_enum)const { return v2[Y]; }
	inline float operator[](const m10_enum)const { return v2[Z]; }
	inline float operator[](const m11_enum)const { return v2[W]; }
	inline float operator[](const m12_enum)const { return v3[X]; }
	inline float operator[](const m13_enum)const { return v3[Y]; }
	inline float operator[](const m14_enum)const { return v3[Z]; }
	inline float operator[](const m15_enum)const { return v3[W]; }
	Vect get(const MatrixRowType row)const;

	// [] set operators
	Vect& operator[](const MatrixRowType row);
	inline float& operator[](const m0_enum) { return v0[X]; }
	inline float& operator[](const m1_enum) { return v0[Y]; }
	inline float& operator[](const m2_enum) { return v0[Z]; }
	inline float& operator[](const m3_enum) { return v0[W]; }
	inline float& operator[](const m4_enum) { return v1[X]; }
	inline float& operator[](const m5_enum) { return v1[Y]; }
	inline float& operator[](const m6_enum) { return v1[Z]; }
	inline float& operator[](const m7_enum) { return v1[W]; }
	inline float& operator[](const m8_enum) { return v2[X]; }
	inline float& operator[](const m9_enum) { return v2[Y]; }
	inline float& operator[](const m10_enum) { return v2[Z]; }
	inline float& operator[](const m11_enum) { return v2[W]; }
	inline float& operator[](const m12_enum) { return v3[X]; }
	inline float& operator[](const m13_enum) { return v3[Y]; }
	inline float& operator[](const m14_enum) { return v3[Z]; }
	inline float& operator[](const m15_enum) { return v3[W]; }
	
	// unary operators
	Matrix operator+(void)const;
	Matrix operator-(void)const;

	// binary operators
	Matrix operator+(const Matrix &t)const;
	Matrix operator-(const Matrix &t)const;
	Matrix operator*(const Matrix &t)const;
	Matrix operator*(const float f)const;

	// binary in-place operators
	void operator+=(const Matrix &t);
	void operator-=(const Matrix &t);
	void operator*=(const Matrix &t);
	void operator*=(const float f);
	
	// get determinant
	float det()const;

	// get transpose
	void T();
	Matrix getT()const;

	// get inverse
	void inv();
	Matrix getInv()const;

	// get adjutant
	Matrix getAdj()const;

	friend class Vect;
	friend class Quat;

private:
	Matrix(const M128_TYPE& row0, const M128_TYPE& row1, const M128_TYPE& row2, const M128_TYPE& row3);

	Vect v0;
	Vect v1;
	Vect v2;
	Vect v3;
};

Matrix operator*(const float f, const Matrix &t);	// float * matrix

#endif