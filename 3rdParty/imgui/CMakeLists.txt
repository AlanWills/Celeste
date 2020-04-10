set(INCLUDES 
    ${THIRD_PARTY_DIR}/glew/include)

set(LIBS 
    opengl32
    glfw
	glew)

build_library(NAME imgui FOLDER "3rd Party" TYPE SHARED INCLUDES "${INCLUDES}" LIBS "${LIBS}")

target_compile_definitions(imgui PRIVATE -DBUILDING_IMGUI_DLL)