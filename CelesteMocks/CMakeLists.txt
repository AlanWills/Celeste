cmake_minimum_required(VERSION 3.6)

##---------------------------- Globals ----------------------------##
project(CelesteMocks)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
IF(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
ENDIF()


##------------------------------ CelesteMocks ------------------------------##
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})						   
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    FOLDER Celeste/Tests
    CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Include)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    Celeste)

target_compile_options(${PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DCELESTE_MOCKS_STATIC_LIB -DGLM_FORCE_SILENT_WARNINGS)
