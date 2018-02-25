cmake_minimum_required (VERSION 3.9)
project(RadioStream)

if(WIN32)
        set(BASS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/bass/c)
        set(BASS_LIB_FILE ${CMAKE_SOURCE_DIR}/libs/bass/c/bass.lib)
elseif(UNIX)
        set(BASS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/bass)
        set(BASS_LIB_FILE ${CMAKE_SOURCE_DIR}/libs/bass/x64/libbass.so)
	set(FONTCONFIG_LIB "-lfontconfig")
	set(SQLITE3_LIB "-lsqlite3")
	set(PTHREAD_LIB "-lpthread")
endif()

set(MSVC_USE_STATIC_RUNTIME OFF )

set(ENABLE_XML OFF)
set(ENABLE_JSON ON)
set(ENABLE_MONGODB OFF)
set(ENABLE_REDIS OFF)
set(ENABLE_PDF OFF)
set(ENABLE_UTIL ON)
set(ENABLE_NET ON)
set(ENABLE_NETSSL ON)
set(ENABLE_NETSSL_WIN OFF)
set(ENABLE_CRYPTO OFF)
set(ENABLE_DATA ON)
set(ENABLE_DATA_SQLITE ON)
set(ENABLE_DATA_MYSQL OFF)
set(ENABLE_DATA_ODBC OFF)
set(ENABLE_SEVENZIP OFF)
set(ENABLE_ZIP OFF)
set(ENABLE_APACHECONNECTOR OFF)
set(ENABLE_CPPPARSER OFF)
set(ENABLE_POCODOC OFF)
set(ENABLE_PAGECOMPILER OFF)
set(ENABLE_PAGECOMPILER_FILE2PAGE OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/nana)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/poco)

add_executable(RadioStream 
include/Application.hpp
include/Config.hpp
include/Constants.hpp
include/Language.hpp
include/RadioBrowserRequester.hpp
include/RadioBrowserStation.hpp
include/Station.hpp
include/StationsDatabase.hpp
include/StatusBar.hpp
include/StreamManager.hpp
include/TextLocalizer.hpp
include/Utilities.hpp
include/controllers/ConfigController.hpp
include/controllers/Controller.hpp
include/controllers/StationsDatabaseController.hpp
include/controllers/StreamManagerController.hpp
include/exceptions/LanguageFileNotFound.hpp
include/exceptions/NanaTextboxProcessingException.hpp
include/exceptions/NotSupportedLanguageException.hpp
include/exceptions/WrongLanguageCodeFormatException.hpp
include/observers/ConfigObserver.hpp
include/observers/Events.hpp
include/observers/Observer.hpp
include/observers/StationsDatabaseObserver.hpp
include/observers/StreamManagerObserver.hpp
include/observers/Subject.hpp
include/states/MainState.hpp
include/states/SearchState.hpp
include/states/State.hpp
include/states/StateIdentifiers.hpp
include/states/StatesManager.hpp
include/states/ToolsState.hpp
src/Application.cpp
src/Config.cpp
src/Constants.cpp
src/Language.cpp
src/main.cpp
src/RadioBrowserRequester.cpp
src/RadioBrowserStationcpp.cpp
src/Station.cpp
src/StationsDatabase.cpp
src/StatusBar.cpp
src/StreamManager.cpp
src/TextLocalizer.cpp
src/Utilities.cpp
src/controllers/ConfigController.cpp
src/controllers/Controller.cpp
src/controllers/StationsDatabaseController.cpp
src/controllers/StreamManagerController.cpp
src/exceptions/LanguageFileNotFound.cpp
src/exceptions/NanaTextboxProcessingException.cpp
src/exceptions/NotSupportedLanguageException.cpp
src/exceptions/WrongLanguageCodeFormatException.cpp
src/observers/ConfigObserver.cpp
src/observers/Observer.cpp
src/observers/StationsDatabaseObserver.cpp
src/observers/StreamManagerObserver.cpp
src/observers/Subject.cpp
src/states/MainState.cpp
src/states/SearchState.cpp
src/states/State.cpp
src/states/StatesManager.cpp
src/states/ToolsState.cpp
)

if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(RadioStream PRIVATE "-Wall")
endif()
if ( MSVC )
    target_compile_options(RadioStream PRIVATE "/W4")
endif()
target_compile_features(RadioStream PRIVATE cxx_std_17)

target_include_directories(RadioStream PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/poco/Foundation/include
    ${CMAKE_SOURCE_DIR}/libs/poco/Data/include
    ${CMAKE_SOURCE_DIR}/libs/poco/Data/SQLite/include
    ${CMAKE_SOURCE_DIR}/libs/poco/Net/include
    ${CMAKE_SOURCE_DIR}/libs/nana/include ${CMAKE_SOURCE_DIR}/libs/json/include
    ${BASS_LIB_DIR} ${CMAKE_SOURCE_DIR}/libs/sqlitemoderncpp/hdr)

target_link_libraries(RadioStream PRIVATE nana Foundation Data DataSQLite Net ${BASS_LIB_FILE} ${FONTCONFIG_LIB} ${SQLITE3_LIB} ${PTHREAD_LIB})

