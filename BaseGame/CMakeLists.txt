project(BaseGame)
file(GLOB_RECURSE SOURCE_FILES  "Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "Include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Group source files inside IDE
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Source" FILES ${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include" PREFIX "Include" FILES ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
	Include
	../Core/Include
)

target_link_libraries(${PROJECT_NAME} PRIVATE AquaEngineCore)
