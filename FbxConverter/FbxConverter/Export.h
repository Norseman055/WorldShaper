/// This converter class and almost every method in it is written by Vitor Fernandes. While some modifications may
/// have been made to a few of the functions, the majority of these functions are either direct copies or very close copies
/// of his work. All credit goes to him for this converter and the functionality therein. It has been modified for use
/// with my game engine, but is in no way work attributable to me.

#ifndef EXPORT_H
#define EXPORT_H

#include <File.h>

class FbxConverter;

namespace Export {
	void Print(const FbxConverter& converter);
	void Save(const FbxConverter& converter, const char* filename);
	void CloseFile(FileHandle&);

	void printVerts(const FbxConverter& converter);
	void printNorms(const FbxConverter& converter);
	void printTris(const FbxConverter& converter);
	void printSkeleton(const FbxConverter& converter);
}

#endif