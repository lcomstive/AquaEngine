cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules ${CMAKE_MODULE_PATH})

project(AquaEngine)

# Engine Core
add_subdirectory(Core)

# Base Game
add_subdirectory(BaseGame)

# Get the engine version from the git tag
include(GetGitRevisionDescription)
git_describe(VERSION --tags --dirty=-d)

#parse the version information into pieces.
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" AQUA_ENGINE_VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" AQUA_ENGINE_VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" AQUA_ENGINE_VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" AQUA_ENGINE_VERSION_SHA1 "${VERSION}")
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

add_definitions(-DAQUA_ENGINE_VERSION_MAJOR=${AQUA_ENGINE_VERSION_MAJOR})
add_definitions(-DAQUA_ENGINE_VERSION_MINOR=${AQUA_ENGINE_VERSION_MINOR})
add_definitions(-DAQUA_ENGINE_VERSION_PATCH=${AQUA_ENGINE_VERSION_PATCH})
add_definitions(-DAQUA_ENGINE_VERSION_SHA1=${AQUA_ENGINE_VERSION_SHA1})
