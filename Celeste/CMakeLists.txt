set(INCLUDES 
    ${FREEALUT_PROJECT_DIR}/include
    ${OPENAL_INCLUDE_DIR}
    ${SOIL2_PROJECT_DIR}/src
    ${CURLPP_PROJECT_DIR}/include)

set(LIBS 
    opengl32
    OpenAL
    alut
    assimp
    curlpp
    crossguid
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
