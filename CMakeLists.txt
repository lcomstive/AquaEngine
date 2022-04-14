cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

# Get the engine version from Version.txt & git revision
include(VersionInfo)

### ENGINE
project(AquaEngine)
add_subdirectory(Engine)

### APPS
# Base Game
add_subdirectory(Apps/BaseGame)

# Editor
add_subdirectory(Apps/Editor)