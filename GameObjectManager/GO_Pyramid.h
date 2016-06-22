#pragma once

#include "GameObject.h"

class GO_Pyramid : public GameObject {
public:
	GO_Pyramid(const char*);
	~GO_Pyramid();
private:
	void setupPyramid();
};