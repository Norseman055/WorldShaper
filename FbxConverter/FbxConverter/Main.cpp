
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