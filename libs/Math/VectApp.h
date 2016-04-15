/*****************************************************************************/
/*                                                                           */
/* file: VectApp.h                                                           */
/*                                                                           */
/*****************************************************************************/

#ifndef VECT_APP_H
#define VECT_APP_H

class Vect;

class VectApp {
public:

	// lerp
	static void Lerp(Vect &out, const Vect &a, const Vect &b, const float t);
	static const Vect Lerp(const Vect& a, const Vect& b, const float t);

	// lerp array
	static void LerpArray(Vect *out, const Vect *a, const Vect *b, const float t, const int numVects);
};

#endif

/**** END of VectApp.h *******************************************************/