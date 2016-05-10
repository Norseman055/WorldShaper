#include "Duplicates.h"
#include <functional>

namespace Duplicates {
	const bool Vertex::operator==(const Vertex & other) const {
		return this->position.x == other.position.x &&
			this->position.y == other.position.y &&
			this->position.z == other.position.z &&
			this->normal.x == other.normal.x &&
			this->normal.y == other.normal.y &&
			this->normal.z == other.normal.z;
	}

	const std::size_t Hash::operator()(const Vertex & key) const {
		size_t result = std::hash<float>()(key.position.x);
		result <<= 1;
		result ^= std::hash<float>()(key.position.y);
		result <<= 1;
		result ^= std::hash<float>()(key.position.z);
		result <<= 1;
		result ^= std::hash<float>()(key.normal.x);
		result <<= 1;
		result ^= std::hash<float>()(key.normal.y);
		result <<= 1;
		result ^= std::hash<float>()(key.normal.z);

		return result;
	}

	const Report GetDuplicates(const FbxConverter & converter) {
		auto vertices = converter.GetVertices();
		auto normals = converter.GetNormals();

		Report result;
		result.vertexCount = vertices.size();
		Map map;

		Vertex* combined = new Vertex[result.vertexCount];
		for(unsigned int i = 0; i < result.vertexCount; i++) {
			combined[i].position = vertices[i];
			combined[i].normal = normals[i];
			map[combined[i]]++;
		}
		delete[] combined;

		result.minRepetition = result.vertexCount;
		result.maxRepetition = 0;
		result.uniqueCount = map.size();

		for(const auto & item : map) {
			if(result.maxRepetition < item.second) {
				result.maxRepetition = item.second;
			} else if(result.minRepetition > item.second) {
				result.minRepetition = item.second;
			}
		}

		return result;
	}
};