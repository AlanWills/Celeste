cmake_minimum_required(VERSION 3.6)

function(build_project)
    set(oneValueArgs NAME FOLDER TYPE SOURCE_DIR RESOURCES_DIR RUNTIME_OUTPUT_DIRECTORY)
    set(multiValueArgs INCLUDES LIBS)
    cmake_parse_arguments(BUILD_PROJECT "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

    project(${BUILD_PROJECT_NAME})

    file(GLOB_RECURSE SOURCE_FILES ${BUILD_PROJECT_SOURCE_DIR}/Source/*.c ${BUILD_PROJECT_SOURCE_DIR}/Source/*.cpp)
    file(GLOB_RECURSE HEADER_FILES ${BUILD_PROJECT_SOURCE_DIR}/Include/*.h ${BUILD_PROJECT_SOURCE_DIR}/Include/*.hpp)
    
    source_group(TREE ${BUILD_PROJECT_SOURCE_DIR} FILES ${SOURCE_FILES})						   
    source_group(TREE ${BUILD_PROJECT_SOURCE_DIR} FILES ${HEADER_FILES})

    if (BUILD_PROJECT_RESOURCES_DIR)
        message(${BUILD_PROJECT_RESOURCES_DIR})
        file(GLOB_RECURSE RESOURCE_FILES ${BUILD_PROJECT_RESOURCES_DIR}/*.*)

        source_group(TREE ${BUILD_PROJECT_SOURCE_DIR} FILES ${RESOURCE_FILES})
        set_source_files_properties(${RESOURCE_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
    elseif()
        set(RESOURCE_FILES "")
    endif()

    add_library(${PROJECT_NAME} ${BUILD_PROJECT_TYPE} ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCE_FILES})

    IF(NOT BUILD_PROJECT_RUNTIME_OUTPUT_DIRECTORY)
        set(BUILD_PROJECT_RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR})
    ENDIF()

    set_target_properties(${PROJECT_NAME} PROPERTIES 
        FOLDER ${BUILD_PROJECT_FOLDER}
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_PROJECT_RUNTIME_OUTPUT_DIRECTORY}
        CXX_STANDARD 17)

    IF(NOT BUILD_PROJECT_INCLUDES)
        set(BUILD_PROJECT_INCLUDES ${BUILD_PROJECT_SOURCE_DIR}/Include)
    ELSE()
        list(APPEND BUILD_PROJECT_INCLUDES ${BUILD_PROJECT_SOURCE_DIR}/Include)
    ENDIF()

    target_include_directories(${PROJECT_NAME} PUBLIC "${BUILD_PROJECT_INCLUDES}")
       
    if (BUILD_PROJECT_LIBS)
        target_link_libraries(${PROJECT_NAME} PUBLIC "${BUILD_PROJECT_LIBS}")
    endif()

    target_compile_options(${PROJECT_NAME} PRIVATE /MP4 /W4 /WX)
endfunction()

function(build_library)
    set(oneValueArgs NAME FOLDER TYPE RESOURCES_DIR RUNTIME_OUTPUT_DIRECTORY)
    set(multiValueArgs INCLUDES LIBS TEST_LIBS)
    cmake_parse_arguments(BUILD_LIBRARY "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN})

    build_project(
        NAME ${BUILD_LIBRARY_NAME}
        FOLDER ${BUILD_LIBRARY_FOLDER}
        TYPE ${BUILD_LIBRARY_TYPE}
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
        RESOURCES_DIR ${BUILD_LIBRARY_RESOURCES_DIR}
        INCLUDES "${BUILD_LIBRARY_INCLUDES}"
        LIBS "${BUILD_LIBRARY_LIBS}"
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_LIBRARY_RUNTIME_OUTPUT_DIRECTORY})

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Tests)
        if (NOT BUILD_LIBRARY_TEST_LIBS)
            set(BUILD_LIBRARY_TEST_LIBS 
                ${BUILD_LIBRARY_NAME}
                TestUtils)
        else()
            list(APPEND BUILD_LIBRARY_TEST_LIBS 
                ${BUILD_LIBRARY_NAME}
                TestUtils)
        endif()

        build_project(
            NAME Test${BUILD_LIBRARY_NAME}
            FOLDER ${BUILD_LIBRARY_FOLDER}/Tests
            TYPE SHARED
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Tests
            RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Resources
            LIBS "${BUILD_LIBRARY_TEST_LIBS}"
            RUNTIME_OUTPUT_DIRECTORY ${BUILD_LIBRARY_RUNTIME_OUTPUT_DIRECTORY})

        set_target_properties(Test${BUILD_LIBRARY_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Tests)
    endif()
endfunction()