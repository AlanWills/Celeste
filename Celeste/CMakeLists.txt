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
    Log
    CelesteStl
    FileSystem
    FileSystemLua
    System
    SystemLua
    Dolce
    DolceLua)
    
set(TEST_LIBS
    CelesteLua
    CelesteMocks
    CelesteTestResources
    CelesteTestUtils)

cbt_build_project(
    NAME Celeste 
    FOLDER Celeste 
    TYPE SHARED 
    INCLUDES "${INCLUDES}" 
    LIBS "${LIBS}"
    TEST_LIBS "${TEST_LIBS}")

target_compile_definitions(Celeste PUBLIC -DGLM_FORCE_SILENT_WARNINGS)
