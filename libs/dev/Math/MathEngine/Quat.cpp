/*****************************************************************************/
/*                                                                           */
/* File: Quat.cpp                                                            */
/*                                                                           */
/* Quaternion Class                                                           */
/*                                                                           */
/*****************************************************************************/

#include "Quat.h"
#include <math.h>

const __m128 ZERO_ROW = _mm_setzero_ps();
const __m128 IDENT_ROW = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);

Quat::Quat() {
	this->set(IDENT_ROW);
}

Quat::Quat( const Quat &q0 ) {
	this->set(q0);
}

Quat::Quat( const __m128& m0 ) {
	this->set(m0);
}

Quat::Quat( const Matrix &M ) {
	this->set(M);
}

Quat::Quat( const float f0, const float f1, const float f2, const float f3 ) {
	this->set(f0, f1, f2, f3);
}

Quat::Quat( const Vect &v, const float f0 ) {
	this->set(v, f0);
}

Quat::Quat( const Rot3AxisType, const float f0, const float f1, const float f2 ) {
	this->set(ROT_XYZ, f0, f1, f2);
}

Quat::Quat( const RotType in, const float f0 ) {
	this->set(in, f0);
}

Quat::Quat( const RotAxisAngleType, const Vect &v, const float f0 ) {
	this->set(ROT_AXIS_ANGLE, v, f0);
}

Quat::Quat( const RotOrientType in, const Vect &v0, const Vect &v1 ) {
	this->set(in, v0, v1);
}

Quat::Quat( MatrixSpecialType in ) {
	this->set(in);
}

Quat::~Quat() { }

void Quat::set( const float f0, const float f1, const float f2, const float f3 ) {
	_mm_store_ps(reinterpret_cast<float*>(&this->m), _mm_setr_ps(f0, f1, f2, f3));
}

void Quat::set( const Matrix &M ) {
	auto tr = M._m0 + M._m5 + M._m10;

	if(tr > 0.0f) {
		const float S = 2.0f * sqrtf(tr + 1.0f);
		_mm_store_ps(reinterpret_cast< float* >(&m), _mm_setr_ps(
			-(M._m9 - M._m6) / S,
			-(M._m2 - M._m8) / S,
			-(M._m4 - M._m1) / S,
			0.25f * S));
	} else if((M._m0 > M._m5) && (M._m0 > M._m10)) {
		const float S = 2.0f * sqrtf(1.0f + M._m0 - M._m5 - M._m10);
		_mm_store_ps(reinterpret_cast< float* >(&m), _mm_setr_ps(
			0.25f * S,
			(M._m1 + M._m4) / S,
			(M._m2 + M._m8) / S,
			-(M._m9 - M._m6) / S));
	} else if(M._m5 > M._m10) {
		const float S = 2.0f * sqrtf(1.0f + M._m5 - M._m0 - M._m10);
		_mm_store_ps(reinterpret_cast< float* >(&m), _mm_setr_ps(
			(M._m1 + M._m4) / S,
			0.25f * S,
			(M._m6 + M._m9) / S,
			-(M._m2 - M._m8) / S));
	} else {
		const float S = 2.0f * sqrtf(1.0f + M._m10 - M._m0 - M._m5);
		_mm_store_ps(reinterpret_cast< float* >(&m), _mm_setr_ps(
			(M._m2 + M._m8) / S,
			(M._m6 + M._m9) / S,
			0.25f * S,
			-(M._m4 - M._m1) / S));
	}
}

void Quat::set( const RotType in, const float f ) {
	this->set(IDENT_ROW);
	const float sf = sinf(f / 2.0f);
	const float cf = cosf(f / 2.0f);

	switch ( in ) {
		case ROT_X:
			this->qx = sf;
			break;
		case ROT_Y:
			this->qy = sf;
			break;
		default:
			this->qz = sf;
			break;
	}

	this->qw = cf;
}

void Quat::set( const Vect &v, const float f ) {
	_mm_store_ps(reinterpret_cast<float*>(&this->m), _mm_setr_ps(v.vx, v.vy, v.vz, f));
}

void Quat::set( const __m128& xm ) {
	_mm_store_ps(reinterpret_cast<float*>(&this->m), xm);
}

void Quat::set(const Quat& q) {
	_mm_store_ps(reinterpret_cast<float*>(&this->m), q.m);
}

void Quat::set( const RotAxisAngleType, const Vect &v, const float f0 ) {
	this->set(v.getNorm().m);

	_mm_store_ps(reinterpret_cast<float*>(&this->m), _mm_mul_ps(this->m, _mm_set1_ps(sinf(f0 / 2.0f))));
	this->qw = cosf(f0 / 2.0f);
}

void Quat::set( const RotOrientType in, const Vect &v0, const Vect &v1 ) {
	this->set(Matrix(in, v0, v1));
}

void Quat::set( const MatrixSpecialType in ) {
	switch ( in ) {
		case ZERO:
			_mm_store_ps( reinterpret_cast< float* >(&m), ZERO_ROW );
			break;
		default:
			_mm_store_ps( reinterpret_cast< float* >(&m), IDENT_ROW );
			break;
	}
}

void Quat::set( const Rot3AxisType, const float f0, const float f1, const float f2 ) {
	this->set(ROT_X, f0);
	
	Quat temp(ROT_Y, f1);
	*this *= temp;

	temp.set(ROT_Z, f2);
	*this *= temp;
};

void Quat::setVect( const Vect &v0 ) {
	_mm_store_ps( reinterpret_cast< float* >(&m), _mm_setr_ps( v0.vx, v0.vy, v0.vz, this->qw ) );
};

void Quat::getVect( Vect &v0 ) const {
	_mm_store_ps( reinterpret_cast< float* >(&v0.m), _mm_setr_ps( this->qx, this->qy, this->qz, v0.vw ) );
};

void Quat::operator=(const Quat &q) {
	_mm_store_ps( reinterpret_cast< float* >(&m), q.m );
};

Quat Quat::operator+(const Quat &q)const {
	return Quat( _mm_add_ps( this->m, q.m ) );
};

Quat Quat::operator+(const float f0)const {
	return Quat( _mm_add_ps( this->m, _mm_set_ps1( f0 ) ) );
};

void Quat::operator+=(const Quat &q) {
	_mm_store_ps( reinterpret_cast< float* >(&m), _mm_add_ps( this->m, q.m ) );;
};

void Quat::operator+=(const float f0) {
	_mm_store_ps( reinterpret_cast< float* >(&m), _mm_add_ps( this->m, _mm_set_ps1( f0 ) ) );
};

Quat operator+(const float f0, const Quat &q) {
	return q + f0;
};

Quat Quat::operator-(const Quat &q)const {
	return Quat( _mm_sub_ps( this->m, q.m ) );
};

Quat Quat::operator-(const float f0)const {
	return Quat( _mm_sub_ps( this->m, _mm_set_ps1( f0 ) ) );
};

void Quat::operator-=(const Quat &q) {
	_mm_store_ps( reinterpret_cast< float* >(&m), _mm_sub_ps( this->m, q.m ) );
};

void Quat::operator-=(const float f0) {
	_mm_store_ps( reinterpret_cast< float* >(&m), _mm_sub_ps( this->m, _mm_set_ps1( f0 ) ) );
};

Quat operator-(const float f0, const Quat &q) {
	return -q + f0;
};

Quat Quat::operator*(const Quat &q)const {
	Vect vLeft( this->qx, this->qy, this->qz );
	Vect vRight( q.qx, q.qy, q.qz );
	return Quat( Vect( vRight.cross( vLeft ) + (q.qw * vLeft) + (this->qw * vRight) ), (this->qw * q.qw) - vLeft.dot( vRight ) );
};

Quat Quat::operator*(const float f)const {
	return Quat( _mm_mul_ps( this->m, _mm_set_ps1( f ) ) );
};

void Quat::operator*=(const Quat &q) {
	Vect vLeft( this->qx, this->qy, this->qz );
	Vect vRight( q.qx, q.qy, q.qz );
	*this = Quat( Vect( vRight.cross( vLeft ) + (q.qw * vLeft) + (this->qw * vRight) ), (this->qw * q.qw) - vLeft.dot( vRight ) );
};

void Quat::operator*=(const float f) {
	_mm_store_ps( reinterpret_cast< float* >(&m), _mm_mul_ps( this->m, _mm_set_ps1( f ) ) );
};

void Quat::operator*=(const Matrix &_m) {
	this->set( Matrix( *this ) * _m );
};

Quat operator*(const float f, const Quat &q) {
	return q * f;
};

Quat Quat::operator/(const Quat &q)const {
	return Quat( _mm_div_ps( this->m, q.m ) );
};

Quat Quat::operator/(const float f0)const {
	return Quat( _mm_div_ps( this->m, _mm_set_ps1( f0 ) ) );
};

void Quat::operator/=(const Quat &q) {
	_mm_store_ps( reinterpret_cast< float* >(&this->m), _mm_div_ps( this->m, q.m ) );
};

void Quat::operator/=(const float f0) {
	_mm_store_ps( reinterpret_cast< float* >(&this->m), _mm_div_ps( this->m, _mm_set_ps1( f0 ) ) );
};

Quat operator/(const float f0, const Quat &q) {
	return Quat( _mm_div_ps( _mm_set_ps1( f0 ), q.m ) );
};

Quat Quat::operator-() const {
	return Quat( *this * -1 );
};

Quat Quat::operator+() const {
	return *this;
};

Quat Quat::multByElement( const Quat &q ) const {
	return Quat( _mm_mul_ps( this->m, q.m ) );
};

Quat Quat::getConj()const {
	return Quat( _mm_mul_ps( this->m, _mm_setr_ps( -1, -1, -1, 1 ) ) );
};

Quat Quat::getT() const {
	return this->getConj();
};

Quat Quat::norm() {
	float magSqr = this->magSquared();
	__m128 rMag = _mm_rsqrt_ps(_mm_set1_ps(magSqr));
	_mm_store_ps(reinterpret_cast< float* >(&this->m), _mm_mul_ps(this->m, rMag));
	return *this;
};

Quat Quat::getNorm()const {
	return Quat(*this).norm();
};

Quat Quat::getInv()const {
	return Quat(_mm_div_ps(this->m, _mm_set_ps1(this->magSquared()))).getConj();
};

void Quat::conj() {
	_mm_store_ps( reinterpret_cast< float* >(&m), _mm_mul_ps( this->m, _mm_setr_ps( -1, -1, -1, 1 ) ) );
};

void Quat::T() {
	this->conj();
};

void Quat::inv() {
	*this = Quat(_mm_div_ps(this->m, _mm_set_ps1(this->magSquared()))).getConj();
};

void Quat::Lqcvq( const Vect &vIn, Vect &vOut ) const {
	const Vect tmp( this->qx, this->qy, this->qz );
	vOut = 2.0f * this->qw * tmp.cross( vIn ) + (this->qw * this->qw - tmp.dot( tmp )) * vIn + 2.0f * tmp.dot( vIn ) * tmp;
};

void Quat::Lqvqc( const Vect &vIn, Vect &vOut ) const {
	const Vect tmp( this->qx, this->qy, this->qz );
	vOut = 2.0f * this->qw * vIn.cross( tmp ) + (this->qw * this->qw - tmp.dot( tmp )) * vIn + 2.0f * tmp.dot( vIn ) * tmp;
};

void Quat::getAxis( Vect &v ) const {
	_mm_store_ps( reinterpret_cast< float* >(&v.m), _mm_setr_ps( qx, qy, qz, v.vw ) );
};

float Quat::mag()const {
	return sqrtf( this->magSquared() );
};

float Quat::magSquared()const {
	return this->qx * this->qx + this->qy * this->qy + this->qz * this->qz + this->qw * this->qw;
};

float Quat::invMag()const {
	return 1 / this->mag();
};

float Quat::dot( const Quat &q )const {
	return this->qx * q.qx + this->qy * q.qy + this->qz * q.qz + this->qw * q.qw;
};

float Quat::getAngle()const {
	return 2 * (acosf( this->qw ));
};

bool Quat::isEqual( const Quat &q, const float f0 ) const {
	auto answer = false;
	if ( fabs( this->qx - q.qx ) <= f0 && fabs( this->qy - q.qy ) <= f0 && fabs( this->qz - q.qz ) <= f0 && fabs( this->qw - q.qw ) <= f0 ) {
		answer = true;
	}
	return answer;
};

bool Quat::isNegEqual( const Quat &q, const float f0 ) const {
	auto answer = false;
	if ( this->qx + q.qx <= f0 && this->qy + q.qy <= f0 && this->qz + q.qz <= f0 && this->qw + q.qw <= f0 ) {
		answer = true;
	}
	return answer;
};

bool Quat::isEquivalent( const Quat &q, const float precision ) const {
	auto answer = this->isEqual( q, precision );
	if ( !answer ) {
		answer = this->isEqual( -q, precision );
	}
	return answer;
};

bool Quat::isConjugateEqual( const Quat &q, const float precision ) const {
	auto answer = false;
	if ( this->qx + q.qx <= precision && this->qy + q.qy <= precision && this->qz + q.qz <= precision && this->qw - q.qw <= precision ) {
		answer = true;
	}
	return answer;
};

bool Quat::isIdentity( const float precision ) const {
	auto answer = false;
	if ( fabs( this->qx ) - precision <= 0 && fabs( this->qy ) - precision <= 0 && fabs( this->qz ) - precision <= 0 && fabs( this->qw ) - 1 - precision <= 0 ) {
		answer = true;
	}
	return answer;
};

bool Quat::isNormalized( const float precision ) const {
	auto answer = false;
	Vect tmp( this->qx, this->qy, this->qz );

	if ( fabs( this->qw * this->qw + tmp.dot( tmp ) ) - 1 <= precision ) {
		answer = true;
	}
	return answer;
};

bool Quat::isZero( const float precision ) const {
	auto answer = false;
	if ( fabs( this->qx ) <= precision && fabs( this->qy ) <= precision && fabs( this->qz ) <= precision && fabs( this->qw ) <= precision ) {
		answer = true;
	}
	return answer;
};