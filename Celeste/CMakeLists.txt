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

file(RELATIVE_PATH CELESTE_DIR_FROM_WD ${WORKING_DIR} ${CELESTE_DIR})

if (NOT CELESTE_DIR_FROM_WD)
    # Bit of a hack because configure_file will not define the variable if it is the empty string
    # This is annoying because the empty string is a valid value here
    set(CELESTE_DIR_FROM_WD "\"\"")
else()
    string(REPLACE "/" "\\\\" CELESTE_DIR_FROM_WD ${CELESTE_DIR_FROM_WD})
endif()

configure_file("Include/CelesteConfig.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/Include/CelesteConfig.h" @ONLY)

cbt_build_project(
    NAME Celeste 
    FOLDER Celeste 
    TYPE SHARED 
    INCLUDES "${INCLUDES}" 
    LIBS "${LIBS}"
    TEST_LIBS "${TEST_LIBS}")

target_compile_definitions(Celeste PUBLIC -DGLM_FORCE_SILENT_WARNINGS)
