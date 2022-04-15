project(BaseGame)
file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES Include/*.hpp)
file(GLOB_RECURSE COMMON_INCLUDE_FILES ${CMAKE_SOURCE_DIR}/Apps/Common/Include/*.hpp)

file(GLOB_RECURSE COMMON_SOURCE_FILES
	${CMAKE_SOURCE_DIR}/Apps/Common/Source/*.c
	${CMAKE_SOURCE_DIR}/Apps/Common/Source/*.cpp
)

if(APPLE)
	file(GLOB_RECURSE COMMON_MM_SOURCE_FILES ${CMAKE_SOURCE_DIR}/Apps/Common/Source/*.mm)
	list(APPEND COMMON_SOURCE_FILES ${COMMON_MM_SOURCE_FILES})
endif()

add_executable(${PROJECT_NAME}
	${SOURCE_FILES}
	${HEADER_FILES}
	${COMMON_SOURCE_FILES}
	${COMMON_HEADER_FILES}
	${EXECUTABLE_RESOURCES}
)

if(WIN32)
	set_target_properties(${PROJECT_NAME} PROPERTIES
		LINK_FLAGS_DEBUG   			"/SUBSYSTEM:CONSOLE"
		LINK_FLAGS_RELEASE 			"/SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup"
		LINK_FLAGS_MINSIZEREL 		"/SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup"
		LINK_FLAGS_RELWITHDEBINFO 	"/SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup"
	)
endif()

# Group source files inside IDE
source_group("Resources" FILES ${EXECUTABLE_RESOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Source" FILES ${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include" PREFIX "Include" FILES ${INCLUDE_FILES})
source_group(TREE "${CMAKE_SOURCE_DIR}/Apps/Common/Include" PREFIX "Include/Common" FILES ${COMMON_INCLUDE_FILES})
source_group(TREE "${CMAKE_SOURCE_DIR}/Apps/Common/Source" PREFIX "Source/Common" FILES ${COMMON_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
	Include
	${CMAKE_SOURCE_DIR}/Engine/Include
	${CMAKE_SOURCE_DIR}/Apps/Common/Include/
	${CMAKE_SOURCE_DIR}/Apps/Common/Include/BGFXEntry/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	AquaEngine
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	_CRT_SECURE_NO_WARNINGS
	__STDC_FORMAT_MACROS
)
