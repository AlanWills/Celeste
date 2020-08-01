set(LIBS 
    Dolce
    DolceScriptCommands
    Celeste
    CelesteScriptCommands)
    
cbt_build_project(
    NAME TestGame 
    FOLDER "Celeste" 
    TYPE EXECUTABLE 
    LIBS "${LIBS}")

set_target_properties(TestGame PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${WORKING_DIR})