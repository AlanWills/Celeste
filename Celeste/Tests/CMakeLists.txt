cmake_minimum_required(VERSION 3.6)

##---------------------------- Globals ----------------------------##
project(TestCeleste)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
ENDIF()


##------------------------------ TestCeleste ------------------------------##
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp)
file(GLOB_RECURSE RES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Resources/*.*)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RES_FILES})

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

set_source_files_properties(${RES_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    FOLDER Celeste/Tests
    CXX_STANDARD 17
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include)
#target_link_directories(${TEST_CELESTE_PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIB_DIR} ${PROJECT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC 
    Celeste
    TestUtils
    CelesteMocks
    CelesteTestResources
    CelesteTestUtils)

target_compile_options(${PROJECT_NAME} PRIVATE /MP4 /W4 /WX)