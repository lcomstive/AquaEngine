# Flecs
add_subdirectory(Vendor/flecs)
set_target_properties(flecs PROPERTIES FOLDER "Vendor") # Assign folders in solution explorer

# Aqua Engine Core
project(AquaEngineCore)
file(GLOB_RECURSE SOURCE_FILES  "Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "Include/*.hpp")

add_library(AquaEngineCore SHARED ${SOURCE_FILES} ${HEADER_FILES})

# Group source files inside IDE
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Source" FILES 
${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include" PREFIX "Include" 
FILES ${INCLUDE_FILES})

target_include_directories(AquaEngineCore PUBLIC
	Include
	Vendor/flecs/include
	Vendor/spdlog/include
	Vendor/cereal/include
)

target_link_libraries(AquaEngineCore PUBLIC
	flecs
)

