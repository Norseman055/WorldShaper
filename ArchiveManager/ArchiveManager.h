#pragma once

#include "Singleton.h"

class ArchiveManager : public Singleton<ArchiveManager> {
	friend class Singleton<ArchiveManager>;
public:
	static void Startup();
	static void Shutdown();

	static void LoadModelFromFile(const char*);

private:
	static void CloseFile(void*);
};