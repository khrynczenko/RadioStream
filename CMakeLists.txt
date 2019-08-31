cmake_minimum_required (VERSION 3.13)
project(RadioStream VERSION "0.1.1")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(MSVC_USE_STATIC_RUNTIME OFF CACHE BOOL "Nana runtime type") #This is nana variable

# POCO variables
set(ENABLE_XML FALSE)
set(ENABLE_JSTRUE TRUE)
set(ENABLE_MONGODB FALSE)
set(ENABLE_REDIS FALSE)
set(ENABLE_PDF FALSE)
set(ENABLE_UTIL TRUE)
set(ENABLE_NET TRUE)
set(ENABLE_NETSSL TRUE)
set(ENABLE_NETSSL_WIN FALSE)
set(ENABLE_CRYPTO FALSE)
set(ENABLE_DATA TRUE)
set(ENABLE_DATA_SQLITE TRUE)
set(ENABLE_DATA_MYSQL FALSE)
set(ENABLE_DATA_ODBC FALSE)
set(ENABLE_SEVENZIP FALSE)
set(ENABLE_ZIP FALSE)
set(ENABLE_APACHECONNECTOR FALSE)
set(ENABLE_CPPPARSER FALSE)
set(ENABLE_POCODOC FALSE)
set(ENABLE_PAGECOMPILER FALSE)
set(ENABLE_PAGECOMPILER_FILE2PAGE FALSE)

include(DownloadDependencies)

add_subdirectory(${nana_SOURCE_DIR} EXCLUDE_FROM_ALL)
add_subdirectory(${poco_SOURCE_DIR} EXCLUDE_FROM_ALL)
add_subdirectory(${clip_SOURCE_DIR} EXCLUDE_FROM_ALL)

if(WIN32)
    set(BASS_LIB_DIR ${bass_SOURCE_DIR}/c)
    set(BASS_LIB_FILE ${bass_SOURCE_DIR}/c/x64/bass.lib)
elseif(UNIX)
    set(BASS_LIB_DIR ${bass_SOURCE_DIR})
    set(BASS_LIB_FILE ${bass_SOURCE_DIR}/x64/libbass.so)
	set(FONTCONFIG_LIB "-lfontconfig")
	set(PTHREAD_LIB "-lpthread")
endif()

add_executable(RadioStream
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
src/ApplicationDirectories.cpp)

target_compile_features(RadioStream PRIVATE cxx_std_17)

target_include_directories(RadioStream PRIVATE
    ${poco_SOURCE_DIR}/Foundation/include
    ${poco_SOURCE_DIR}/Data/include
    ${poco_SOURCE_DIR}/poco/Data/SQLite/include
    ${poco_SOURCE_DIR}/poco/Net/include
    ${nana_SOURCE_DIR}/include
    ${json_SOURCE_DIR}
    ${clip_SOURCE_DIR}
    ${BASS_LIB_DIR}
    ${PROJECT_BINARY_DIR}/radio-stream-version
)

target_link_libraries(RadioStream PRIVATE
                      nana
                      Foundation
                      Data
                      DataSQLite
                      Net
                      clip
                      ${BASS_LIB_FILE} 
                      ${FONTCONFIG_LIB} 
                      ${PTHREAD_LIB})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_options(RadioStream BEFORE PRIVATE "/SUBSYSTEM:WINDOWS")
endif()

if(UNIX)
        set(BASS_INSTALL_LIB "${BASS_LIB_FILE}")
elseif(WIN32)
        set(BASS_INSTALL_LIB "${bass_SOURCE_DIR}/x64/bass.dll")
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
elseif(UNIX)
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
    install(DIRECTORY DESTINATION "/usr/local/share/radiostream")
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/lang"
            DESTINATION "/usr/local/share/radiostream/")
endif()

#CPACK SCRIPT
SET(CPACK_PACKAGE_NAME "RadioStream")
SET(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
SET(CPACK_PACKAGE_VENDOR "https://github.com/khrynczenko")
SET(CPACK_PACKAGE_CONTACT "https://github.com/khrynczenko")
SET(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RadioStream")
SET(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/khrynczenko/RadioStream")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "RadioStream")
SET(CPACK_PACKAGE_EXECUTABLES "RadioStream;RadioStream")
SET(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
SET(CPACK_NSIS_INSTALL_ROOT "C:")


include(CPack)

