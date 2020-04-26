set(LIBS 
    Platform
    CelesteStl)

cbt_build_project(NAME Assert FOLDER Celeste TYPE SHARED LIBS "${LIBS}")