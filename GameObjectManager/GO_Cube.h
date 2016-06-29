#pragma once

#include "GameObject.h"

class GO_Cube : public GameObject {
public:
	void transform(Animation* const) override;

	GO_Cube(const char*);
	~GO_Cube();
private:
	void setupCube();
};