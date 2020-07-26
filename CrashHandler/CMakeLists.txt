set(LIBS 
    StackWalker
    Log)

cbt_build_project(NAME CrashHandler FOLDER Celeste TYPE STATIC LIBS "${LIBS}")