#pragma once

#include "Math\Vect.h"

struct Vertex : public Align16 {
	Vect pos;
	Vect normal;
	Vect color;		// x = R, y = G, z = B, w = A
	Vect uv;		// x = U, y = V
};