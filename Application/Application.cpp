#include <stdlib.h>

#include <WorldShaper.h>

int main() {
	try {
		WorldShaper::Run();
		return EXIT_SUCCESS;
	} catch(...) {
		printf("Exception while running WorldShaper engine!");
		system("PAUSE");
		return EXIT_FAILURE;
	}
}