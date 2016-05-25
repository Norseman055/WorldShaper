/// This converter class and almost every method in it is written by Vitor Fernandes. While some modifications may
/// have been made to a few of the functions, the majority of these functions are either direct copies or very close copies
/// of his work. All credit goes to him for this converter and the functionality therein. It has been modified for use
/// with my game engine, but is in no way work attributable to me.

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