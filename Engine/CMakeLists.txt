# Flecs
set(FLECS_SHARED_LIBS OFF CACHE BOOL "")
add_subdirectory(Vendor/flecs)

# BGFX
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(Vendor/bgfx.cmake)

# Assign folders in solution explorer
if(FLECS_SHARED_LIBS)
	set_target_properties(flecs PROPERTIES FOLDER "Vendor")
endif()
if(FLECS_STATIC_LIBS)
	set_target_properties(flecs_static PROPERTIES FOLDER "Vendor")
endif()

# Aqua Engine Core
project(AquaEngine)
file(GLOB_RECURSE SOURCE_FILES  "Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "Include/*.hpp")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(
	${PROJECT_NAME} PROPERTIES
	VERSION ${VERSION_STRING}
)

# Group source files inside IDE
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Source" FILES ${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include" PREFIX "Include" FILES ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
	Include
	Vendor/flecs/include
	Vendor/spdlog/include
	Vendor/cereal/include
	Vendor/bgfx.cmake/bgfx/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	flecs_static
	
	# BGFX
	bx
	bimg 
	bgfx
	dear-imgui
	meshoptimizer
)

if(UNIX AND NOT APPLE AND NOT ANDROID)
	target_link_libraries(${PROJECT_NAME} PUBLIC X11)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC BUILD_SHARED_LIBS)
target_compile_definitions(${PROJECT_NAME} PRIVATE AQUA_ENGINE_EXPORT_DLL)

if(NOT WIN32)
	include(GNUInstallDirs)

	install(
		TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
endif()
