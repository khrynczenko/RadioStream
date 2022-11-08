include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/deps)
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

if(WIN32)
    set(BASS_URL "http://us.un4seen.com/files/bass24.zip")
elseif(UNIX)
    set(BASS_URL "http://us.un4seen.com/files/bass24-linux.zip")
    set(BASS_AAC_URL "http://us.un4seen.com/files/z/2/bass_aac24-linux.zip")
endif()

include(CPM)

CPMAddPackage(
    NAME clip
    GIT_TAG "v1.2"
    GITHUB_REPOSITORY dacap/clip
    OPTIONS
        "CLIP_EXAMPLES FALSE"
        "CLIP_TESTS FALSE"
        "CLIP_X11_WITH_PNG FALSE"
)

CPMAddPackage(
    NAME nana
    GITHUB_REPOSITORY khrynczenko/nana
    GIT_TAG "hotfix-1.7.4"
    OPTIONS
        "MSVC_USE_STATIC_RUNTIME OFF"
        "NANA_CMAKE_ENABLE_PNG ${NANA_PNG}"
)

CPMAddPackage(
    NAME poco
    GITHUB_REPOSITORY pocoproject/poco
    GIT_TAG "poco-1.10.1-release"
    OPTIONS
        "POCO_DISABLE_INTERNAL_OPENSSL TRUE"
        "POCO_EXTERNAL_OPENSSL TRUE"
        "FORCE_OPENSSL TRUE"
        "ENABLE_XML FALSE"
        "ENABLE_ENCODINGS FALSE"
        "ENABLE_MONGODB FALSE"
        "ENABLE_REDIS FALSE"
        "ENABLE_PDF FALSE"
        "ENABLE_UTIL FALSE"
        "ENABLE_NET TRUE"
        "ENABLE_NETSSL TRUE"
        "ENABLE_JSON FALSE"
        "ENABLE_NETSSL_WIN FALSE"
        "ENABLE_CRYPTO TRUE"
        "ENABLE_JWT FALSE"
        "ENABLE_DATA TRUE"
        "ENABLE_DATA_SQLITE TRUE"
        "ENABLE_DATA_MYSQL FALSE"
        "ENABLE_DATA_ODBC FALSE"
        "ENABLE_SEVENZIP FALSE"
        "ENABLE_ZIP FALSE"
        "ENABLE_APACHECONNECTOR FALSE"
        "ENABLE_CPPPARSER FALSE"
        "ENABLE_POCODOC FALSE"
        "ENABLE_PAGECOMPILER FALSE"
        "ENABLE_PAGECOMPILER_FILE2PAGE FALSE"
)

CPMAddPackage(
    NAME json
    VERSION 3.2.0  
    # the git repo is incredibly large, so we download the archived include directory
    URL https://github.com/nlohmann/json/releases/download/v3.2.0/include.zip
)

if (json_ADDED)
    add_library(json INTERFACE IMPORTED)
    target_include_directories(json INTERFACE ${json_SOURCE_DIR})
endif()

CPMAddPackage(
    NAME bass
    # the git repo is incredibly large, so we download the archived include directory
    URL ${BASS_URL}
)

if(UNIX)
    CPMAddPackage(
        NAME bass_aac
        # the git repo is incredibly large, so we download the archived include directory
        URL ${BASS_AAC_URL}
    )
endif()

if(WIN32)
    set(BASS_LIB_DIR ${bass_SOURCE_DIR}/c)
    set(BASS_LIB_FILE ${bass_SOURCE_DIR}/c/x64/bass${CMAKE_LINK_LIBRARY_SUFFIX})
    set(BASS_AAC_LIB_DIR "")
    set(BASS_AAC_LIB_FILE "")
    set(CRYPTO_LIB_FILE $ENV{OPENSSL_ROOT_DIR}/lib/libcrypto.lib)
    set(SSL_LIB_FILE $ENV{OPENSSL_ROOT_DIR}/lib/libssl.lib)
elseif(UNIX)
    set(BASS_LIB_DIR ${bass_SOURCE_DIR})
    set(BASS_LIB_FILE ${bass_SOURCE_DIR}/x64/libbass${CMAKE_SHARED_LIBRARY_SUFFIX})
    set(BASS_AAC_LIB_DIR ${bass_aac_SOURCE_DIR}/c)
    set(BASS_AAC_LIB_FILE ${bass_aac_SOURCE_DIR}/x64/libbass_aac${CMAKE_SHARED_LIBRARY_SUFFIX})
    set(CRYPTO_LIB_FILE "")
    set(SSL_LIB_FILE "")
    set(FONTCONFIG_LIB "-lfontconfig")
    set(PTHREAD_LIB "-lpthread")
endif()
