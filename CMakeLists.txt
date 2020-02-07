cmake_minimum_required( VERSION 3.5 )

project( blokus )

# -DSPDLOG_COMPILED_LIB needed for spdlog to use static lib instead of headers only
set( CMAKE_CXX_FLAGS " -g -Wall -Wextra -O2 -Wl,--no-as-needed -fPIC -std=c++17 -DSPDLOG_COMPILED_LIB " )
# set( CMAKE_CXX_FLAGS " -O2 -Wl,--no-as-needed -fPIC -std=c++17 -DSPDLOG_COMPILED_LIB " )

include_directories( ${CMAKE_STAGING_PREFIX}/usr/include )
link_directories( ${CMAKE_STAGING_PREFIX}/usr/lib )

# ===================================================================================
include(FindProtobuf REQUIRED ${PROTOBUF_ROOT})

EXECUTE_PROCESS(COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf blokus.proto
RESULT_VARIABLE rv)
# Optional, but that can show the user if something have gone wrong with the proto generation 
IF(${rv})
    MESSAGE("Generation of data model returned ${rv} for proto ${proto_native}")
ENDIF()
# ===================================================================================

# add_subdirectory( examples )

set ( src_blokus
      src/Message.cpp
      src/MessageBase.cpp
      src/protobuf/blokus.pb.cc
      src/Task.cpp
      src/TaskProcessor.cpp
      src/ActiveGame.cpp
      src/ActiveGameManager.cpp
      src/Game.cpp
      src/FindGame.cpp
      src/RegisterForGame.cpp
      src/StartGame.cpp
      src/StartGameRequest.cpp
      src/StartGameRequestData.cpp
      src/GameNotification.cpp
      src/ReadGameNotification.cpp
      src/Register.cpp
      src/RegisterResponse.cpp
      src/Network.cpp
      src/PlayerManager.cpp
      src/Player.cpp
      src/PieceMove.cpp
      src/PlayerSelectedPiece.cpp
      src/BuildGamePieces.cpp
      src/PiecesAvailableForPlayLocations.cpp
      src/PieceSelector.cpp
      src/Board.cpp
      src/GameBoard.cpp
      src/GamePieceBank.cpp
      src/OverlayBoard.cpp
      src/Layout.cpp
      src/Piece.cpp
      src/MoveablePiece.cpp
      src/Padding.cpp
      src/Point.cpp
      src/MessageProcessor.cpp
      src/GameScreen.cpp
      src/StartScreen.cpp
      src/GameLobby.cpp
      src/GameLobbyScreen.cpp
      src/StartGameLobbyScreen.cpp
      src/PlayerMoveRequest.cpp
      src/PlayerMoveRequestData.cpp
      src/ProcessPlayerMove.cpp
      src/RandomizePlayerIds.cpp
      src/PlayerTurnManager.cpp
      src/InitialMoveIndicator.cpp
      src/PlayerScores.cpp
      src/ChatRoom.cpp
      src/ProcessChatMessage.cpp
      src/ChatRequest.cpp
      src/ChatRequestData.cpp
      src/main.cpp
)

add_executable( ${PROJECT_NAME} ${src_blokus} )

target_include_directories( ${PROJECT_NAME} PRIVATE interface )
target_include_directories( ${PROJECT_NAME} PRIVATE include )
target_include_directories( ${PROJECT_NAME} PRIVATE src )

# GRAPHCIS
target_link_libraries( ${PROJECT_NAME} raylib )
target_link_libraries( ${PROJECT_NAME} glfw3 )
target_link_libraries( ${PROJECT_NAME} rt )
target_link_libraries( ${PROJECT_NAME} pthread )

target_link_libraries( ${PROJECT_NAME} m )
target_link_libraries( ${PROJECT_NAME} dl )
target_link_libraries( ${PROJECT_NAME} X11 )

target_link_libraries( ${PROJECT_NAME} GL )
target_link_libraries( ${PROJECT_NAME} GLU )

# NETWORKING
target_link_libraries( ${PROJECT_NAME} zyre )
target_link_libraries( ${PROJECT_NAME} czmq )
target_link_libraries( ${PROJECT_NAME} zmq )

# MESSAGING
target_link_libraries( ${PROJECT_NAME} ${Protobuf_LIBRARIES} )

# LOGGING
target_link_libraries( ${PROJECT_NAME} spdlog )

set ( src_blokus_test
      src/Board.cpp
      src/GameBoard.cpp
      src/OverlayBoard.cpp
      src/Layout.cpp
      src/Piece.cpp
      src/MoveablePiece.cpp
      src/Padding.cpp
      src/Point.cpp
      src/Task.cpp
      src/GameNotification.cpp
      src/ReadGameNotification.cpp
      src/PieceSelector.cpp
      src/Game.cpp
      src/PlayerTurnManager.cpp
      src/BuildGamePieces.cpp
      src/GamePieceBank.cpp
      src/ChatRoom.cpp
      test/TestSuiteSetup.cpp
      test/TestSuiteCalculatePadding.cpp
      test/TestSuitePieceSelector.cpp
      test/TestSuiteTask.cpp
      test/TestSuiteReadGameNotification.cpp
      test/TestSuitePiece.cpp
      test/TestSuiteMoveablePiece.cpp
      test/TestSuiteLayout.cpp
      test/TestSuitePadding.cpp
      test/TestSuitePlayerTurnManager.cpp
      test/TestSuiteGamePieceBank.cpp
      test/TestSuiteChatRoom.cpp
)

add_executable( test_blokus ${src_blokus_test} )

target_include_directories( test_blokus PRIVATE interface )
target_include_directories( test_blokus PRIVATE include )

target_link_libraries( test_blokus gtest )
target_link_libraries( test_blokus gtest_main )
target_link_libraries( test_blokus gmock )

# LOGGING
target_link_libraries( test_blokus spdlog )

target_link_libraries( test_blokus pthread )