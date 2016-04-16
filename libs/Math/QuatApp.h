/*****************************************************************************/
/*                                                                           */
/* file: QuatApp.h                                                           */
/*                                                                           */
/*****************************************************************************/

#pragma once

class Quat;

class QuatApp {
public:
	static void Slerp( Quat &result, const Quat &source, const Quat &target, const float slerpFactor );
	static void SlerpArray( Quat *result, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats );
};

/**** END of QuatApp.h *******************************************************/
