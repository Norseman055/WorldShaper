#pragma once

class WorldShaper {
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

	// Singleton methods
	static WorldShaper* getInstance();
	WorldShaper();

	// Member variables
};