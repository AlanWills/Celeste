set(INCLUDES 
    ${THIRD_PARTY_DIR}/freealut/include
    ${THIRD_PARTY_DIR}/openal-soft/include/AL
    ${THIRD_PARTY_DIR}/SOIL2/src
    ${THIRD_PARTY_DIR}/curlpp/include)

set(LIBS 
    opengl32
    OpenAL
    alut
    assimp
    crossguid
    curlpp
    freetype
    glew
    glfw
    glm
    libcurl
    tinyxml2
    SOIL2
    StaticTypeInfo
    Platform
    Assert
    CrashHandler
    Log
	StringId
    CelesteStl
    FileSystem
    FileSystemScriptCommands
    System
    SystemScriptCommands
    Dolce
    DolceScriptCommands)
    
set(TEST_LIBS
    CelesteScriptCommands
    CelesteMocks
    CelesteTestResources
    CelesteTestUtils)
    
set(LUA_SCRIPTS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lua/Resources/Scripts")
string(REPLACE "/" "\\\\" LUA_SCRIPTS_DIRECTORY ${LUA_SCRIPTS_DIRECTORY})
configure_file("Lua/Include/ScriptCommands/CelesteScriptCommandsConfig.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/Lua/Include/ScriptCommands/CelesteScriptCommandsConfig.h" @ONLY)

cbt_build_project(
    NAME Celeste 
    FOLDER Celeste 
    TYPE SHARED 
    INCLUDES "${INCLUDES}" 
    LIBS "${LIBS}"
    TEST_LIBS "${TEST_LIBS}")

target_compile_definitions(Celeste PUBLIC -DGLM_FORCE_SILENT_WARNINGS)
