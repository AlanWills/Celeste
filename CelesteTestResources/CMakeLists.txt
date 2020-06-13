set(LIBS 
    Celeste)

if (BUILD_TESTS)
    cbt_build_project(NAME CelesteTestResources FOLDER Celeste/Tests TYPE STATIC LIBS "${LIBS}")
endif()