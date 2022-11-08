cmake_minimum_required (VERSION 3.16)
project(RadioStream VERSION "0.2.1")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(SetupDependencies)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL 1.1.1 REQUIRED)

add_executable(RadioStream
    CMakeSetup.rc
    src/Application.cpp
    src/StreamManager.cpp
    src/StationsDatabase.cpp
    src/TextLocalizer.cpp
    src/main.cpp
    src/Constants.cpp
    src/StationPlayer.cpp
    src/Utilities.cpp
    src/Observer.cpp
    src/Config.cpp
    src/Subject.cpp
    src/Language.cpp
    src/Station.cpp
    src/StatusBar.cpp
    src/RadioBrowserRequester.cpp
    src/multimedia_playlists/PocoHTTPDownloader.cpp
    src/multimedia_playlists/M3UReader.cpp
    src/multimedia_playlists/PLSReader.cpp
    src/multimedia_playlists/MultimediaPlaylistReaderFactory.cpp
    src/widgets/StationListbox.cpp
    src/controllers/StationPlayerController.cpp
    src/controllers/ConfigController.cpp
    src/controllers/Controller.cpp
    src/controllers/StationsDatabaseController.cpp
    src/controllers/StatusBarController.cpp
    src/controllers/RadioBrowserRequesterController.cpp
    src/exceptions/NanaTextboxProcessingException.cpp
    src/exceptions/NotSupportedLanguageException.cpp
    src/exceptions/WrongLanguageCodeFormatException.cpp
    src/exceptions/LanguageFileNotFound.cpp
    src/states/ToolsState.cpp
    src/states/State.cpp
    src/states/MainState.cpp
    src/states/SearchState.cpp
    src/states/StatesManager.cpp
    src/exceptions/ReaderCouldNotReadUrl.cpp
    src/exceptions/CouldNotMakeReader.cpp
    src/StreamURIResolver.cpp
    src/ApplicationDirectories.cpp
)

target_compile_features(RadioStream PRIVATE cxx_std_17)

target_include_directories(RadioStream SYSTEM PRIVATE
    ${poco_SOURCE_DIR}/Foundation/include
    ${poco_SOURCE_DIR}/Crypto/include
    ${poco_SOURCE_DIR}/Data/include
    ${poco_SOURCE_DIR}/Data/SQLite/include
    ${poco_SOURCE_DIR}/NetSSL_OpenSSL/include
    ${nana_SOURCE_DIR}/include
    ${json_SOURCE_DIR}
    ${clip_SOURCE_DIR}
    ${BASS_LIB_DIR}
    ${BASS_AAC_LIB_DIR}
)

target_include_directories(RadioStream PRIVATE
    ${PROJECT_BINARY_DIR}/radio-stream-version
)


target_link_libraries(RadioStream PRIVATE
                      nana
                      Foundation
                      Crypto
                      Data
                      DataSQLite
                      NetSSL
                      clip
                      ${SSL_LIB_FILE}
                      ${CRYPTO_LIB_FILE} 
                      ${BASS_LIB_FILE}
                      ${BASS_AAC_LIB_FILE}
                      ${FONTCONFIG_LIB} 
                      ${PTHREAD_LIB})

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    target_link_options(RadioStream PRIVATE "/SUBSYSTEM:WINDOWS")
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    # remove "overriding /W3 with /W4" compiler warning
    string(REGEX REPLACE "/W3" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    # warning level 4 and all warnings as errors
    target_compile_options(RadioStream PRIVATE /W4 /WX /sdl)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    # lots of warnings and all warnings as errors
    target_compile_options(RadioStream PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unknown-pragmas)
endif()

if(UNIX)
        set(BASS_INSTALL_LIB "${BASS_LIB_FILE}")
        set(BASS_AAC_INSTALL_LIB "${BASS_AAC_LIB_FILE}")
elseif(WIN32)
        set(BASS_INSTALL_LIB "${bass_SOURCE_DIR}/x64/bass${CMAKE_SHARED_LIBRARY_SUFFIX}")
endif()

configure_file (
  "${PROJECT_SOURCE_DIR}/cmake/RadioStreamVersion.hpp.in"
  "${PROJECT_BINARY_DIR}/radio-stream-version/RadioStreamVersion.hpp"
)

#INSTALL SCRIPT
set_target_properties(RadioStream PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
get_target_property(OUT_DIR RadioStream RUNTIME_OUTPUT_DIRECTORY)
add_custom_command(TARGET RadioStream POST_BUILD COMMAND ${CMAKE_COMMAND} -E
    copy "${BASS_INSTALL_LIB}" "${OUT_DIR}")
add_custom_command(TARGET RadioStream POST_BUILD COMMAND ${CMAKE_COMMAND} -E
    copy_directory "${CMAKE_SOURCE_DIR}/lang" "${OUT_DIR}/lang")
if(WIN32)
    add_custom_command(TARGET RadioStream POST_BUILD COMMAND ${CMAKE_COMMAND} -E
        copy "${CMAKE_SOURCE_DIR}/resources/icon.ico" "${CMAKE_BINARY_DIR}/bin")
    set_target_properties(Foundation PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}")
    set_target_properties(Data PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}")
    set_target_properties(DataSQLite PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}")
    set_target_properties(Net PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}")
    install(TARGETS RadioStream
            RUNTIME
	    PERMISSIONS OWNER_READ OWNER_EXECUTE
            DESTINATION "."
            )
    install(TARGETS Foundation Data DataSQLite Net RUNTIME
            DESTINATION ".")
    install(FILES
            "${BASS_INSTALL_LIB}"
            DESTINATION ".")
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/lang"
            DESTINATION "." )
    install(FILES
            "${CMAKE_SOURCE_DIR}/resources/icon.ico"
            DESTINATION ".")
elseif(UNIX)
    add_custom_command(TARGET RadioStream POST_BUILD COMMAND ${CMAKE_COMMAND} -E
                       copy "${BASS_AAC_INSTALL_LIB}" "${OUT_DIR}")
    set_target_properties(Foundation PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}")
    set_target_properties(Data PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}")
    set_target_properties(DataSQLite PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}")
    set_target_properties(Net PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}")
    install(TARGETS RadioStream
            RUNTIME
            DESTINATION "/usr/bin/"
            )
    install(TARGETS Foundation Data DataSQLite Net LIBRARY
            DESTINATION /usr/lib)
    install(FILES
            "${BASS_INSTALL_LIB}"
            "${BASS_AAC_INSTALL_LIB}"
            DESTINATION "/usr/lib")
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/lang"
            DESTINATION "/usr/local/share/radiostream/")
    install(FILES "${CMAKE_SOURCE_DIR}/resources/icon.svg"
            DESTINATION "/usr/local/radiostream/")
    install(FILES "${CMAKE_SOURCE_DIR}/resources/icon.png"
            DESTINATION "/usr/local/radiostream/")
    install(FILES "${CMAKE_SOURCE_DIR}/RadioStream.desktop"
            DESTINATION "/usr/share/applications/")
endif()

# CPACK SCRIPT
SET(CPACK_PACKAGE_NAME "RadioStream")
SET(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
SET(CPACK_PACKAGE_VENDOR "https://github.com/khrynczenko")
SET(CPACK_PACKAGE_CONTACT "https://github.com/khrynczenko")
SET(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY 
    "RadioStream - Simple, fast and light-weight internet radio player for Windows and Linux ")
SET(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/khrynczenko/RadioStream")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
SET(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "RadioStream")
SET(CPACK_PACKAGE_EXECUTABLES "RadioStream;RadioStream")
# DEBIAN PACKAGE VARIABLES

# NSIS INSTALLER VARIABLES
SET(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
SET(CPACK_NSIS_INSTALL_ROOT "C:")
SET(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL TRUE)
SET(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")


include(CPack)

