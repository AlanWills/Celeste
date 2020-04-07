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
    Platform
    Assert
    Log
    CelesteStl
    FileSystem
    Lua
    Dolce)

build_library(NAME Celeste FOLDER Celeste TYPE SHARED INCLUDES "${INCLUDES}" LIBS "${LIBS}")

target_compile_definitions(Celeste PUBLIC -DGLM_FORCE_SILENT_WARNINGS PRIVATE -DBUILDING_CELESTE_ENGINE_DLL)
