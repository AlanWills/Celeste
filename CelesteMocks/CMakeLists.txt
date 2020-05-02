set(LIBS
    Celeste
    CelesteTestResources)

cbt_build_project(NAME CelesteMocks FOLDER Celeste/Tests TYPE STATIC LIBS "${LIBS}")