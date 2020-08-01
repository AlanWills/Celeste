set(LIBS 
    Celeste)

if (${BUILD_TESTS})
    set(TEST_RESOURCES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
    string(REPLACE "/" "\\\\" TEST_RESOURCES_DIRECTORY "${TEST_RESOURCES_DIRECTORY}")
    configure_file("Include/TestResources/TestResourcesConfig.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/Include/TestResources/TestResourcesConfig.h" @ONLY)

    cbt_build_project(NAME CelesteTestResources FOLDER Celeste/Tests TYPE STATIC LIBS "${LIBS}")
endif()