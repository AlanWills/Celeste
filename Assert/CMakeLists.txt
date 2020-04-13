set(LIBS 
    Platform
    CelesteStl)

build_library(NAME Assert FOLDER Celeste TYPE SHARED LIBS "${LIBS}")

target_compile_definitions(Assert PRIVATE -DBUILDING_ASSERT_DLL)