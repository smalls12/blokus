#include "gtest/gtest.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef SPDLOG_ACTIVE_LEVEL
    #undef SPDLOG_ACTIVE_LEVEL
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif

class TestSuiteSetup : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuiteSetup() {
		// You can do set-up work for each test here.

		// create color multi threaded logger
		spdlog::set_level(spdlog::level::info); // Set global log level to info
		auto console = spdlog::stdout_color_mt("console");    
		auto err_logger = spdlog::stderr_color_mt("stderr");
	}

	virtual ~TestSuiteSetup() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Project1.
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(TestSuiteSetup, Nothing)
{
    // this is a hack
    // this test runs first
    // and the test suite setup will configure spdlog
}

// }  // namespace - could surround Project1Test in a namespace