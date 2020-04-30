set(LIBS
    StaticTypeInfo)

cbt_build_project(NAME System FOLDER Celeste TYPE STATIC LIBS "${LIBS}")

set_target_properties(System PROPERTIES LINKER_LANGUAGE CXX)