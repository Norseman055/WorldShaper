#include "ArchiveManager.h"
#include "File\File.h"

#include "Macros.h"
#include "ArchiveStructures.h"
#include "ModelManager.h"
#include "AnimationManager.h"

void ArchiveManager::Startup() {
	printf("\n===== Starting Archive Manager =====\n");
	GetInstance();
	LoadModelFromFile("../_archives/humanoid2.model");
	printf("===== Archive Manager started =====\n\n");
}

void ArchiveManager::Shutdown() {
	DestroyInstance();
}

void ArchiveManager::LoadModelFromFile(const char* filename) {
	printf("  Loading model from %s... \n", filename);
	char* buffer;
	
	FileHandle file;
	FileError error;

	// Open file
	printf("    Opening file... ");
	error = File::open(file, filename, FILE_READ);
	if(error != FILE_SUCCESS) {
		printf(" Failed!\n");
	} else {
		ModelFileHeader fileHeader;
		error = File::read(file, &fileHeader, sizeof(fileHeader));
		if(error != FILE_SUCCESS) {
			printf(" Failed to read file header!\n");
		} else {
			buffer = new char[fileHeader.sizeofModelData + sizeof(fileHeader)];
			error = File::read(file, buffer, fileHeader.sizeofModelData + sizeof(fileHeader));
			if(error != FILE_SUCCESS) {
				printf(" Failed to read file into buffer!\n");
			} else {
				printf(" Success! \n    Closing file and sending to ModelManager to load.\n");
				CloseFile(file);
				ModelManager::LoadModelFromBuffer(fileHeader, buffer);
				AnimationManager::LoadAnimationFromBuffer(fileHeader, buffer);
			}
		}
	}
}

void ArchiveManager::CloseFile(void* file) {
	FileError error;

	// Close file
	printf("    Closing file... ");
	error = File::close(file);
	if(error == FILE_SUCCESS) {
		printf(" Success!\n");
	} else {
		printf(" Failed! Could not close file!\n");
	}
}