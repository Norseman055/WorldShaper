/// This converter class and almost every method in it is written by Vitor Fernandes. While some modifications may
/// have been made to a few of the functions, the majority of these functions are either direct copies or very close copies
/// of his work. All credit goes to him for this converter and the functionality therein. It has been modified for use
/// with my game engine, but is in no way work attributable to me.

#include <stdio.h>
#include "FbxConverter.h"
#include "Duplicates.h"
#include "Export.h"

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("Invalid number of arguments. Enter input and output files.");
		return EXIT_FAILURE;
	} else {
		FbxConverter converter;
		converter.Import(argv[1]);

		Duplicates::Report report = Duplicates::GetDuplicates(converter);
		printf("Total vertices:  %i \n", report.vertexCount);
		printf("Unique vertices: %i \n", report.uniqueCount);
		printf("Min repetitions: %i \n", report.minRepetition);
		printf("Max repetitions: %i \n", report.maxRepetition);

		if(argc > 2) {
			Export::Save(converter, argv[2]);
			printf("Exported to %s \n", argv[2]);
		} else {
			Export::Print(converter);
		}
	}

	system("PAUSE");
	return EXIT_SUCCESS;
}