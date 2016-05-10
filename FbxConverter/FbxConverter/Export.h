#ifndef EXPORT_H
#define EXPORT_H

class FbxConverter;

namespace Export {
	void Print(const FbxConverter& converter);
	void Save(const FbxConverter& converter, const char* filename);
}

#endif