set(LIBS
    spdlog
    Platform)

cbt_build_project(NAME Log FOLDER Celeste TYPE SHARED LIBS "${LIBS}")