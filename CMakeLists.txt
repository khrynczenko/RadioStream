cmake_minimum_required (VERSION 3.10)
project(RadioStream VERSION "0.1.0")

if(WIN32)
    set(BASS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/bass/c)
    set(BASS_LIB_FILE ${CMAKE_SOURCE_DIR}/libs/bass/c/x64/bass.lib)
    set(shared_lib "dll")
elseif(UNIX)
    set(BASS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/bass)
    set(BASS_LIB_FILE ${CMAKE_SOURCE_DIR}/libs/bass/x64/libbass.so)
	set(FONTCONFIG_LIB "-lfontconfig")
	set(PTHREAD_LIB "-lpthread")
endif()

set(MSVC_USE_STATIC_RUNTIME FALSE) #This is nana variable

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

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/nana EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/poco EXCLUDE_FROM_ALL)

add_executable(RadioStream
include/StatusBar.hpp
include/Subject.hpp
include/Station.hpp
include/StationsDatabase.hpp
include/Utilities.hpp
include/RadioBrowserRequester.hpp
include/StationPlayer.hpp
include/Constants.hpp
include/Application.hpp
include/Events.hpp
include/Config.hpp
include/Observer.hpp
include/Language.hpp
include/StreamManager.hpp
include/TextLocalizer.hpp
include/multimedia_playlists/MultimediaPlaylistReader.hpp
        include/multimedia_playlists/HTTPDownloader.hpp
include/multimedia_playlists/M3UReader.hpp
include/multimedia_playlists/MultimediaPlaylistReaderFactory.hpp
include/multimedia_playlists/PocoHTTPDownloader.hpp
include/multimedia_playlists/PLSReader.hpp
include/widgets/StationListbox.hpp
include/controllers/Controller.hpp
include/controllers/ConfigController.hpp
include/controllers/StationPlayerController.hpp
include/controllers/StatusBarController.hpp
include/controllers/RadioBrowserRequesterController.hpp
include/controllers/StationsDatabaseController.hpp
include/exceptions/NanaTextboxProcessingException.hpp
include/exceptions/WrongLanguageCodeFormatException.hpp
include/exceptions/NotSupportedLanguageException.hpp
include/exceptions/LanguageFileNotFound.hpp
include/states/State.hpp
include/states/StatesManager.hpp
include/states/MainState.hpp
include/states/StateIdentifiers.hpp
include/states/ToolsState.hpp
include/states/SearchState.hpp
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
src/states/StatesManager.cpp include/exceptions/ReaderCouldNotReadUrl.hpp src/exceptions/ReaderCouldNotReadUrl.cpp src/exceptions/CouldNotMakeReader.cpp include/exceptions/CouldNotMakeReader.hpp)

target_compile_features(RadioStream PRIVATE cxx_std_17)

target_include_directories(RadioStream PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/poco/Foundation/include
    ${CMAKE_SOURCE_DIR}/libs/poco/Data/include
    ${CMAKE_SOURCE_DIR}/libs/poco/Data/SQLite/include
    ${CMAKE_SOURCE_DIR}/libs/poco/Net/include
    ${CMAKE_SOURCE_DIR}/libs/nana/include
    ${CMAKE_SOURCE_DIR}/libs/json/include
    ${BASS_LIB_DIR} )

target_link_libraries(RadioStream PRIVATE nana Foundation Data DataSQLite Net ${BASS_LIB_FILE} ${FONTCONFIG_LIB} ${PTHREAD_LIB})

if(UNIX)
        set(BASS_INSTALL_LIB "${BASS_LIB_FILE}")
elseif(WIN32)
        set(BASS_INSTALL_LIB "${CMAKE_SOURCE_DIR}/libs/bass/x64/bass.dll")
endif()

#INSTALL SCRIPT
if(WIN32)
    install(TARGETS RadioStream
            RUNTIME
	    PERMISSIONS OWNER_READ OWNER_EXECUTE
            DESTINATION "."
            )
    install(FILES
            "${CMAKE_BINARY_DIR}/bin/Release/PocoData.${shared_lib}"
            "${CMAKE_BINARY_DIR}/bin/Release/PocoDataSQLite.${shared_lib}"
            "${CMAKE_BINARY_DIR}/bin/Release/PocoFoundation.${shared_lib}"
            "${CMAKE_BINARY_DIR}/bin/Release/PocoNet.${shared_lib}"
            "${BASS_INSTALL_LIB}"
            DESTINATION ".")
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/lang"
            DESTINATION "." )
elseif(UNIX)
    install(TARGETS RadioStream
            RUNTIME
            DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/"
            )
    install(FILES
            "${CMAKE_BINARY_DIR}/lib/libPocoData.so.52"
            "${CMAKE_BINARY_DIR}/lib/libPocoDataSQLite.so.52"
            "${CMAKE_BINARY_DIR}/lib/libPocoFoundation.so.52"
            "${CMAKE_BINARY_DIR}/lib/libPocoNet.so.52"
            "${BASS_INSTALL_LIB}"
            DESTINATION /usr/lib)
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/lang"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/" )
endif()

#CPACK SCRIPT
SET(CPACK_PACKAGE_NAME "RadioStream")
SET(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
SET(CPACK_PACKAGE_VENDOR "https://github.com/JenioPY")
SET(CPACK_PACKAGE_CONTACT "https://github.com/JenioPY")
SET(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RadioStream")
SET(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/JenioPY/RadioStream")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "RadioStream")
SET(CPACK_PACKAGE_EXECUTABLES "RadioStream;RadioStream")
SET(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
SET(CPACK_NSIS_INSTALL_ROOT "C:")


include(CPack)

