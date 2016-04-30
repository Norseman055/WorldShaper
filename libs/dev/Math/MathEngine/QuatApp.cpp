/*****************************************************************************/
/*                                                                           */
/* File: QuatApp.cpp                                                         */
/*                                                                           */
/* Quaternion Application Class                                             */
/*                                                                           */
/*****************************************************************************/

#include "QuatApp.h"
#include "Quat.h"

#include <math.h>

void QuatApp::Slerp( Quat &result, const Quat &source, const Quat &tar, const float slerpFactor ) {
	Quat target;

	// Constants.
	const auto QUAT_EPSILON = 0.001f;
	auto cosom = source.dot( tar );

	// adjust signs if necessary
	if ( cosom < 0.0f ) {
		cosom = -cosom;
		target = -tar;
	} else {
		target = tar;
	}

	// If the the source and target are close, we can do a lerp.
	auto tarFactor = slerpFactor;
	auto srcFactor = 1.0f - slerpFactor;

	// calculate coefficients
	if ( cosom < (1.0f - QUAT_EPSILON) ) {
		// Quats are not close enough for a lerp.
		// Calculating coefficients for a slerp.
		const auto omega = acosf( cosom );
		const auto sinom = 1.0f / sinf( omega );

		srcFactor = sinf( srcFactor * omega ) * sinom;
		tarFactor = sinf( tarFactor * omega ) * sinom;
	}

	// MY mistake: I had tar instead of target in the lines below
	result.set( source[x] * srcFactor + target[x] * tarFactor,
				source[y] * srcFactor + target[y] * tarFactor,
				source[z] * srcFactor + target[z] * tarFactor,
				source[w] * srcFactor + target[w] * tarFactor );
};

void QuatApp::SlerpArray( Quat *result, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats ) {
	for ( auto i = 0; i < numQuats; i++ ) {
		Slerp( result[i], source[i], target[i], slerpFactor );
	}
};

/***** END of File QuatApp.cpp ***********************************************/