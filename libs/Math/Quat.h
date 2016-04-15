/** @file */
/*****************************************************************************/
/*                                                                           */
/* file: Quat.h                                                              */
/*                                                                           */
/*****************************************************************************/

#ifndef MATH_QUAT_H
#define MATH_QUAT_H

/*****************************************************************************/
/* Includes:                                                                 */
/*****************************************************************************/
#include "MathEnum.h"
#include "Matrix.h"

/*************************************************************************
*
* This class contains functions and data structure for a 4-dimensional
* Quaternions.  The quaternions are internally stored interms of the
* imaginary components (qx,qy,qz) and the real components (qw).
*
* In the Math library, quaternions can be thought of as "rotational"
* matrices, everything that you can represent with rotational matrices
* you can use with quaternions.  Such as quaternion concatenation,
* inverses, transpose, normalize, multiplying with matrices, and with
* vectors.
*
*
**************************************************************************/

class Quat final : public Align16 {
public:
	// ctors
	Quat();
	Quat(const float x, const float y, const float z, const float w);
	Quat(const Vect &v);
	Quat(const Vect &v, const float f);
	Quat(const Matrix &m);
	Quat(const M128_TYPE &m);
	Quat(RotType type, const float angle);
	Quat(Rot3AxisType, const float x, const float y, const float z);
	Quat(RotAxisAngleType, const Vect &axis, const float angle);
	Quat(RotOrientType type, const Vect &direction, const Vect &up);
	Quat(MatrixSpecialType type);

	// copy
	Quat(const Quat &q0);

	// assignment
	Quat& operator=(const Quat &q);

	// dtor
	~Quat();

	// equality
	bool isEqual(const Quat &q, const float precision) const;
	bool isNegEqual(const Quat &q, const float precision) const;
	bool isEquivalent(const Quat &q, const float precision) const;
	bool isConjugateEqual(const Quat &q, const float precision) const;
	bool isIdentity(const float precision) const;
	bool isNormalized(const float precision) const;
	bool isZero(const float precision) const;

	// set
	void set(const float x, const float y, const float z, const float w);
	void set(const Vect &v);
	void set(const Vect &v, const float f);
	void set(const Matrix &m);
	void set(const M128_TYPE &m);
	void set(RotType in, const float f);
	void set(Rot3AxisType, const float x, const float y, const float z);
	void set(RotAxisAngleType, const Vect &axis, const float angle);
	void set(RotOrientType type, const Vect &direction, const Vect &up);
	void set(MatrixSpecialType type);

	// xyzw get operators
	inline float operator[](const x_enum)const { return this->qx; }
	inline float operator[](const y_enum)const { return this->qy; }
	inline float operator[](const z_enum)const { return this->qz; }
	inline float operator[](const w_enum)const { return this->qw; }

	// xyzw set operators
	inline float& operator[](const x_enum) { return this->qx; }
	inline float& operator[](const y_enum) { return this->qy; }
	inline float& operator[](const z_enum) { return this->qz; }
	inline float& operator[](const w_enum) { return this->qw; }

	// unary operators
	Quat operator-(void)const;
	Quat operator+(void)const;

	// binary operators
	Quat operator+(const Quat &q)const;
	Quat operator+(const float f0)const;
	Quat operator-(const Quat &q)const;
	Quat operator-(const float f0)const;
	Quat operator*(const Quat &q)const;
	Quat operator*(const float f)const;
	Quat operator/(const Quat &q)const;
	Quat operator/(const float f0)const;

	// binary in-place operators
	void operator+=(const Quat &q);
	void operator+=(const float f0);
	void operator-=(const Quat &q);
	void operator-=(const float f0);
	void operator*=(const Quat &q);
	void operator*=(const float f0);
	void operator*=(const Matrix &m);
	void operator/=(const Quat &q);
	void operator/=(const float f0);

	// multiply by element
	Quat multByElement( const Quat &q ) const;

	// get Conjugate
	void conj();
	Quat getConj()const;

	// get Transpose
	void T();
	Quat getT() const;

	// get Normal
	void norm();
	Quat getNorm()const;

	// get Inverse
	void inv();
	Quat getInv()const;

	// set / get Axis / angle
	void setVect(const Vect &v0);
	void getVect(Vect &v) const;
	void getAxis( Vect &v ) const; // definitely same as getVect.
	float getAngle()const;

	// get magnitude / squared / inverse
	float mag()const;
	float magSquared()const;
	float invMag()const;

	// get Dot product
	float dot( const Quat &q )const;

	// SPECIAL!
	void Lqvqc(const Vect &vIn, Vect &vOut) const;
	void Lqcvq(const Vect &vIn, Vect &vOut) const;

private:
	// Level 4 complains nameless struct/union ...
#pragma warning( disable : 4201)

	// anonymous union
	union {
		struct {
			M128_TYPE m;
		};

		// anonymous struct
		struct {
			float qx;
			float qy;
			float qz;
			float qw;
		};
	};

	friend class Matrix;
	friend Quat operator/(const float f0, const Quat &q);
};

Quat operator+(const float f0, const Quat &q);
Quat operator-(const float f0, const Quat &q);
Quat operator*(const float f0, const Quat &q);
Quat operator/(const float f0, const Quat &q);

#endif

/**** END of Quat.h ********************************************************/
