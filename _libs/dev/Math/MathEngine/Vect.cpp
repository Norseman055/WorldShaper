#include "MathEngine.h"
#include <math.h>

const __m128 IDENT_ROW = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);

Vect::Vect() {
	this->set(IDENT_ROW);
}

Vect::Vect(const float inX, const float inY, const float inZ, const float inW) {
	this->set(inX, inY, inZ, inW);
}

Vect::Vect(const __m128& inM) {
	this->set(inM);
}

Vect::~Vect() { }

void Vect::operator=(const Vect &t) {
	_mm_store_ps(reinterpret_cast<float*>(&this->m), t.m);
}

Vect Vect::operator+(const Vect &t)const {
	return Vect(_mm_add_ps(_mm_setr_ps(this->vx, this->vy, this->vz, 0.0f), _mm_setr_ps(t.vx, t.vy, t.vz, 1.0f)));
}

void Vect::operator+=(const Vect &t) {
	_mm_store_ps( reinterpret_cast< float* >(&this->m), _mm_add_ps( this->m, t.m ) );
	this->vw = 1.0f;
}

Vect Vect::operator-(const Vect &t)const {
	return Vect(_mm_sub_ps(_mm_setr_ps(this->vx, this->vy, this->vz, 1.0f), _mm_setr_ps(t.vx, t.vy, t.vz, 0.0f)));
}

void Vect::operator-=(const Vect &t) {
	_mm_store_ps( reinterpret_cast< float* >(&this->m), _mm_sub_ps( this->m, t.m ) );
	this->vw = 1.0f;
}

Vect Vect::operator*(const Matrix &M)const {
	return Vect( _mm_add_ps(
		_mm_add_ps( _mm_mul_ps( _mm_set_ps1( this->vx ), M.xm0 ), _mm_mul_ps( _mm_set_ps1( this->vy ), M.xm1 ) ),
		_mm_add_ps( _mm_mul_ps( _mm_set_ps1( this->vz ), M.xm2 ), _mm_mul_ps( _mm_set_ps1( this->vw ), M.xm3 ) ) )
		);
}

void Vect::operator*=(const Matrix &M) {
	_mm_store_ps( reinterpret_cast< float* >(&this->m), _mm_add_ps(
		_mm_add_ps( _mm_mul_ps( _mm_set_ps1( this->vx ), M.xm0 ), _mm_mul_ps( _mm_set_ps1( this->vy ), M.xm1 ) ),
		_mm_add_ps( _mm_mul_ps( _mm_set_ps1( this->vz ), M.xm2 ), _mm_mul_ps( _mm_set_ps1( this->vw ), M.xm3 ) ) )
		);
}

Vect Vect::operator*(const float f)const {
	return Vect(_mm_mul_ps(_mm_setr_ps(this->vx, this->vy, this->vz, 1.0f), _mm_setr_ps(f, f, f, 1.0f)));
}

void Vect::operator*=(const float f) {
	_mm_store_ps( reinterpret_cast< float* >(&this->m), _mm_mul_ps( this->m, _mm_set_ps1( f ) ) );
	this->vw = 1.0f;
}

Vect operator*(const float f, const Vect &v) {
	return v * f;
}

Vect Vect::operator+() const {
	return Vect(_mm_setr_ps(this->vx, this->vy, this->vz, 1.0f));
}

Vect Vect::operator-() const {
	return *this * -1;
}

bool Vect::isEqual( const Vect &t, const float prec )const {
	return Util::isEqual(this->vx, t.vx, prec)
		&& Util::isEqual(this->vy, t.vy, prec)
		&& Util::isEqual(this->vz, t.vz, prec)
		&& Util::isEqual(this->vw, t.vw, prec);
}

bool Vect::isZero( const float prec )const {
	return Util::isZero(this->vx, prec)
		&& Util::isZero(this->vy, prec)
		&& Util::isZero(this->vz, prec)
		&& Util::isZero(this->vw - 1.0f, prec);
}

float Vect::dot( const Vect &t )const {
	Vect dotted( _mm_mul_ps( this->m, t.m ) );
	return (dotted.vx + dotted.vy + dotted.vz);
}

Vect Vect::cross( const Vect &t )const {
	return Vect( this->vy * t.vz - this->vz * t.vy, this->vz * t.vx - this->vx * t.vz, this->vx * t.vy - this->vy * t.vx, this->vw );
}

void Vect::norm() {
	_mm_store_ps( reinterpret_cast< float* >(&this->m), _mm_div_ps( this->m, _mm_set_ps1( this->mag() ) ) );
	this->vw = 1.0f;
}

Vect Vect::getNorm()const {
	Vect norming( *this );
	norming.norm();

	return norming;
}

float Vect::mag()const {
	return sqrtf( this->magSqr() );
}

float Vect::magSqr()const {
	return this->vx * this->vx + this->vy * this->vy + this->vz * this->vz;
}

float Vect::getAngle( const Vect &t )const {
	// T = theta
	// cosT = (a.dot(b)/a.mag()*b.mag())
	// T = acosf(a.dot(b)/a.mag()*b.mag());

	return acosf( this->dot( t ) / (this->mag() * t.mag()) );
}

void Vect::set(const float inX, const float inY, const float inZ, const float inW) {
	_mm_store_ps(reinterpret_cast<float*>(&this->m), _mm_setr_ps(inX, inY, inZ, inW));
}

void Vect::set( const Vect &v ) {
	_mm_store_ps(reinterpret_cast<float*>(&this->m), v.m);
}

void Vect::set(const __m128 &m) {
	_mm_store_ps(reinterpret_cast<float*>(&this->m), m);
}