set(LIBS 
    TestUtils
    Celeste
    CelesteMocks
    CelesteTestResources)

build_library(NAME CelesteTestUtils FOLDER Celeste/Tests TYPE STATIC LIBS "${LIBS}")