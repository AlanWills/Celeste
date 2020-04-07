set(LIBS 
    FileSystem)

build_library(NAME Log FOLDER Celeste/Packages TYPE SHARED LIBS "${LIBS}")

target_compile_definitions(Log PRIVATE -DBUILDING_LOG_DLL)