#pragma once

#include "Singleton.h"

class WorldShaper : public Singleton<WorldShaper> {
	friend class Singleton<WorldShaper>;
public:
	// Methods
	static void Run();

	virtual ~WorldShaper();

private:
	// Methods
	static void Startup();
	static void Shutdown();

	void update(double gameTime);
	void draw();

	// Member variables
};