#pragma once

#include "GameObject.h"

class GO_Cube : public GameObject {
public:
	GO_Cube(const char*);
	~GO_Cube();
private:
	void setupCube();
};