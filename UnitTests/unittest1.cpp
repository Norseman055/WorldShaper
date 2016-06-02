#include "CppUnitTest.h"
#include "TESTING.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests {
	TEST_CLASS(UnitTest1) {
public:

	TEST_METHOD(TestMethod1) {
		// TODO: Your test code here
		Assert::AreEqual(1, 1);
	}
	};
}