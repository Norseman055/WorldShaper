//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "UnitTest.h"

//---------------------------------------------------------------------------
// MAIN METHOD:
//---------------------------------------------------------------------------
int main() {
	// Do NOT change anything!
	UnitTest_platform_init();

	const int numFailures = UnitTest_platform_runTests();

	UnitTest_platform_exit();
	return(numFailures);
}