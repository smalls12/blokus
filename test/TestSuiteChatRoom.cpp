#include <iostream>

#include "gtest/gtest.h"

#include "ChatRoom.hpp"

class TestSuiteChatRoom : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	TestSuiteChatRoom() {
		// You can do set-up work for each test here.
	}

	virtual ~TestSuiteChatRoom() {
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
TEST_F(TestSuiteChatRoom, Constructor)
{
    ChatRoom chatRoom(1);
}

TEST_F(TestSuiteChatRoom, AddMessage)
{
    ChatRoom chatRoom(1);
    chatRoom.AddMessage("adam", "hi");
}

TEST_F(TestSuiteChatRoom, VerifyAddingMessage)
{
    ChatRoom chatRoom(1);
    chatRoom.AddMessage("adam", "hi");

    BlokusChatMessages verifyMessages;
    verifyMessages.swap(chatRoom.GetMessages());

    EXPECT_TRUE(verifyMessages.front().first == "adam");
    EXPECT_TRUE(verifyMessages.front().second == "hi");
}

TEST_F(TestSuiteChatRoom, ConfirmMaxMessages_AtMax)
{
    ChatRoom chatRoom(3);
    chatRoom.AddMessage("adam", "hi");
    chatRoom.AddMessage("dee", "blah");
    chatRoom.AddMessage("shaine", "ugh");

    BlokusChatMessages verifyMessages;
    verifyMessages.swap(chatRoom.GetMessages());

    EXPECT_TRUE(verifyMessages.front().first == "adam");
    EXPECT_TRUE(verifyMessages.front().second == "hi");

    verifyMessages.pop_front();

    EXPECT_TRUE(verifyMessages.front().first == "dee");
    EXPECT_TRUE(verifyMessages.front().second == "blah");

    verifyMessages.pop_front();

    EXPECT_TRUE(verifyMessages.front().first == "shaine");
    EXPECT_TRUE(verifyMessages.front().second == "ugh");
}

TEST_F(TestSuiteChatRoom, ConfirmMaxMessages_OverMax)
{
    ChatRoom chatRoom(3);
    chatRoom.AddMessage("adam", "hi");
    chatRoom.AddMessage("dee", "blah");
    chatRoom.AddMessage("shaine", "ugh");
    chatRoom.AddMessage("noah", "wow");

    BlokusChatMessages verifyMessages;
    verifyMessages.swap(chatRoom.GetMessages());

    EXPECT_TRUE(verifyMessages.front().first == "dee");
    EXPECT_TRUE(verifyMessages.front().second == "blah");

    verifyMessages.pop_front();

    EXPECT_TRUE(verifyMessages.front().first == "shaine");
    EXPECT_TRUE(verifyMessages.front().second == "ugh");

    verifyMessages.pop_front();

    EXPECT_TRUE(verifyMessages.front().first == "noah");
    EXPECT_TRUE(verifyMessages.front().second == "wow");
}

// }  // namespace - could surround Project1Test in a namespace