#ifndef MATH_VECT_H
#define MATH_VECT_H

#include "Align16.h"
#include "MathConstants.h"
#include "MathEngineSIMD.h"
#include "MathEnum.h"

// forward declare
class Matrix;
class Quat;
class VectApp;

class Vect final : public Align16 {
public:
	// ctors
	Vect();
	Vect(const float x, const float y, const float z, const float w = 1.0f);

	// copy
	Vect(const Vect& v);
	Vect(const Vect& v, const float w);

	// assignment
	Vect& operator=(const Vect& v);

	// dtor
	~Vect();

	// equality
	bool isEqual(const Vect &rhs, const float tolerance = MATH_TOLERANCE)const;
	bool isZero(const float precision = MATH_TOLERANCE)const;

	// set
	void set(const float x, const float y, const float z, const float w = 1.0f);
	void set(const Vect &v);
	void set(const Vect &v, const float w);

	// xyzw get operators
	inline float operator[](const x_enum)const {	return this->x;	}
	inline float operator[](const y_enum)const {	return this->y;	}
	inline float operator[](const z_enum)const {	return this->z;	}
	inline float operator[](const w_enum)const {	return this->w;	}

	// xyzw set operators
	inline float& operator[](const x_enum) {	return this->x;	}
	inline float& operator[](const y_enum) {	return this->y;	}
	inline float& operator[](const z_enum) {	return this->z;	}
	inline float& operator[](const w_enum) {	return this->w;	}

	// unary operators
	Vect operator+(void)const;
	Vect operator-(void)const;

	// binary operators
	Vect operator+(const Vect &rhs)const;
	Vect operator-(const Vect &rhs)const;
	Vect operator*(const Matrix &rhs)const;
	Vect operator*(const float rhs)const;	// vect * float

	// binary in-place operators
	void operator+=(const Vect &rhs);
	void operator-=(const Vect &rhs);
	void operator*=(const Matrix &rhs);
	void operator*=(const float rhs);

	// get dot product
	float dot(const Vect &t)const;

	// get cross product vector
	Vect cross(const Vect &t)const;

	// normalize/get normalized vector
	void norm();
	Vect getNorm()const;

	// get magnitude/magnitude squared
	float mag()const;
	float magSqr()const;

	// get angle
	float getAngle(const Vect &t)const;

	friend Matrix;
	friend Quat;
	friend VectApp;

private:
	Vect(const M128_TYPE &m);
	Vect(const M128_TYPE &m, const float w);

public:

	// Level 4 complains nameless struct/union ...
#pragma warning( disable : 4201)
	// anonymous union
	union {
		struct {
			M128_TYPE m;
		};

		// anonymous struct
		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};
};

Vect operator*(const float f, const Vect &v);	// float * vect

#endif