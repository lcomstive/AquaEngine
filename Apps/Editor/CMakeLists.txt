project(AquaEditor)
file(GLOB_RECURSE SOURCE_FILES  "Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "Include/*.hpp")


if(WIN32)
	set(EXECUTABLE_RESOURCES ${CMAKE_SOURCE_DIR}/CMake/Windows/AppIcon.rc)
else()
	set(EXECUTABLE_RESOURCES "")
endif()

add_executable(
	${PROJECT_NAME}
	${SOURCE_FILES}
	${HEADER_FILES}
	${EXECUTABLE_RESOURCES}
)

# Group source files inside IDE
source_group("Resources" FILES ${EXECUTABLE_RESOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source" PREFIX "Source" FILES ${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include" PREFIX "Include" FILES ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
	Include
	../Core/Include
)

target_link_libraries(${PROJECT_NAME} PRIVATE AquaEngineCore)

install(
	TARGETS ${PROJECT_NAME}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	BUNDLE DESTINATION .
	RUNTIME DESTINATION bin
)

set(CPACK_PACKAGE_NAME "Aqua Engine")
set(CPACK_PACKAGE_VERSION ${VERSION_STRING})
set(CPACK_PACKAGE_VENDOR "Madissia Technologies")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Aqua Engine/v${VERSION_STRING}")
set(CPACK_STRIP_FILES
	"bin/AquaEditor;.DS_Store;.git;Core/Vendor"
)

if("${GIT_BRANCH}" STREQUAL "main") # Production build
	set(CPACK_PACKAGE_FILE_NAME "Aqua Engine v${VERSION_STRING}")
elseif("${GIT_BRANCH}" STREQUAL "staging") # Staging build
	set(CPACK_PACKAGE_FILE_NAME "Aqua Engine v${VERSION_STRING_LONG}")
else() # Dev build
	set(CPACK_PACKAGE_FILE_NAME "Aqua Engine v${VERSION_STRING_LONG}-dev")
endif()

if(APPLE)
	configure_file(${CMAKE_SOURCE_DIR}/CMake/Mac/Info.plist.in ${CMAKE_BINARY_DIR}/Info.plist @ONLY)

	set(CPACK_GENERATOR "Bundle")
	set(CPACK_MONOLITHIC_INSTALL 1)
	set(CPACK_BUNDLE_NAME "Aqua Engine")
	set(CPACK_BUNDLE_PLIST ${CMAKE_BINARY_DIR}/Info.plist)
	set(CPACK_DMG_VOLUME_NAME ${CPACK_SOURCE_PACKAGE_FILE_NAME})
	set(CPACK_BUNDLE_ICON ${CMAKE_SOURCE_DIR}/CMake/Mac/AquaIcon.icns)
	set(CPACK_PACKAGE_ICON ${CMAKE_SOURCE_DIR}/CMake/Mac/AquaIcon.icns)
	set(CPACK_BUNDLE_STARTUP_COMMAND ${CMAKE_SOURCE_DIR}/CMake/Mac/launcher.sh)
elseif(WIN32)
	# Replace '/' with '\\'; regex so have to escape characters
	STRING(REGEX REPLACE "/" "\\\\\\\\" CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_INSTALL_DIRECTORY} )


	set(CPACK_GENERATOR "NSIS64")
	set(CPACK_NSIS_DISPLAY_NAME ${CPACK_PACKAGE_NAME})
	set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "Aqua Engine")
	set(CPACK_NSIS_MUI_ICON ${CMAKE_SOURCE_DIR}/CMake/Windows/AquaIcon.ico)
	set(CPACK_NSIS_MUI_UNIICON ${CMAKE_SOURCE_DIR}/CMake/Windows/AquaIcon.ico)
	set(CPACK_NSIS_INSTALLED_ICON_NAME ${CMAKE_SOURCE_DIR}/CMake/Windows/AquaIcon.ico)
	install(
		FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
		DESTINATION ${CMAKE_BINARY_DIR}
	)
else()
	set(CPACK_MONOLITHIC_INSTALL 1)
	set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)