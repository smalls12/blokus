#include <iostream>

#include "gtest/gtest.h"

#include "mock/MNetworkReceive.hpp"

#include "ReadGameNotification.hpp"

using testing::_;
using ::testing::Invoke;

class TestSuiteReadGameNotification : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuiteReadGameNotification() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuiteReadGameNotification() {
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
TEST_F(TestSuiteReadGameNotification, Constructor)
{
    MNetworkReceive mock;
	std::string gameName("test");
    ReadGameNotification rgn(mock, gameName);
}

TEST_F(TestSuiteReadGameNotification, JoinMessage)
{
    MNetworkReceive mock;
	std::string gameName("test");
    ReadGameNotification rgn(mock, gameName);	

	EXPECT_CALL( mock, Receive(_,_) )
	.WillOnce( Invoke( [](std::string groupName, std::vector<std::string>& messages) {
		messages.push_back( std::string("test_name") );
		messages.push_back( std::string("test_uuid") );
		messages.push_back( std::string("JOIN") );
		messages.push_back( std::string("") );

		return true;
	} ) );
	// .WillByDefault(testing::Return(message));

	GameNotification gm;
	EXPECT_TRUE( rgn.Receive(gm) );

	EXPECT_TRUE( gm.getName() == "test_name" );
	EXPECT_TRUE( gm.getUuid() == "test_uuid" );
	EXPECT_TRUE( gm.getType() == NotificationType::JOIN );
	EXPECT_TRUE( gm.getData() == "" );

}

// }  // namespace - could surround Project1Test in a namespace