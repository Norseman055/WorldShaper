#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Vector {
	float x, y, z;
};

struct Matrix {
	float elements[4][4];
};

struct Triangle {
	unsigned int a, b, c;
};


#endif