
include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/deps)
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(
        nana
        GIT_REPOSITORY "https://github.com/cnjinhao/nana.git"
        GIT_TAG "v1.7.1"
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        UPDATE_COMMAND ""
        UPDATE_DISCONNECTED TRUE
        INSTALL_COMMAND ""
        TEST_COMMAND ""
)
FetchContent_Declare(
        poco
        GIT_REPOSITORY "https://github.com/pocoproject/poco.git"
        GIT_TAG "poco-1.9.0-release"
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        GIT_SUBMODULES ""
        UPDATE_COMMAND ""
        UPDATE_DISCONNECTED TRUE
        INSTALL_COMMAND ""
        TEST_COMMAND ""
)
FetchContent_Declare(
        json
        GIT_REPOSITORY "https://github.com/azadkuh/nlohmann_json_release.git"
        GIT_TAG "v3.2.0"
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        UPDATE_COMMAND ""
        UPDATE_DISCONNECTED TRUE
        INSTALL_COMMAND ""
        TEST_COMMAND ""
)

if(WIN32)
    set(BASS_URL "http://us.un4seen.com/files/bass24.zip")
elseif(UNIX)
    set(BASS_URL "http://us.un4seen.com/files/bass24-linux.zip")
endif()

FetchContent_Declare(
        bass
        URL ${BASS_URL}
        UPDATE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
)
FetchContent_Populate(nana)
FetchContent_Populate(poco)
FetchContent_Populate(json)
FetchContent_Populate(bass)
