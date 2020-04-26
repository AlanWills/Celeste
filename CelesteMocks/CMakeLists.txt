set(LIBS
    Celeste)

cbt_build_project(NAME CelesteMocks FOLDER Celeste/Tests TYPE STATIC LIBS "${LIBS}")