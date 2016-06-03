#pragma once

#include "Singleton.h"

class WorldShaper : public Singleton<WorldShaper> {
	friend class Singleton<WorldShaper>;
public:
	// Methods
	static void Run();

	virtual ~WorldShaper();

private:
	WorldShaper();

	// Methods
	static void Startup();
	static void SetGLFWCallbacks();
	static void Shutdown();

	void runGameLoop();
	void update(const float);
	void draw();

	// Member variables
	float tCurrent;
	float tPrevious;
	float tDelta;
};