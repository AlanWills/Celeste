set(LIBS 
    TestUtils
    Celeste
    CelesteMocks
    CelesteTestResources)

cbt_build_project(NAME CelesteTestUtils FOLDER Celeste/Tests TYPE STATIC LIBS "${LIBS}")