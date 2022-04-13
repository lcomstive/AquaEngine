project(BaseGame)
file(GLOB_RECURSE SOURCE_FILES  "Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "Include/*.hpp")

add_executable(BaseGame ${SOURCE_FILES} ${HEADER_FILES})

# Group source files inside IDE
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Source" FILES 
${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include" PREFIX "Include" 
FILES ${INCLUDE_FILES})

target_include_directories(BaseGame PUBLIC
	Include
	../Core/Include
)

target_link_libraries(BaseGame PRIVATE AquaEngineCore)
