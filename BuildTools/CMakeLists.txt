cmake_minimum_required(VERSION 3.6)

function(build_project)
    set(oneValueArgs NAME FOLDER TYPE)
    set(multiValueArgs INCLUDES LIBS)
    cmake_parse_arguments(BUILD_LIBRARY "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

    project(${BUILD_LIBRARY_NAME})

    file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
    file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp)
    file(GLOB_RECURSE RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Resources/*.*)

    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})						   
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${RESOURCE_FILES})

    add_library(${PROJECT_NAME} ${BUILD_LIBRARY_TYPE} ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCE_FILES})

    set_source_files_properties(${RESOURCE_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

    set_target_properties(${PROJECT_NAME} PROPERTIES 
        FOLDER ${BUILD_LIBRARY_FOLDER}
        CXX_STANDARD 17)

    IF(NOT BUILD_LIBRARY_INCLUDES)
        set(BUILD_LIBRARY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/Include)
    ELSE()
        list(APPEND BUILD_LIBRARY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/Include)
    ENDIF()

    target_include_directories(${PROJECT_NAME} PUBLIC "${BUILD_LIBRARY_INCLUDES}")
       
    if (BUILD_LIBRARY_LIBS)
        target_link_libraries(${PROJECT_NAME} PUBLIC "${BUILD_LIBRARY_LIBS}")
    endif()

    target_compile_options(${PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
endfunction()

function(build_library)
    set(oneValueArgs NAME FOLDER TYPE)
    set(multiValueArgs INCLUDES LIBS)
    cmake_parse_arguments(BUILD_LIBRARY "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN})

    build_project(
        NAME ${BUILD_LIBRARY_NAME}
        FOLDER ${BUILD_LIBRARY_FOLDER}
        TYPE ${BUILD_LIBRARY_TYPE}
        INCLUDES "${BUILD_LIBRARY_INCLUDES}"
        LIBS "${BUILD_LIBRARY_LIBS}")
endfunction()