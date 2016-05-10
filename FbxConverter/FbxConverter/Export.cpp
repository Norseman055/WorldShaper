#include "Export.h"
#include "FbxConverter.h"
#include "Structures.h"
#include <stdio.h>
#include <File.h>
#include <algorithm>
#include <assert.h>

#define UNUSED(x) (void)x

namespace Export {
	void Save(const FbxConverter & importer, const char* path) {
		FileHandle file;
		FileError error;

		UNUSED(importer);

		error = File::open(file, path, FILE_WRITE);
		assert(error != FILE_OPEN_FAIL);

		// write vertices header
		// write vertices

		// write normals header
		// write normals

		// write triangles header
		// write triangles

		error = File::close(file);
		assert(error != FILE_CLOSE_FAIL);
	}

	void Print(const FbxConverter & importer) {
		printf("\nVertices\n");
		for(unsigned int i = 0; i < importer.GetVertices().size(); i++) {
			const Vector & v = importer.GetVertices()[i];
			printf("i: %u x: %f y: %f z: %f \n", i, v.x, v.y, v.z);
		}

		printf("\nNormals\n");
		for(unsigned int i = 0; i < importer.GetNormals().size(); i++) {
			const Vector & v = importer.GetNormals()[i];
			printf("i: %u nx: %f ny: %f nz: %f \n", i, v.x, v.y, v.z);
		}

		printf("\nTriangles\n");
		for(unsigned int i = 0; i < importer.GetTriangles().size(); i++) {
			const Triangle & t = importer.GetTriangles()[i];
			printf("i: %u a: %u b: %u c: %u \n", i, t.a, t.b, t.c);
		}
	}
}