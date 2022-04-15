option(AQUA_BUILD_EDITOR "Build the Aqua Editor" ON)
option(AQUA_BUILD_BASE_GAME "Build the base game application" ON)

if(WIN32)
	set(EXECUTABLE_RESOURCES ${CMAKE_SOURCE_DIR}/CMake/Windows/AppIcon.rc)
else()
	set(EXECUTABLE_RESOURCES "")
endif()

# Base Game
if(AQUA_BUILD_BASE_GAME)
	add_subdirectory(BaseGame)
	set_target_properties(BaseGame PROPERTIES FOLDER "Apps")
endif()

# Editor
if(AQUA_BUILD_EDITOR)
	add_subdirectory(Editor)
	set_target_properties(AquaEditor PROPERTIES FOLDER "Apps")
endif()
