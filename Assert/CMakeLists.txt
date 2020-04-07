set(LIBS 
    Platform
    CelesteStl)

build_library(NAME Assert FOLDER Celeste/Packages TYPE SHARED LIBS "${LIBS}")

target_compile_definitions(Assert PRIVATE -DBUILDING_ASSERT_DLL)