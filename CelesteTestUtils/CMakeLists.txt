set(LIBS 
    TestUtils
    Celeste
    CelesteMocks
    CelesteTestResources)

if (BUILD_TESTS)
    cbt_build_project(NAME CelesteTestUtils FOLDER Celeste/Tests TYPE STATIC LIBS "${LIBS}")
endif()