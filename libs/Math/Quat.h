/** @file */
/*****************************************************************************/
/*                                                                           */
/* file: Quat.h                                                              */
/*                                                                           */
/*****************************************************************************/

#pragma once

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

	Quat();
	Quat( const Quat &q0 );
	Quat( const __m128 &m0 );
	Quat( const float f0, const float f1, const float f2, const float f3 );
	Quat( const Vect &v, const float f0 );
	Quat( const Matrix &m0 );
	Quat( RotType in, const float f0 );
	Quat( RotAxisAngleType, const Vect &v, const float f0 );
	Quat( Rot3AxisType, const float f0, const float f1, const float f2 );
	Quat( RotOrientType in, const Vect &v0, const Vect &v1 );
	Quat( MatrixSpecialType in );
	~Quat();

	float operator[]( const x_enum )const;
	float operator[]( const y_enum )const;
	float operator[]( const z_enum )const;
	float operator[]( const w_enum )const;
	float& operator[]( const x_enum );
	float& operator[]( const y_enum );
	float& operator[]( const z_enum );
	float& operator[]( const w_enum );

	void set( const float f0, const float f1, const float f2, const float f3 );
	void set( const Vect &v, const float f );
	void set( const Matrix &m );
	void set( const __m128 &xm );
	void set( RotType in, const float f );
	void set( RotAxisAngleType, const Vect &v, const float f0 );
	void set( Rot3AxisType, const float f0, const float f1, const float f2 );
	void set( RotOrientType in, const Vect &v0, const Vect &v1 );
	void set( MatrixSpecialType in );

	void setVect( const Vect &v0 );
	void getVect( Vect &v0 ) const;

	// binary
	void operator = (const Quat &q);
	Quat operator + (const Quat &q)const;
	Quat operator + (const float f0)const;
	void operator += (const Quat &q);
	void operator += (const float f0);
	friend Quat operator + (const float f0, const Quat &t);
	Quat operator - (const Quat &q)const;
	Quat operator - (const float f0)const;
	void operator -= (const Quat &q);
	void operator -= (const float f0);
	friend Quat operator - (const float f0, const Quat &q);
	Quat operator * (const Quat &q)const;
	Quat operator * (const float f)const;
	void operator *= (const Quat &q);
	void operator *= (const float f0);
	void operator *= (const Matrix &m);
	friend Quat operator * (const float f0, const Quat &q);
	Quat operator / (const Quat &q)const;
	Quat operator / (const float f0)const;
	void operator /= (const Quat &q);
	void operator /= (const float f0);
	friend Quat operator / (const float f0, const Quat &q);

	// unary
	friend Quat operator - (const Quat &q);
	friend Quat operator + (const Quat &q);

	Quat multByElement( const Quat &q ) const;
	Quat getConj()const;
	Quat getT() const;
	Quat norm();
	Quat getNorm()const;
	Quat getInv()const;

	void conj();
	void T();
	void inv();
	void Lqvqc( const Vect &vIn, Vect &vOut ) const;
	void Lqcvq( const Vect &vIn, Vect &vOut ) const;
	void getAxis( Vect &v ) const;

	float mag()const;
	float magSquared()const;
	float invMag()const;
	float dot( const Quat &q )const;
	float getAngle()const;

	bool isEqual( const Quat &q, const float precision ) const;
	bool isNegEqual( const Quat &q, const float precision ) const;
	bool isEquivalent( const Quat &q, const float precision ) const;
	bool isConjugateEqual( const Quat &q, const float precision ) const;
	bool isIdentity( const float precision ) const;
	bool isNormalized( const float precision ) const;
	bool isZero( const float precision ) const;

private:
	friend Matrix;
	// Level 4 complains nameless struct/union ...
#pragma warning( disable : 4201)

	// anonymous union
	union {
		__m128	m;

		// anonymous struct
		struct {
			float qx;
			float qy;
			float qz;
			float qw;
		};
	};
};

/**** END of Quat.h ********************************************************/
