cmake_minimum_required(VERSION 3.6)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	set(CELESTE_STANDALONE ON)
	
	project(Celeste)
else()
	set(CELESTE_STANDALONE OFF)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/BuildTools/BuildProject.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/BuildTools/AddPackages.txt)

#---------------------------- Globals ----------------------------##
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
ENDIF()

IF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	SET(BUILD_TESTS FALSE)
ELSE()
	SET(BUILD_TESTS TRUE)
ENDIF()

IF(NOT DEFINED USE_PREBUILT_LIBS)
    SET(USE_PREBUILT_LIBS OFF CACHE BOOL "" FORCE)
ENDIF()

IF(USE_PREBUILT_LIBS)
    SET(EXCLUDE EXCLUDE_FROM_ALL CACHE STRING "" FORCE)
ELSE()
    SET(EXCLUDE "" CACHE STRING "" FORCE)
ENDIF()

if (NOT DEFINED BUILDS_DIR)
    set(BUILDS_DIR ${PROJECT_SOURCE_DIR}/Build/${CMAKE_VS_PLATFORM_NAME})
endif()

if (NOT DEFINED CELESTE_DIR)
    set(CELESTE_DIR ${PROJECT_SOURCE_DIR})
endif()

if (NOT DEFINED WORKING_DIR)
    set(WORKING_DIR ${PROJECT_SOURCE_DIR})
endif()

set(THIRD_PARTY_DIR ${CELESTE_DIR}/3rdParty)
#---------------------------- end Globals ----------------------------##


#---------------------------- Third Party ----------------------------##
add_subdirectory(${THIRD_PARTY_DIR} ${THIRD_PARTY_DIR}/build ${EXCLUDE})
#---------------------------- end Third Party ----------------------------##


cbt_add_packages(PACKAGES
	Platform
	CelesteStl
	Assert
	CrashHandler
	Log
	StringId
	FileSystem
	Lua
	System
	Dolce
	Celeste
	CelesteMocks
	CelesteTestResources
	TestUtils
	CelesteTestUtils)
	
if(${CELESTE_STANDALONE})
	cbt_add_packages(PACKAGES TestGame)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TestGame)
endif()
