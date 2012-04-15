
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT (ProfilerServer CXX C)

IF( ${CMAKE_BUILD_TYPE} STREQUAL Debug )
    # CMAKE_C_FLAGS_DEBUG will also be added to CMAKE_C_FLAGS
    MESSAGE( "Debug build" )
    ADD_DEFINITIONS(-DDEBUG -D_DEBUG -D__DEBUG__)
ENDIF()

INCLUDE_DIRECTORIES( ../ )

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin" )

INCLUDE(TestBigEndian)

TEST_BIG_ENDIAN(BIG_ENDIAN_SYSTEM)

IF(BIG_ENDIAN_SYSTEM)
    MESSAGE("SETTING Big endian")
    ADD_DEFINITIONS(-D__BIG_ENDIAN__)
ELSE()
    MESSAGE("SETTING Little endian")
    ADD_DEFINITIONS(-D__LITTLE_ENDIAN__)
ENDIF()

IF(WIN32)
    ADD_DEFINITIONS(-D__WINDOWS__ -D_CRT_SECURE_NO_WARNINGS)
ENDIF()

file(GLOB APP_CPPFILES ../*.cpp)
file(GLOB APP_INLFILES ../*.inl)
file(GLOB APP_HPPFILES ../*.hpp)
file(GLOB APP_CFILES ../*.c)
file(GLOB APP_HFILES ../*.h)
source_group("Application Files" FILES ${APP_CPPFILES} ${APP_INLFILES} ${APP_HPPFILES} ${APP_CFILES} ${APP_HFILES})

SET( ALLFILES ${APP_CPPFILES} ${APP_INLFILES} ${APP_HPPFILES} ${APP_CFILES} ${APP_HFILES} )

ADD_EXECUTABLE( ProfileServer ${ALLFILES} )

IF(WIN32)
    TARGET_LINK_LIBRARIES( ProfileServer
        winmm.lib
        comctl32.lib
        ws2_32.lib advapi32.lib )
ENDIF()


# force variables that could be defined on the cmdline
# to be written to the cach

SET( CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
"One of None Debug Release RelWithDebInfo MinSizeRel" FORCE )
