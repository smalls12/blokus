cmake_minimum_required( VERSION 3.5 )

project( blokus )

# -DSPDLOG_COMPILED_LIB needed for spdlog to use static lib instead of headers only
set( CMAKE_CXX_FLAGS " -g -Wall -Wextra -O2 -Wl,--no-as-needed -fPIC -std=c++17 -DSPDLOG_COMPILED_LIB " )

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

set( src_blokus_threading
     src/Task.cpp
     src/TaskProcessor.cpp
)

add_library( ${PROJECT_NAME}_threading OBJECT ${src_blokus_threading} )

target_include_directories( ${PROJECT_NAME}_threading PRIVATE include )

set( src_blokus_networking
     src/ActiveGame.cpp
     src/ActiveGameManager.cpp
     src/ProcessEvent.cpp
     src/Game.cpp
     src/JoinLobby.cpp
     src/StartGame.cpp
     src/FindGame.cpp
     src/JoinGame.cpp
     src/RegisterForGame.cpp
     src/BroadcastPlayerMove.cpp
     src/GameNotification.cpp
     src/ReadGameNotification.cpp
     src/WaitForServerNode.cpp
     src/RegisterResponse.cpp
     src/NetworkConnection.cpp
)

add_library( ${PROJECT_NAME}_networking OBJECT ${src_blokus_networking} )

target_include_directories( ${PROJECT_NAME}_networking PRIVATE include )
target_include_directories( ${PROJECT_NAME}_networking PRIVATE src )

set( src_blokus_protobuf
     src/Message.cpp
     src/protobuf/blokus.pb.cc
)

add_library( ${PROJECT_NAME}_protobuf OBJECT ${src_blokus_protobuf} )

target_include_directories( ${PROJECT_NAME}_protobuf PRIVATE include )
target_include_directories( ${PROJECT_NAME}_protobuf PRIVATE src )

set ( src_blokus
      src/PlayerManager.cpp
      src/Player.cpp
      src/PieceMove.cpp
      src/Board.cpp
      src/GameBoard.cpp
      src/OverlayBoard.cpp
      src/Layout.cpp
      src/Piece.cpp
      src/Padding.cpp
      src/Point.cpp
      src/MessageProcessor.cpp
      src/GameScreen.cpp
      src/StartScreen.cpp
      src/GameLobbyScreen.cpp
      src/main.cpp
)

add_executable( ${PROJECT_NAME} ${src_blokus}
$<TARGET_OBJECTS:${PROJECT_NAME}_threading>
$<TARGET_OBJECTS:${PROJECT_NAME}_networking>
$<TARGET_OBJECTS:${PROJECT_NAME}_protobuf>
)

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
      src/Padding.cpp
      src/Point.cpp
      src/Task.cpp
      test/TestSuiteCalculatePadding.cpp
      test/TestSuiteTask.cpp
)

add_executable( test_blokus ${src_blokus_test} )

target_include_directories( test_blokus PRIVATE include )

target_link_libraries( test_blokus gtest )
target_link_libraries( test_blokus gtest_main )

# LOGGING
target_link_libraries( test_blokus spdlog )

target_link_libraries( test_blokus pthread )