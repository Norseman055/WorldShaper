#ifndef FBX_CONVERTER_H
#define FBX_CONVERTER_H

#include <vector>

using namespace std;

namespace fbxsdk {
	class FbxManager;
	class FbxScene;
}

struct Vector;
struct Triangle;

class FbxConverter {
public:
	void Import(const char* filepath);
	const vector<const Vector>& GetVertices() const;
	const vector<const Vector>& GetNormals() const;
	const vector<const Triangle>& GetTriangles() const;

	FbxConverter();
	~FbxConverter();

	// No copy or assignment
	FbxConverter(FbxConverter&) = delete;
	FbxConverter& operator=(FbxConverter&) = delete;

private:
	void ImportVertices();
	void ImportNormals();
	void ImportTriangles();

private:
	vector<const Vector> vertices;
	vector<const Vector> normals;
	vector<const Triangle> triangles;

	fbxsdk::FbxManager* const fbxManager;
	fbxsdk::FbxScene* const fbxScene;
};

#endif