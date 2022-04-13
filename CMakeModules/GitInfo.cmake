# Thanks to https://www.mattkeeter.com/blog/2018-01-06-versioning/

execute_process(COMMAND git log --pretty=format:'%h' -n 1
                OUTPUT_VARIABLE GIT_REV
                ERROR_QUIET)

# Check whether we got any revision (which isn't
# always the case, e.g. when someone downloaded a zip
# file from Github instead of a checkout)
if ("${GIT_REV}" STREQUAL "")
    set(GIT_REV "N/A")
    set(GIT_DIFF "")
    set(GIT_TAG "N/A")
    set(GIT_BRANCH "N/A")
else()
    execute_process(
        COMMAND bash -c "git diff --quiet --exit-code || echo +"
        OUTPUT_VARIABLE GIT_DIFF)
    execute_process(
        COMMAND git describe --exact-match --tags
        OUTPUT_VARIABLE GIT_TAG ERROR_QUIET)
    execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE GIT_BRANCH)

    string(STRIP "${GIT_REV}" GIT_REV)
    string(SUBSTRING "${GIT_REV}" 1 7 GIT_REV)
    string(STRIP "${GIT_DIFF}" GIT_DIFF)
    string(STRIP "${GIT_TAG}" GIT_TAG)
    string(STRIP "${GIT_BRANCH}" GIT_BRANCH)
endif()

# Thanks to https://ipenguin.ws/2012/11/cmake-automatically-use-git-tags-as.html
#parse the version information into pieces.
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${GIT_TAG}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${GIT_TAG}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${GIT_TAG}")

add_definitions(-DAQUA_ENGINE_VERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DAQUA_ENGINE_VERSION_MINOR=${VERSION_MINOR})
add_definitions(-DAQUA_ENGINE_VERSION_PATCH=${VERSION_PATCH})
add_definitions(-DAQUA_ENGINE_VERSION_REV="${GIT_REV}")
add_definitions(-DAQUA_ENGINE_VERSION_DIFF="${GIT_DIFF}")
add_definitions(-DAQUA_ENGINE_VERSION_BRANCH="${GIT_BRANCH}")

message("Engine v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${VERSION_SHA1}")