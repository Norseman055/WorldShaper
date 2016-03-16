#pragma once

#include "Align16.h"
#include "MathConstants.h"
#include "MathEnum.h"
#include <smmintrin.h>

// forward declare
class Matrix;
class Quat;

class Vect final : public Align16 {
public:

	Vect();
	Vect( const float x, const float y, const float z, const float w = 1.0f );
	Vect( const __m128& inM );
	~Vect();

	void operator = (const Vect &t);
	Vect operator + (const Vect &t)const;
	void operator += (const Vect &t);
	Vect operator - (const Vect &t)const;
	void operator -= (const Vect &t);
	Vect operator * (const Matrix &t)const;
	void operator *= (const Matrix &t);
	void operator *= (const float f);
	Vect operator * (const float f)const;	// vect * float
	friend Vect operator * (const float f, const Vect &v);	// float * vect
	friend Vect operator + (const Vect &t);
	friend Vect operator - (const Vect &t);

	float operator[]( const x_enum )const;
	float& operator[]( const x_enum );
	float operator[]( const y_enum )const;
	float& operator[]( const y_enum );
	float operator[]( const z_enum )const;
	float& operator[]( const z_enum );
	float operator[]( const w_enum )const;
	float& operator[]( const w_enum );

	bool isEqual( const Vect &t, const float &precision = MATH_TOLERANCE )const;
	bool isZero( const float &precision = 0.01f )const;

	float dot( const Vect &t )const;
	Vect cross( const Vect &t )const;
	void norm();
	Vect getNorm()const;
	float mag()const;
	float magSqr()const;
	float getAngle( const Vect &t )const;

	void set( const float x, const float y, const float z, const float w = 1.0f );
	void set( const Vect &v );

private:
	friend Matrix;
	friend Quat;
	// Level 4 complains nameless struct/union ...
#pragma warning( disable : 4201)
	// anonymous union
	union {
		__m128	m;

		// anonymous struct
		struct {
			float vx;
			float vy;
			float vz;
			float vw;
		};
	};
};