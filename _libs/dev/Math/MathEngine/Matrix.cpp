#include "MathEngine.h"
#include <math.h>

const __m128 ZERO_ROW = _mm_setzero_ps();
const __m128 IDENT_ROW0 = _mm_setr_ps(1.0f, 0.0f, 0.0f, 0.0f);
const __m128 IDENT_ROW1 = _mm_setr_ps(0.0f, 1.0f, 0.0f, 0.0f);
const __m128 IDENT_ROW2 = _mm_setr_ps(0.0f, 0.0f, 1.0f, 0.0f);
const __m128 IDENT_ROW3 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);

Matrix::Matrix() {
	this->set(ZERO);
}

Matrix::Matrix( const Vect &in0, const Vect &in1, const Vect &in2, const Vect &in3 ) {
	this->v0.set(in0);
	this->v1.set(in1);
	this->v2.set(in2);
	this->v3.set(in3);
}

Matrix::Matrix( const __m128 &m0, const __m128 &m1, const __m128 &m2, const __m128 &m3 ) {
	this->set(m0, m1, m2, m3);
}

Matrix::Matrix( const float m0, const float m1, const float m2, const float m3,
				const float m4, const float m5, const float m6, const float m7,
				const float m8, const float m9, const float m10, const float m11,
				const float m12, const float m13, const float m14, const float m15 ) {
	this->set(_mm_setr_ps(m0, m1, m2, m3),
			  _mm_setr_ps(m4, m5, m6, m7),
			  _mm_setr_ps(m8, m9, m10, m11),
			  _mm_setr_ps(m12, m13, m14, m15));
}

Matrix::Matrix( const MatrixSpecialType in ) {
	this->set(in);
}

Matrix::Matrix( const MatrixTransType, const float f0, const float f1, const float f2 ) {
	this->set(TRANS, f0, f1, f2);
}

Matrix::Matrix( const MatrixTransType, const Vect &v0 ) {
	this->set(TRANS, v0);
}

Matrix::Matrix( const MatrixScaleType, const float f0, const float f1, const float f2 ) {
	this->set(SCALE, f0, f1, f2);
}

Matrix::Matrix( const MatrixScaleType, const Vect &v0 ) {
	this->set(SCALE, v0);
}

Matrix::Matrix( const RotType in, const float f ) {
	this->set(in, f);
}

Matrix::Matrix( const RotAxisAngleType, const Vect &v0, const float f0 ) {
	this->set(ROT_AXIS_ANGLE, v0, f0);
}

Matrix::Matrix( const Rot3AxisType, const float f0, const float f1, const float f2 ) {
	this->set(ROT_XYZ, f0, f1, f2);
}

Matrix::Matrix( const RotOrientType in, const Vect &v0, const Vect &v1 ) {
	this->set(in, v0, v1);
}

Matrix::Matrix( const Matrix &m0 ) {
	this->set(m0);
}

Matrix::Matrix( const Quat &q0 ) {
	this->set(q0);
}

Matrix::~Matrix() { }

void Matrix::set( const MatrixSpecialType in ) {
	switch ( in ) {
		case ZERO:
			// Matrix of all 0's, reset all values to 0
			_mm_store_ps( reinterpret_cast< float* >(&xm0), ZERO_ROW );
			_mm_store_ps( reinterpret_cast< float* >(&xm1), ZERO_ROW );
			_mm_store_ps( reinterpret_cast< float* >(&xm2), ZERO_ROW );
			_mm_store_ps( reinterpret_cast< float* >(&xm3), ZERO_ROW );
			break;
		case IDENTITY:
			// Matrix of 1's along the diagonal
			_mm_store_ps( reinterpret_cast< float* >(&xm0), IDENT_ROW0 );
			_mm_store_ps( reinterpret_cast< float* >(&xm1), IDENT_ROW1 );
			_mm_store_ps( reinterpret_cast< float* >(&xm2), IDENT_ROW2 );
			_mm_store_ps( reinterpret_cast< float* >(&xm3), IDENT_ROW3 );
			break;
	}
}

void Matrix::set( const MatrixTransType, const float f0, const float f1, const float f2 ) {
	_mm_store_ps( reinterpret_cast< float* >(&xm0), IDENT_ROW0 );
	_mm_store_ps( reinterpret_cast< float* >(&xm1), IDENT_ROW1 );
	_mm_store_ps( reinterpret_cast< float* >(&xm2), IDENT_ROW2 );
	_mm_store_ps( reinterpret_cast< float* >(&xm3), _mm_setr_ps( f0, f1, f2, 1 ) );
}

void Matrix::set( const MatrixTransType, const Vect &_v0 ) {
	_mm_store_ps( reinterpret_cast< float* >(&xm0), IDENT_ROW0 );
	_mm_store_ps( reinterpret_cast< float* >(&xm1), IDENT_ROW1 );
	_mm_store_ps( reinterpret_cast< float* >(&xm2), IDENT_ROW2 );
	_mm_store_ps( reinterpret_cast< float* >(&xm3), _mm_setr_ps( _v0.vx, _v0.vy, _v0.vz, 1 ) );
}

void Matrix::set( const MatrixScaleType, const float f0, const float f1, const float f2 ) {
	_mm_store_ps(reinterpret_cast< float* >(&this->xm0), _mm_setr_ps(f0, 0.0f, 0.0f, 0.0f));
	_mm_store_ps(reinterpret_cast< float* >(&this->xm1), _mm_setr_ps(0.0f, f1, 0.0f, 0.0f));
	_mm_store_ps(reinterpret_cast< float* >(&this->xm2), _mm_setr_ps(0.0f, 0.0f, f2, 0.0f));
	_mm_store_ps(reinterpret_cast< float* >(&this->xm3), IDENT_ROW3);
}

void Matrix::set( const MatrixScaleType, const Vect &v0 ) {
	_mm_store_ps(reinterpret_cast< float* >(&this->xm0), _mm_setr_ps(v0.vx, 0.0f, 0.0f, 0.0f));
	_mm_store_ps(reinterpret_cast< float* >(&this->xm1), _mm_setr_ps(0.0f, v0.vy, 0.0f, 0.0f));
	_mm_store_ps(reinterpret_cast< float* >(&this->xm2), _mm_setr_ps(0.0f, 0.0f, v0.vz, 0.0f));
	_mm_store_ps(reinterpret_cast< float* >(&this->xm3), IDENT_ROW3);
}

void Matrix::set( const RotType in, const float f ) {
	_mm_store_ps(reinterpret_cast<float*>(&this->xm3), IDENT_ROW3);
	const float cf = cosf(f);
	const float sf = sinf(f);

	switch(in) {
		case ROT_X:
			_mm_store_ps(reinterpret_cast< float* >(&this->xm0), IDENT_ROW0);
			_mm_store_ps(reinterpret_cast< float* >(&this->xm1), _mm_setr_ps(0.0f, cf, sf, 0.0f));
			_mm_store_ps(reinterpret_cast< float* >(&this->xm2), _mm_setr_ps(0.0f, -sf, cf, 0.0f));
			break;
		case ROT_Y:
			_mm_store_ps(reinterpret_cast< float* >(&this->xm0), _mm_setr_ps(cf, 0.0f, -sf, 0.0f));
			_mm_store_ps(reinterpret_cast< float* >(&this->xm1), IDENT_ROW1);
			_mm_store_ps(reinterpret_cast< float* >(&this->xm2), _mm_setr_ps(sf, 0.0f, cf, 0.0f));
			break;
		case ROT_Z:
			_mm_store_ps(reinterpret_cast< float* >(&this->xm0), _mm_setr_ps(cf, sf, 0.0f, 0.0f));
			_mm_store_ps(reinterpret_cast< float* >(&this->xm1), _mm_setr_ps(-sf, cf, 0.0f, 0.0f));
			_mm_store_ps(reinterpret_cast< float* >(&this->xm2), IDENT_ROW2);
			break;
	}
}

void Matrix::set( const Rot3AxisType, const float f0, const float f1, const float f2 ) {
	// this = mx * my * mz
	*this = Matrix(Quat(ROT_X, f0) * Quat(ROT_Y, f1) * Quat(ROT_Z, f2));
}

void Matrix::set( const RotAxisAngleType, const Vect &_v0, const float f0 ) {
	const Vect tmp = _v0.getNorm();
	const float cf = cosf(f0);
	const float sf = sinf(f0);

	_mm_store_ps(reinterpret_cast< float* >(&this->xm0), _mm_setr_ps(
		cf + ((tmp[x] * tmp[x])*(1 - cf)),
		((tmp[y] * tmp[x])*(1 - cf)) + (tmp[z] * sf),
		((tmp[z] * tmp[x])*(1 - cf)) - (tmp[y] * sf),
		0.0f));

	_mm_store_ps(reinterpret_cast< float* >(&this->xm1), _mm_setr_ps(
		((tmp[x] * tmp[y])*(1 - cf)) - (tmp[z] * sf),
		cf + ((tmp[y] * tmp[y])*(1 - cf)),
		((tmp[z] * tmp[y])*(1 - cf)) + (tmp[x] * sf),
		0.0f));

	_mm_store_ps(reinterpret_cast< float* >(&this->xm2), _mm_setr_ps(
		((tmp[x] * tmp[z])*(1 - cf)) + (tmp[y] * sf),
		((tmp[y] * tmp[z])*(1 - cf)) - (tmp[x] * sf),
		cf + ((tmp[z] * tmp[z])*(1 - cf)),
		0.0f));

	_mm_store_ps(reinterpret_cast<float*>(&this->xm3), IDENT_ROW3);
}

void Matrix::set( const RotOrientType in, const Vect &_v0, const Vect &_v1 ) {
	const Vect rz = _v0.getNorm();

	auto rx = _v1.cross(rz);
	rx.norm();

	auto ry = rz.cross(rx);
	ry.norm();

	_mm_store_ps(reinterpret_cast< float* >(&this->xm0), _mm_setr_ps(rx.vx, rx.vy, rx.vz, 0.0f));
	_mm_store_ps(reinterpret_cast< float* >(&this->xm1), _mm_setr_ps(ry.vx, ry.vy, ry.vz, 0.0f));
	_mm_store_ps(reinterpret_cast<float*>(&this->xm2), _mm_setr_ps(rz.vx, rz.vy, rz.vz, 0.0f));
	_mm_store_ps(reinterpret_cast<float*>(&this->xm3), IDENT_ROW3);

	switch(in) {
		case ROT_ORIENT:
			// Default is constructed, inverse is calculated as transpose
			break;
		case ROT_INVERSE_ORIENT:
			this->T();
			break;
	}
}

void Matrix::set( const MatrixRowType in, const Vect &v ) {
	switch ( in ) {
		case ROW_0:
			_mm_store_ps( reinterpret_cast< float* >(&xm0), v.m);
			break;
		case ROW_1:
			_mm_store_ps( reinterpret_cast< float* >(&xm1), v.m );
			break;
		case ROW_2:
			_mm_store_ps( reinterpret_cast< float* >(&xm2), v.m );
			break;
		case ROW_3:
			_mm_store_ps( reinterpret_cast< float* >(&xm3), v.m );
			break;
	}
}

void Matrix::set( const Vect &_v0, const Vect &_v1, const Vect &_v2, const Vect &_v3 ) {
	_mm_store_ps( reinterpret_cast< float* >(&xm0), _v0.m );
	_mm_store_ps( reinterpret_cast< float* >(&xm1), _v1.m );
	_mm_store_ps( reinterpret_cast< float* >(&xm2), _v2.m );
	_mm_store_ps( reinterpret_cast< float* >(&xm3), _v3.m );
}

void Matrix::set( const __m128& m0, const __m128& m1, const __m128& m2, const __m128& m3 ) {
	_mm_store_ps( reinterpret_cast< float* >(&xm0), m0 );
	_mm_store_ps( reinterpret_cast< float* >(&xm1), m1 );
	_mm_store_ps( reinterpret_cast< float* >(&xm2), m2 );
	_mm_store_ps( reinterpret_cast< float* >(&xm3), m3 );
}

void Matrix::set(const Matrix &m0) {
	_mm_store_ps(reinterpret_cast< float* >(&this->xm0), m0.xm0);
	_mm_store_ps(reinterpret_cast< float* >(&this->xm1), m0.xm1);
	_mm_store_ps(reinterpret_cast< float* >(&this->xm2), m0.xm2);
	_mm_store_ps(reinterpret_cast< float* >(&this->xm3), m0.xm3);
}

void Matrix::set( const Quat &q0 ) {
	_mm_store_ps(reinterpret_cast< float* >(&this->xm0), _mm_setr_ps(
		1.0f - 2.0f * (q0.qy * q0.qy + q0.qz * q0.qz),
		2.0f * (q0.qx * q0.qy + q0.qw * q0.qz),
		2.0f * (q0.qx * q0.qz - q0.qw * q0.qy),
		0.0f));

	_mm_store_ps(reinterpret_cast< float* >(&this->xm1), _mm_setr_ps(
		2.0f * (q0.qx * q0.qy - q0.qw * q0.qz),
		1.0f - 2.0f * (q0.qx * q0.qx + q0.qz * q0.qz),
		2.0f * (q0.qy * q0.qz + q0.qw * q0.qx),
		0.0f));

	_mm_store_ps(reinterpret_cast< float* >(&this->xm2), _mm_setr_ps(
		2.0f * (q0.qx * q0.qz + q0.qw * q0.qy),
		2.0f * (q0.qy * q0.qz - q0.qw * q0.qx),
		1.0f - 2.0f * (q0.qx * q0.qx + q0.qy * q0.qy),
		0.0f));

	_mm_store_ps(reinterpret_cast<float*>(&this->xm3), IDENT_ROW3);
}

Vect Matrix::get( const MatrixRowType in )const {
	Vect out;

	switch ( in ) {
		case ROW_0:
			_mm_store_ps(reinterpret_cast< float* >(&out.m), this->xm0);
			break;
		case ROW_1:
			_mm_store_ps(reinterpret_cast< float* >(&out.m), this->xm1);
			break;
		case ROW_2:
			_mm_store_ps(reinterpret_cast< float* >(&out.m), this->xm2);
			break;
		case ROW_3:
			_mm_store_ps(reinterpret_cast< float* >(&out.m), this->xm3);
			break;
	}

	return out;
}

void Matrix::operator=(const Matrix &t) {
	this->set( t.v0, t.v1, t.v2, t.v3 );
}

Matrix Matrix::operator+(const Matrix &t)const {
	return Matrix( _mm_add_ps( this->xm0, t.xm0 ),
				   _mm_add_ps( this->xm1, t.xm1 ),
				   _mm_add_ps( this->xm2, t.xm2 ),
				   _mm_add_ps( this->xm3, t.xm3 ) );
}

void Matrix::operator+=(const Matrix &t) {
	_mm_store_ps(reinterpret_cast< float* >(&xm0), _mm_add_ps(this->xm0, t.xm0));
	_mm_store_ps(reinterpret_cast< float* >(&xm1), _mm_add_ps(this->xm1, t.xm1));
	_mm_store_ps(reinterpret_cast< float* >(&xm2), _mm_add_ps(this->xm2, t.xm2));
	_mm_store_ps(reinterpret_cast< float* >(&xm3), _mm_add_ps(this->xm3, t.xm3));
}

Matrix Matrix::operator-(const Matrix &t)const {
	return Matrix( _mm_sub_ps( this->xm0, t.xm0 ),
				   _mm_sub_ps( this->xm1, t.xm1 ),
				   _mm_sub_ps( this->xm2, t.xm2 ),
				   _mm_sub_ps( this->xm3, t.xm3 ) );
}

void Matrix::operator-=(const Matrix &t) {
	_mm_store_ps(reinterpret_cast< float* >(&xm0), _mm_sub_ps(this->xm0, t.xm0));
	_mm_store_ps(reinterpret_cast< float* >(&xm1), _mm_sub_ps(this->xm1, t.xm1));
	_mm_store_ps(reinterpret_cast< float* >(&xm2), _mm_sub_ps(this->xm2, t.xm2));
	_mm_store_ps(reinterpret_cast< float* >(&xm3), _mm_sub_ps(this->xm3, t.xm3));
}

Matrix Matrix::operator*(const Matrix &t)const {
	return Matrix(
		_mm_add_ps( _mm_add_ps( _mm_mul_ps( _mm_set_ps1( _m0 ), t.xm0 ), _mm_mul_ps( _mm_set_ps1( _m1 ), t.xm1 ) ),
		_mm_add_ps( _mm_mul_ps( _mm_set_ps1( _m2 ), t.xm2 ), _mm_mul_ps( _mm_set_ps1( _m3 ), t.xm3 ) ) ),
		_mm_add_ps( _mm_add_ps( _mm_mul_ps( _mm_set_ps1( _m4 ), t.xm0 ), _mm_mul_ps( _mm_set_ps1( _m5 ), t.xm1 ) ),
		_mm_add_ps( _mm_mul_ps( _mm_set_ps1( _m6 ), t.xm2 ), _mm_mul_ps( _mm_set_ps1( _m7 ), t.xm3 ) ) ),
		_mm_add_ps( _mm_add_ps( _mm_mul_ps( _mm_set_ps1( _m8 ), t.xm0 ), _mm_mul_ps( _mm_set_ps1( _m9 ), t.xm1 ) ),
		_mm_add_ps( _mm_mul_ps( _mm_set_ps1( _m10 ), t.xm2 ), _mm_mul_ps( _mm_set_ps1( _m11 ), t.xm3 ) ) ),
		_mm_add_ps( _mm_add_ps( _mm_mul_ps( _mm_set_ps1( _m12 ), t.xm0 ), _mm_mul_ps( _mm_set_ps1( _m13 ), t.xm1 ) ),
		_mm_add_ps( _mm_mul_ps( _mm_set_ps1( _m14 ), t.xm2 ), _mm_mul_ps( _mm_set_ps1( _m15 ), t.xm3 ) ) )
		);
}

void Matrix::operator*=(const Matrix &t) {
	Matrix tmp( *this );

	_mm_store_ps( reinterpret_cast< float* >(&this->xm0),
				  _mm_add_ps( _mm_add_ps( _mm_mul_ps( _mm_set_ps1( tmp._m0 ), t.xm0 ), _mm_mul_ps( _mm_set_ps1( tmp._m1 ), t.xm1 ) ),
				  _mm_add_ps( _mm_mul_ps( _mm_set_ps1( tmp._m2 ), t.xm2 ), _mm_mul_ps( _mm_set_ps1( tmp._m3 ), t.xm3 ) ) )
				  );

	_mm_store_ps( reinterpret_cast< float* >(&this->xm1),
				  _mm_add_ps( _mm_add_ps( _mm_mul_ps( _mm_set_ps1( tmp._m4 ), t.xm0 ), _mm_mul_ps( _mm_set_ps1( tmp._m5 ), t.xm1 ) ),
				  _mm_add_ps( _mm_mul_ps( _mm_set_ps1( tmp._m6 ), t.xm2 ), _mm_mul_ps( _mm_set_ps1( tmp._m7 ), t.xm3 ) ) )
				  );

	_mm_store_ps( reinterpret_cast< float* >(&this->xm2),
				  _mm_add_ps( _mm_add_ps( _mm_mul_ps( _mm_set_ps1( tmp._m8 ), t.xm0 ), _mm_mul_ps( _mm_set_ps1( tmp._m9 ), t.xm1 ) ),
				  _mm_add_ps( _mm_mul_ps( _mm_set_ps1( tmp._m10 ), t.xm2 ), _mm_mul_ps( _mm_set_ps1( tmp._m11 ), t.xm3 ) ) )
				  );

	_mm_store_ps( reinterpret_cast< float* >(&this->xm3),
				  _mm_add_ps( _mm_add_ps( _mm_mul_ps( _mm_set_ps1( tmp._m12 ), t.xm0 ), _mm_mul_ps( _mm_set_ps1( tmp._m13 ), t.xm1 ) ),
				  _mm_add_ps( _mm_mul_ps( _mm_set_ps1( tmp._m14 ), t.xm2 ), _mm_mul_ps( _mm_set_ps1( tmp._m15 ), t.xm3 ) ) )
				  );
}

void Matrix::operator*=(const float f) {
	auto tmp = Matrix( *this );

	_mm_store_ps( reinterpret_cast< float* >(&this->xm0), _mm_mul_ps( tmp.xm0, _mm_set_ps1( f ) ) );
	_mm_store_ps( reinterpret_cast< float* >(&this->xm1), _mm_mul_ps( tmp.xm1, _mm_set_ps1( f ) ) );
	_mm_store_ps( reinterpret_cast< float* >(&this->xm2), _mm_mul_ps( tmp.xm2, _mm_set_ps1( f ) ) );
	_mm_store_ps( reinterpret_cast< float* >(&this->xm3), _mm_mul_ps( tmp.xm3, _mm_set_ps1( f ) ) );
}

Matrix operator*(const float f, const Matrix &t) {
	return Matrix(
		_mm_mul_ps( t.xm0, _mm_set_ps1( f ) ),
		_mm_mul_ps( t.xm1, _mm_set_ps1( f ) ),
		_mm_mul_ps( t.xm2, _mm_set_ps1( f ) ),
		_mm_mul_ps( t.xm3, _mm_set_ps1( f ) ) );
}

Matrix operator*(const Matrix &t, const float f) {
	return Matrix(
		_mm_mul_ps( t.xm0, _mm_set_ps1( f ) ),
		_mm_mul_ps( t.xm1, _mm_set_ps1( f ) ),
		_mm_mul_ps( t.xm2, _mm_set_ps1( f ) ),
		_mm_mul_ps( t.xm3, _mm_set_ps1( f ) ) );
}

Matrix Matrix::operator+()const {
	return *this;
}

Matrix Matrix::operator-()const {
	return *this * -1;
}

Vect Matrix::operator[]( const MatrixRowType row )const {
	switch(row) {
		case ROW_0:
			return this->v0;
		case ROW_1:
			return this->v1;
		case ROW_2:
			return this->v2;
		default:
			return this->v3;
	}
}

Vect& Matrix::operator[]( const MatrixRowType row ) {
	switch ( row ) {
		case ROW_0:
			return this->v0;
		case ROW_1:
			return this->v1;
		case ROW_2:
			return this->v2;
		default:
			return this->v3;
	}
}

bool Matrix::isEqual( const Matrix &t )const {
	return this->v0.isEqual(t.v0)
		&& this->v1.isEqual(t.v1)
		&& this->v2.isEqual(t.v2)
		&& this->v3.isEqual(t.v3);
}

bool Matrix::isIdentity( const float f )const {
	return this->v0.isEqual(IDENT_ROW0, f)
		&& this->v1.isEqual(IDENT_ROW1, f)
		&& this->v2.isEqual(IDENT_ROW2, f)
		&& this->v3.isEqual(IDENT_ROW3, f);
}

float Matrix::det()const {
	return
		this->_m0 * (this->_m5 * (this->_m10 * this->_m15 - this->_m11 * this->_m14) - this->_m6 * (this->_m9 * this->_m15 - this->_m11 * this->_m13) + this->_m7 * (this->_m9 * this->_m14 - this->_m10 * this->_m13))
		- this->_m1 * (this->_m4 * (this->_m10 * this->_m15 - this->_m11 * this->_m14) - this->_m6 * (this->_m8 * this->_m15 - this->_m11 * this->_m12) + this->_m7 * (this->_m8 * this->_m14 - this->_m10 * this->_m12))
		+ this->_m2 * (this->_m4 * (this->_m9 * this->_m15 - this->_m11 * this->_m13) - this->_m5 * (this->_m8 * this->_m15 - this->_m11 * this->_m12) + this->_m7 * (this->_m8 * this->_m13 - this->_m9 * this->_m12))
		- this->_m3 * (this->_m4 * (this->_m9 * this->_m14 - this->_m10 * this->_m13) - this->_m5 * (this->_m8 * this->_m14 - this->_m10 * this->_m12) + this->_m6 * (this->_m8 * this->_m13 - this->_m9 * this->_m12));
}

void Matrix::T() {
	this->set( _mm_setr_ps( this->_m0, this->_m4, this->_m8, this->_m12 ),
			   _mm_setr_ps( this->_m1, this->_m5, this->_m9, this->_m13 ),
			   _mm_setr_ps( this->_m2, this->_m6, this->_m10, this->_m14 ),
			   _mm_setr_ps( this->_m3, this->_m7, this->_m11, this->_m15 ) );
}

Matrix Matrix::getT()const {
	return Matrix( this->_m0, this->_m4, this->_m8, this->_m12,
				   this->_m1, this->_m5, this->_m9, this->_m13,
				   this->_m2, this->_m6, this->_m10, this->_m14,
				   this->_m3, this->_m7, this->_m11, this->_m15 );
}

void Matrix::inv() {
	auto m = 1 / this->det() * this->getAdj();
	this->set( m.xm0, m.xm1, m.xm2, m.xm3 );
}

Matrix Matrix::getInv()const {
	return 1 / this->det() * this->getAdj();
}

Matrix Matrix::getAdj() const {
	Matrix tmp;

	tmp._m0 = _m6 * _m11 * _m13 - _m7 * _m10 * _m13 + _m7 * _m9 * _m14 - _m5 * _m11 * _m14 - _m6 * _m9 * _m15 + _m5 * _m10 * _m15;
	tmp._m1 = _m3 * _m10 * _m13 - _m2 * _m11 * _m13 - _m3 * _m9 * _m14 + _m1 * _m11 * _m14 + _m2 * _m9 * _m15 - _m1 * _m10 * _m15;
	tmp._m2 = _m2 * _m7 * _m13 - _m3 * _m6 * _m13 + _m3 * _m5 * _m14 - _m1 * _m7 * _m14 - _m2 * _m5 * _m15 + _m1 * _m6 * _m15;
	tmp._m3 = _m3 * _m6 * _m9 - _m2 * _m7 * _m9 - _m3 * _m5 * _m10 + _m1 * _m7 * _m10 + _m2 * _m5 * _m11 - _m1 * _m6 * _m11;
	tmp._m4 = _m7 * _m10 * _m12 - _m6 * _m11 * _m12 - _m7 * _m8 * _m14 + _m4 * _m11 * _m14 + _m6 * _m8 * _m15 - _m4 * _m10 * _m15;
	tmp._m5 = _m2 * _m11 * _m12 - _m3 * _m10 * _m12 + _m3 * _m8 * _m14 - _m0 * _m11 * _m14 - _m2 * _m8 * _m15 + _m0 * _m10 * _m15;
	tmp._m6 = _m3 * _m6 * _m12 - _m2 * _m7 * _m12 - _m3 * _m4 * _m14 + _m0 * _m7 * _m14 + _m2 * _m4 * _m15 - _m0 * _m6 * _m15;
	tmp._m7 = _m2 * _m7 * _m8 - _m3 * _m6 * _m8 + _m3 * _m4 * _m10 - _m0 * _m7 * _m10 - _m2 * _m4 * _m11 + _m0 * _m6 * _m11;
	tmp._m8 = _m5 * _m11 * _m12 - _m7 * _m9 * _m12 + _m7 * _m8 * _m13 - _m4 * _m11 * _m13 - _m5 * _m8 * _m15 + _m4 * _m9 * _m15;
	tmp._m9 = _m3 * _m9 * _m12 - _m1 * _m11 * _m12 - _m3 * _m8 * _m13 + _m0 * _m11 * _m13 + _m1 * _m8 * _m15 - _m0 * _m9 * _m15;
	tmp._m10 = _m1 * _m7 * _m12 - _m3 * _m5 * _m12 + _m3 * _m4 * _m13 - _m0 * _m7 * _m13 - _m1 * _m4 * _m15 + _m0 * _m5 * _m15;
	tmp._m11 = _m3 * _m5 * _m8 - _m1 * _m7 * _m8 - _m3 * _m4 * _m9 + _m0 * _m7 * _m9 + _m1 * _m4 * _m11 - _m0 * _m5 * _m11;
	tmp._m12 = _m6 * _m9 * _m12 - _m5 * _m10 * _m12 - _m6 * _m8 * _m13 + _m4 * _m10 * _m13 + _m5 * _m8 * _m14 - _m4 * _m9 * _m14;
	tmp._m13 = _m1 * _m10 * _m12 - _m2 * _m9 * _m12 + _m2 * _m8 * _m13 - _m0 * _m10 * _m13 - _m1 * _m8 * _m14 + _m0 * _m9 * _m14;
	tmp._m14 = _m2 * _m5 * _m12 - _m1 * _m6 * _m12 - _m2 * _m4 * _m13 + _m0 * _m6 * _m13 + _m1 * _m4 * _m14 - _m0 * _m5 * _m14;
	tmp._m15 = _m1 * _m6 * _m8 - _m2 * _m5 * _m8 + _m2 * _m4 * _m9 - _m0 * _m6 * _m9 - _m1 * _m4 * _m10 + _m0 * _m5 * _m10;

	return tmp;
}