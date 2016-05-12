#ifndef EXPORT_H
#define EXPORT_H

#include <File.h>

class FbxConverter;

namespace Export {
	void Print(const FbxConverter& converter);
	void Save(const FbxConverter& converter, const char* filename);
	void CloseFile(FileHandle&);
}

#endif