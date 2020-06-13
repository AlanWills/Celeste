set(LIBS
    Celeste
    CelesteTestResources)

if (${BUILD_TESTS})
    cbt_build_project(NAME CelesteMocks FOLDER Celeste/Tests TYPE STATIC LIBS "${LIBS}")
endif()