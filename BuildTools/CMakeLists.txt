cmake_minimum_required(VERSION 3.6)

function(build_library)
    set(oneValueArgs NAME FOLDER TYPE)
    set(multiValueArgs INCLUDES LIBS)
    cmake_parse_arguments(BUILD_LIBRARY "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

    project(${BUILD_LIBRARY_NAME})

    file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
    file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp)

    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})						   
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})

    add_library(${PROJECT_NAME} ${BUILD_LIBRARY_TYPE} ${HEADER_FILES} ${SOURCE_FILES} ${RES_FILES})

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