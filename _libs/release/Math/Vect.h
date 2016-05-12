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

	void operator=(const Vect &t);
	Vect operator+(const Vect &t)const;
	void operator+=(const Vect &t);
	Vect operator-(const Vect &t)const;
	void operator-=(const Vect &t);
	Vect operator*(const Matrix &t)const;
	void operator*=(const Matrix &t);
	void operator*=(const float f);
	Vect operator*(const float f)const;	// vect * float
	friend Vect operator*(const float f, const Vect &v);	// float * vect
	Vect operator+()const;
	Vect operator-()const;

	inline float operator[](const x_enum)const { return this->vx; }
	inline float operator[](const y_enum)const { return this->vy; }
	inline float operator[](const z_enum)const { return this->vz; }
	inline float operator[](const w_enum)const { return this->vw; }
	inline float& operator[](const x_enum) { return this->vx; }
	inline float& operator[](const y_enum) { return this->vy; }
	inline float& operator[](const z_enum) { return this->vz; }
	inline float& operator[](const w_enum) { return this->vw; }

	bool isEqual( const Vect &t, const float precision = MATH_TOLERANCE )const;
	bool isZero( const float precision = MATH_TOLERANCE )const;

	float dot( const Vect &t )const;
	Vect cross( const Vect &t )const;
	void norm();
	Vect getNorm()const;
	float mag()const;
	float magSqr()const;
	float getAngle( const Vect &t )const;

	void set( const float x, const float y, const float z, const float w = 1.0f );
	void set( const Vect &v );
	void set(const __m128 &m);

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