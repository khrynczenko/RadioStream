cmake_minimum_required (VERSION 3.9)
project(RadioStream)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED ON)

if(WIN32)
	set(BASS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/bass/c)
	set(BASS_LIB_FILE ${CMAKE_SOURCE_DIR}/libs/bass/c/bass.lib)
elseif(UNIX)
	set(BASS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/bass)
	set(BASS_LIB_FILE ${CMAKE_SOURCE_DIR}/libs/bass/x64/libbass.so)
	set(FONTCONFIG_LIB "-lfontconfig")
endif()



SET(MSVC_USE_STATIC_RUNTIME OFF CACHE BOOL "Build nana with static runtime.")
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/nana)

add_executable(RadioStream 
src/Application.cpp
src/Constants.cpp
src/main.cpp
src/states
src/Station.cpp
src/StatusBar.cpp
src/StreamManager.cpp
src/Utilities.cpp
src/observers/Observer.cpp
src/observers/StatusObserver.cpp
src/observers/StreamObserver.cpp
src/observers/Subject.cpp
src/states/MainState.cpp
src/states/State.cpp
src/states/StatesManager.cpp
src/Config.cpp
src/TextLocalizer.cpp
src/observers/TextLocalizerObserver.cpp
src/states/ToolsState.cpp
src/Language.cpp
src/exceptions/LanguageFileNotFound.cpp
src/exceptions/NotSupportedLanguageException.cpp
src/exceptions/WrongLanguageCodeFormatException.cpp
src/StationsDatabase.cpp
src/observers/StationsDatabaseObserver.cpp
include/Application.hpp
include/Constants.hpp
include/observers
include/states
include/Station.hpp
include/StatusBar.hpp
include/StreamManager.hpp
include/Utilities.hpp
include/observers/Events.hpp
include/observers/Observer.hpp
include/observers/StatusObserver.hpp
include/observers/StreamObserver.hpp
include/observers/Subject.hpp
include/states/MainState.hpp
include/states/State.hpp
include/states/StateIdentifiers.hpp
include/states/StatesManager.hpp
include/Config.hpp
include/TextLocalizer.hpp
include/observers/TextLocalizerObserver.hpp
include/states/ToolsState.hpp
include/Language.hpp
include/exceptions/LanguageFileNotFound.hpp
include/exceptions/NotSupportedLanguageException.hpp
include/exceptions/WrongLanguageCodeFormatException.hpp
include/StationsDatabase.hpp
include/observers/StationsDatabaseObserver.hpp
)
target_include_directories(RadioStream PUBLIC ${CMAKE_SOURCE_DIR}/libs/nana/include ${CMAKE_SOURCE_DIR}/libs/json/src  
${BASS_LIB_DIR} ${CMAKE_SOURCE_DIR}/libs/sqlitemoderncpp/hdr)
target_link_libraries(RadioStream nana ${BASS_LIB_FILE} ${FONTCONFIG_LIB} )
