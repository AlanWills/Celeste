set(INCLUDES 
    ${THIRD_PARTY_DIR}/glew/include)

set(LIBS 
    opengl32
    glfw
	glew)

cbt_build_project(NAME imgui FOLDER "3rd Party" TYPE SHARED INCLUDES "${INCLUDES}" LIBS "${LIBS}")