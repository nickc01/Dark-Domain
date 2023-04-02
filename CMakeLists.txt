cmake_minimum_required(VERSION 3.6)

project(DarkDomain VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin/${CMAKE_BUILD_TYPE}")

add_executable(${PROJECT_NAME} 
"src/Rooms/Base/Room.cpp"
"src/Rooms/BattleRoom.cpp"
"src/Rooms/CellRoom.cpp"
"src/Rooms/HallwayEndRoom.cpp"
"src/Rooms/HallwayRoom.cpp"
"src/Rooms/LargeDoorRoom.cpp"
"src/Rooms/OfficeRoom.cpp"
"src/Battle.cpp"
"src/gameFunctions.cpp"
"src/GameVariables.cpp"
"src/Inventory.cpp"
"src/main.cpp"
"include/Rooms/Base/Room.h"
"include/Rooms/BattleRoom.h"
"include/Rooms/CellRoom.h"
"include/Rooms/HallwayEndRoom.h"
"include/Rooms/HallwayRoom.h"
"include/Rooms/LargeDoorRoom.h"
"include/Rooms/OfficeRoom.h"
"include/Battle.h"
"include/gameEnums.h"
"include/gameFunctions.h"
"include/GameVariables.h"
"include/Inventory.h")

target_include_directories(${PROJECT_NAME} PUBLIC "include")


IF (NOT WIN32)
    add_subdirectory(lib/termcolor)
    target_link_libraries(${PROJECT_NAME} PUBLIC termcolor)
ENDIF()