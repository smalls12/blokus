# blokus

## How It Works
When the game is launched, the user will be able to either start a game or join one that has already been started and is waiting for more players.

Once enough players have joined a game, the leader can start the game at which point all connected players will be informed to the start of the game.

Players will take turns laying down pieces in accordance with the game rules ( not described here ).

## High Level Design
Built in C++ with the following open source libraries:
1. Networking implemented with zyre ( https://github.com/zeromq/zyre )
2. Messaging between players implemented with protobuf ( https://github.com/protocolbuffers/protobuf )
3. GUI implemented with raylib and raygui ( https://github.com/raysan5/raylib and https://github.com/raysan5/raygui )

## Supported Platforms
All over these libraries are cross platform and should run on x86, ARM, macOS and Windows.</br>
At this point, only working on x86.

## Lower Level Design
The games networking is provided by the zyre library which runs on zeromq.
zyre is used to create virtual networks between networked nodes.

Once a game has begun, messages are exchanged over the zyre network.
The messages are generated with protobuf and indicate the start of a game, player moves, and chat messages.
