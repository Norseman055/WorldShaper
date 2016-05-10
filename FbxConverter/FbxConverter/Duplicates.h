#ifndef DUPLICATES_H
#define DUPLICATES_H

#include "FbxConverter.h"
#include "Structures.h"
#include <unordered_map>

namespace Duplicates {
	struct Vertex {
		Vector position;
		Vector normal;

		const bool operator==(const Vertex & other) const;
	};

	struct Hash {
		const std::size_t operator()(const Vertex & key) const;
	};

	struct Report {
		unsigned int vertexCount;
		unsigned int uniqueCount;
		unsigned int minRepetition;
		unsigned int maxRepetition;
	};

	using Map = std::unordered_map<Vertex, unsigned int, Hash>;
	const Report GetDuplicates(const FbxConverter & converter);
};

#endif