/// This converter class and almost every method in it is written by Vitor Fernandes. While some modifications may
/// have been made to a few of the functions, the majority of these functions are either direct copies or very close copies
/// of his work. All credit goes to him for this converter and the functionality therein. It has been modified for use
/// with my game engine, but is in no way work attributable to me.

#include "Export.h"
#include "FbxConverter.h"
#include "Structures.h"
#include <stdio.h>
#include <algorithm>
#include <assert.h>

namespace Export {
	void Save(const FbxConverter & importer, const char* path) {
		FileHandle file;
		FileError error;

		std::string fullPath = std::string(path) + std::string(".model");
		printf("Writing to file: %s \n", fullPath.c_str());

		// open file
		printf("Opening file... ");
		error = File::open(file, fullPath.c_str(), FILE_WRITE);
		if(error != FILE_OPEN_FAIL) {
			printf("Success!\n");
		} else {
			printf("FAILURE!\n");
			CloseFile(file);
			exit(EXIT_FAILURE);
		}
		
		// make vertices header
		VerticesHeader verticesHeader;
		verticesHeader.numVertices = importer.GetVertices().size();
		verticesHeader.dataSize = verticesHeader.numVertices * sizeof(Vector);
		printf("Vertex data:\n");
		printf("Num vertices: %i\n", verticesHeader.numVertices);
		printf("Data size: %i\n", verticesHeader.dataSize);
		// make normals header
		NormalHeader normalHeader;
		normalHeader.numNormals = importer.GetNormals().size();
		normalHeader.dataSize = normalHeader.numNormals * sizeof(Vector);
		printf("Normal data:\n");
		printf("Num normals: %i\n", normalHeader.numNormals);
		printf("Data size: %i\n", normalHeader.dataSize);
		// make triangles header
		TriangleHeader triangleHeader;
		triangleHeader.numTriangles = importer.GetTriangles().size();
		triangleHeader.dataSize = triangleHeader.numTriangles * sizeof(Triangle);
		printf("Triangle data:\n");
		printf("Num triangles: %i\n", triangleHeader.numTriangles);
		printf("Data size: %i\n", triangleHeader.dataSize);
		// make skeleton header
		SkeletonHeader skeletonHeader;
		skeletonHeader.numBones = importer.GetSkeleton().size();
		skeletonHeader.dataSize = skeletonHeader.numBones * sizeof(Bone);
		printf("Skeleton data:\n");
		printf("Num bones: %i\n", skeletonHeader.numBones);
		printf("Data size: %i\n", skeletonHeader.dataSize);
		// make model file header
		ModelFileHeader modelHeader;
		modelHeader.sizeofModelData = 
			sizeof(verticesHeader) + verticesHeader.dataSize 
			+ sizeof(normalHeader) + normalHeader.dataSize 
			+ sizeof(triangleHeader) + triangleHeader.dataSize
			+ sizeof(skeletonHeader) + skeletonHeader.dataSize;
		int filenameLen = strlen(path);
		if(filenameLen < 24) {
			memcpy(modelHeader.modelName, path, filenameLen);
			modelHeader.modelName[filenameLen] = '\0';
		} else {
			memcpy(modelHeader.modelName, path, 23);
			modelHeader.modelName[23] = '\0';
		}
	
		// write file header
		printf("Writing file header... ");
		error = File::write(file, reinterpret_cast<const char* const>(&modelHeader), sizeof(ModelFileHeader));
		if(error == FILE_WRITE_FAIL) {
			printf("FAILURE!\n");
			CloseFile(file);
			exit(EXIT_FAILURE);
		}
		printf("Success!\n");

		// write vertices
		printf("Writing vertices to file... ");
		error = File::write(file, reinterpret_cast<const char* const>(&verticesHeader), sizeof(VerticesHeader));
		if(error == FILE_WRITE_FAIL) {
			printf("FAILURE!\n");
			CloseFile(file);
			exit(EXIT_FAILURE);
		}
		for(const Vector& vertex : importer.GetVertices()) {
			error = File::write(file, reinterpret_cast<const char* const>(&vertex), sizeof(Vector));
			if(error == FILE_WRITE_FAIL) {
				printf("FAILURE!\n");
				CloseFile(file);
				exit(EXIT_FAILURE);
			}
		}
		printf("Success!\n");

		// write normals
		printf("Writing normals to file... ");
		error = File::write(file, reinterpret_cast<const char* const>(&normalHeader), sizeof(NormalHeader));
		if(error == FILE_WRITE_FAIL) {
			printf("FAILURE!\n");
			CloseFile(file);
			exit(EXIT_FAILURE);
		}
		for(const Vector& vertex : importer.GetNormals()) {
			error = File::write(file, reinterpret_cast<const char* const>(&vertex), sizeof(Vector));
			if(error == FILE_WRITE_FAIL) {
				printf("FAILURE!\n");
				CloseFile(file);
				exit(EXIT_FAILURE);
			}
		}
		printf("Success!\n");

		// write triangles
		printf("Writing triangles to file... ");
		error = File::write(file, reinterpret_cast<const char* const>(&triangleHeader), sizeof(TriangleHeader));
		if(error == FILE_WRITE_FAIL) {
			printf("FAILURE!\n");
			CloseFile(file);
			exit(EXIT_FAILURE);
		}
		for(const Triangle& triangle : importer.GetTriangles()) {
			error = File::write(file, reinterpret_cast<const char* const>(&triangle), sizeof(Triangle));
			if(error == FILE_WRITE_FAIL) {
				printf("FAILURE!\n");
				CloseFile(file);
				exit(EXIT_FAILURE);
			}
		}
		printf("Success!\n");

		// write skeleton heirarchy
		printf("Writing skeleton to file... ");
		error = File::write(file, reinterpret_cast<const char* const>(&skeletonHeader), sizeof(SkeletonHeader));
		if(error == FILE_WRITE_FAIL) {
			printf("FAILURE!\n");
			CloseFile(file);
			exit(EXIT_FAILURE);
		}
		for(const Bone& bone : importer.GetSkeleton()) {
			error = File::write(file, reinterpret_cast<const char* const>(&bone), sizeof(Bone));
			if(error == FILE_WRITE_FAIL) {
				printf("FAILURE!\n");
				CloseFile(file);
				exit(EXIT_FAILURE);
			}
		}
		printf("Success!\n");

		CloseFile(file);
	}

	void Print(const FbxConverter & importer) {
		printVerts(importer);
		printNorms(importer);
		printTris(importer);
		printSkeleton(importer);
	}

	void printVerts(const FbxConverter& importer) {
		printf("\nVertices\n");
		for(unsigned int i = 0; i < importer.GetVertices().size(); i++) {
			const Vector & v = importer.GetVertices()[i];
			printf("i: %u x: %f y: %f z: %f \n", i, v.x, v.y, v.z);
		}
	}

	void printNorms(const FbxConverter& importer) {
		printf("\nNormals\n");
		for(unsigned int i = 0; i < importer.GetNormals().size(); i++) {
			const Vector & v = importer.GetNormals()[i];
			printf("i: %u nx: %f ny: %f nz: %f \n", i, v.x, v.y, v.z);
		}
	}

	void printTris(const FbxConverter& importer) {
		printf("\nTriangles\n");
		for(unsigned int i = 0; i < importer.GetTriangles().size(); i++) {
			const Triangle & t = importer.GetTriangles()[i];
			printf("i: %u a: %u b: %u c: %u \n", i, t.a, t.b, t.c);
		}
	}

	void printSkeleton(const FbxConverter& importer) {
		printf("\nSkeleton\n");
		for(unsigned int i = 0; i < importer.GetSkeleton().size(); i++) {
			const Bone & b = importer.GetSkeleton()[i];
			printf("%i: ", i);
			for(unsigned int i = 0; i < b.level; i++) {
				printf(" ");
			}
			printf("%s \tParent: %i", b.boneName, b.parentIndex);
			if(b.parentIndex >= 0) {
				printf(" (%s)", importer.GetSkeleton()[b.parentIndex].boneName);
			}
			printf("\n");
		}
	}

	void CloseFile(FileHandle& file) {
		FileError error;

		// close file
		printf("Closing file... ");
		error = File::close(file);
		if(error != FILE_CLOSE_FAIL) {
			printf("Success!\n");
		} else {
			printf("FAILURE!\n");
			exit(EXIT_FAILURE);
		}
	}
}