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

		std::string fullPath = std::string(path) + std::string(".model");
		printf("Writing to file: %s \n", fullPath.c_str());

		// open file
		printf("Opening file... ");
		checkError(file, File::open(file, fullPath.c_str(), FILE_WRITE));
		printf("Success!\n");
		
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

		// make bind pose header
		BindPoseHeader bindPoseHeader;
		bindPoseHeader.numMatrices = importer.GetBindPose().size();
		bindPoseHeader.dataSize = bindPoseHeader.numMatrices * sizeof(Matrix);
		printf("Bind pose data:\n");
		printf("Num matrices: %i\n", bindPoseHeader.numMatrices);
		printf("Data size: %i\n", bindPoseHeader.dataSize);

		// make animations header
		AnimationHeader animationHeader;
		animationHeader.numAnimations = importer.GetAnimations().size();
		// need to update data size as we get size of animations dynamically
		int dataSize = 0; 
		for(const Animation& animation : importer.GetAnimations()) {
			dataSize += 16;
			dataSize += sizeof(int);
			for(const Keyframe& keyframe : animation.keyframes) {
				dataSize += (sizeof(TransformData) * keyframe.numTransforms);
				dataSize += sizeof(float);
				dataSize += sizeof(int);
			}
		}
		animationHeader.dataSize = dataSize;
		printf("Animation data:\n");
		printf("Num animations: %i\n", animationHeader.numAnimations);
		printf("Data size: %i\n", animationHeader.dataSize);

		// get top 4 influences for skin and normalize their weights
		std::vector< std::vector<SkinInfluence> > skinCopy = importer.GetSkin();
		for(std::vector<SkinInfluence> & vector : skinCopy) {
			auto compare = [](SkinInfluence lhs, SkinInfluence rhs) {
				return lhs.weight > rhs.weight;
			};
			std::sort(vector.begin(), vector.end(), compare);
			while(vector.size() < 4) {
				vector.push_back({ 0, 0.0f });
			}
			const float sum = vector[0].weight + vector[1].weight + vector[2].weight + vector[3].weight;
			vector[0].weight /= sum;
			vector[1].weight /= sum;
			vector[2].weight /= sum;
			vector[3].weight /= sum;
		}

		// make skin header
		SkinningHeader skinningHeader;
		skinningHeader.numInfluenceVectors = skinCopy.size();
		// need to update data size as we get size of skinning vectors dynamically
		dataSize = 0;
		for(const vector<SkinInfluence>& skinVector : skinCopy) {
			dataSize += skinVector.size() * sizeof(SkinInfluence);
		}
		skinningHeader.dataSize = dataSize;
		printf("Skin data:\n");
		printf("Num influence vectors: %i\n", skinningHeader.numInfluenceVectors);
		printf("Data size: %i\n", skinningHeader.dataSize);

		// make model file header
		ModelFileHeader modelHeader;
		modelHeader.sizeofModelData =
			sizeof(verticesHeader) + verticesHeader.dataSize
			+ sizeof(normalHeader) + normalHeader.dataSize
			+ sizeof(triangleHeader) + triangleHeader.dataSize
			+ sizeof(skeletonHeader) + skeletonHeader.dataSize
			+ sizeof(bindPoseHeader) + bindPoseHeader.dataSize
			+ sizeof(animationHeader) + animationHeader.dataSize
			+ sizeof(skinningHeader) + skinningHeader.dataSize;
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
		checkError(file, File::write(file, reinterpret_cast<const char* const>(&modelHeader), sizeof(ModelFileHeader)));
		printf("Success!\n");

		// write vertices
		printf("Writing vertices to file... ");
		checkError(file, File::write(file, reinterpret_cast<const char* const>(&verticesHeader), sizeof(VerticesHeader)));
		for(const Vector& vertex : importer.GetVertices()) {
			checkError(file, File::write(file, reinterpret_cast<const char* const>(&vertex), sizeof(Vector)));
		}
		printf("Success!\n");

		// write normals
		printf("Writing normals to file... ");
		checkError(file, File::write(file, reinterpret_cast<const char* const>(&normalHeader), sizeof(NormalHeader)));
		for(const Vector& vertex : importer.GetNormals()) {
			checkError(file, File::write(file, reinterpret_cast<const char* const>(&vertex), sizeof(Vector)));
		}
		printf("Success!\n");

		// write triangles
		printf("Writing triangles to file... ");
		checkError(file, File::write(file, reinterpret_cast<const char* const>(&triangleHeader), sizeof(TriangleHeader)));
		for(const Triangle& triangle : importer.GetTriangles()) {
			checkError(file, File::write(file, reinterpret_cast<const char* const>(&triangle), sizeof(Triangle)));
		}
		printf("Success!\n");

		// write skeleton hierarchy
		printf("Writing skeleton to file... ");
		checkError(file, File::write(file, reinterpret_cast<const char* const>(&skeletonHeader), sizeof(SkeletonHeader)));
		for(const Bone& bone : importer.GetSkeleton()) {
			checkError(file, File::write(file, reinterpret_cast<const char* const>(&bone), sizeof(Bone)));
		}
		printf("Success!\n");

		// write bind pose
		printf("Writing bind pose to file... ");
		checkError(file, File::write(file, reinterpret_cast<const char* const>(&bindPoseHeader), sizeof(BindPoseHeader)));
		for(const Matrix& matrix : importer.GetBindPose()) {
			checkError(file, File::write(file, reinterpret_cast<const char* const>(&matrix), sizeof(Matrix)));
		}
		printf("Success!\n");

		// write animations
		printf("Writing animations to file... ");
		checkError(file, File::write(file, reinterpret_cast<const char* const>(&animationHeader), sizeof(AnimationHeader)));
		for(const Animation& animation : importer.GetAnimations()) {
			checkError(file, File::write(file, animation.animName, 16));
			checkError(file, File::write(file, reinterpret_cast<const char* const>(&animation.numKeyframes), sizeof(int)));
			for(const Keyframe& keyframe : animation.keyframes) {
				checkError(file, File::write(file, reinterpret_cast<const char* const>(&keyframe.time), sizeof(float)));
				checkError(file, File::write(file, reinterpret_cast<const char* const>(&keyframe.numTransforms), sizeof(int)));
				for(const TransformData& transform : keyframe.boneTransforms) {
					checkError(file, File::write(file, reinterpret_cast<const char* const>(&transform), sizeof(TransformData)));
				}
			}
		}
		printf("Success!\n");

		// write skin
		printf("Writing skin to file...");
		checkError(file, File::write(file, reinterpret_cast<const char* const>(&skinningHeader), sizeof(SkinningHeader)));
		for(const vector<SkinInfluence>& vector : skinCopy) {
			for(int i = 0; i < 4; i++) {
				checkError(file, File::write(file, reinterpret_cast<const char* const>(&vector[i]), sizeof(vector[i])));
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
		printBindPose(importer);
		printAnimations(importer);
		printSkin(importer);
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
			for(int i = 0; i < b.level; i++) {
				printf(" ");
			}
			printf("%s \tParent: %i", b.boneName, b.parentIndex);
			if(b.parentIndex >= 0) {
				printf(" (%s)", importer.GetSkeleton()[b.parentIndex].boneName);
			}
			printf("\n");
		}
	}

	void printBindPose(const FbxConverter& converter) {
		printf("\nBind Pose\n");
		for(unsigned int i = 0; i < converter.GetBindPose().size(); i++) {
			const Matrix& m = converter.GetBindPose()[i];
			printf("%i:", i);
			printf("\t[ %f, %f, %f, %f ]\n", m.elements[0][0], m.elements[0][1], m.elements[0][2], m.elements[0][3]);
			printf("\t[ %f, %f, %f, %f ]\n", m.elements[1][0], m.elements[1][1], m.elements[1][2], m.elements[1][3]);
			printf("\t[ %f, %f, %f, %f ]\n", m.elements[2][0], m.elements[2][1], m.elements[2][2], m.elements[2][3]);
			printf("\t[ %f, %f, %f, %f ]\n\n", m.elements[3][0], m.elements[3][1], m.elements[3][2], m.elements[3][3]);
		}
	}

	void printAnimations(const FbxConverter& importer) {
		printf("\nAnimations\n");
		for(unsigned int i = 0; i < importer.GetAnimations().size(); i++) {
			const Animation& animation = importer.GetAnimations()[i];
			printf("%s:\tFrames: %i\tDuration: %fs\n", animation.animName, animation.numKeyframes, animation.keyframes.back().time);
		}
	}

	void printSkin(const FbxConverter& converter) {
		printf("\nSkin\n");
		for(unsigned int i = 0; i < converter.GetSkin().size(); i++) {
			printf("Skin vector %i:\t Size: %i\n", i, converter.GetSkin()[i].size());
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

	void checkError(FileHandle& file, const FileError error) {
		if(error != FILE_SUCCESS) {
			printf("FAILURE!\n");
			CloseFile(file);
			exit(EXIT_FAILURE);
		}
	}
}