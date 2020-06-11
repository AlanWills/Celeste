cmake_minimum_required(VERSION 3.6)

##---------------------------- Globals ----------------------------##
if (NOT DEFINED BUILDS_DIR)
    set(BUILDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dll/${CMAKE_VS_PLATFORM_NAME})
endif()

SET(CMAKE_DEBUG_POSTFIX "" CACHE STRING "" FORCE)
set(THIRD_PARTY_FOLDER "3rd Party")
set(THIRD_PARTY_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_VS_PLATFORM_NAME})
##---------------------------- end Globals ----------------------------##


##---------------------------- assimp ----------------------------##
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS ON)
set(ASSIMP_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assimp")
SET(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
SET(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${ASSIMP_PROJECT_DIR} ${ASSIMP_PROJECT_DIR}/build EXCLUDE_FROM_ALL)
set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")

set_target_properties(assimp PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

set_target_properties(IrrXML PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})

set_target_properties(zlibstatic PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})

set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})
#---------------------------- end assimp ----------------------------##


##---------------------------- crossguid ----------------------------##
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS OFF)
set(CROSSGUID_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/crossguid")
SET(CROSSGUID_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CROSSGUID_PROJECT_DIR} ${CROSSGUID_PROJECT_DIR}/build)
set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")

set_target_properties(crossguid PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end crossguid ----------------------------##


##---------------------------- curl ----------------------------##
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS ON)
set(CURL_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/curl")
set(CURL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/curl/include")
add_subdirectory(${CURL_PROJECT_DIR} ${CURL_PROJECT_DIR}/build EXCLUDE_FROM_ALL)
set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")

set_target_properties(libcurl PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end curl ----------------------------##


##---------------------------- curlpp ----------------------------##
set(CURLPP_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/curlpp")
set(CURL_LIBRARY ${THIRD_PARTY_LIB_DIR}/${CMAKE_BUILD_TYPE}/libcurl_imp.lib)

add_subdirectory(${CURLPP_PROJECT_DIR} ${CURLPP_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(curlpp PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

add_dependencies(curlpp libcurl)
##---------------------------- end curlpp ----------------------------##


##---------------------------- dirent ----------------------------##
set(DIRENT_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dirent")
add_subdirectory(${DIRENT_PROJECT_DIR} ${DIRENT_PROJECT_DIR}/build EXCLUDE_FROM_ALL)
##---------------------------- end dirent ----------------------------##


##---------------------------- ffmpeg ----------------------------##
set(FFMPEG_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg")
set(AVCODEC_PROJECT_NAME avcodec)
set(AVFORMAT_PROJECT_NAME avformat)
set(AVUTIL_PROJECT_NAME avutil)
set(SWSCALE_PROJECT_NAME swscale)
##---------------------------- end ffmpeg ----------------------------##


##---------------------------- openal-soft ----------------------------##
set(OPENAL_SOFT_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/openal-soft")
set(OPENAL_INCLUDE_DIR ${OPENAL_SOFT_PROJECT_DIR}/include/AL)
set(OPENAL_LIBRARY ${THIRD_PARTY_LIB_DIR}/${CMAKE_BUILD_TYPE}/OpenAL32.lib)
set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${OPENAL_SOFT_PROJECT_DIR} ${OPENAL_SOFT_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(OpenAL PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

set_target_properties(build_version PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})

set_target_properties(common PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})

set_target_properties(native-tools PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})
#---------------------------- end openal-soft ----------------------------##


##---------------------------- freealut ----------------------------##
set(FREEALUT_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/freealut")
SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
SET(BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${FREEALUT_PROJECT_DIR} ${FREEALUT_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(alut PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

    add_dependencies(alut OpenAL)
#---------------------------- end freealut ----------------------------##


##---------------------------- freetype2 ----------------------------##
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS OFF)
set(FREETYPE2_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/freetype2")
add_subdirectory(${FREETYPE2_PROJECT_DIR} ${FREETYPE2_PROJECT_DIR}/build EXCLUDE_FROM_ALL)
set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")

set_target_properties(freetype PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end freetype2 ----------------------------##


##---------------------------- glew ----------------------------##
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS ON)
set(GLEW_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glew")
add_subdirectory(${GLEW_PROJECT_DIR} ${GLEW_PROJECT_DIR}/build EXCLUDE_FROM_ALL)
set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")

set_target_properties(glew PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

set_target_properties(glewinfo PROPERTIES 
    FOLDER ${THIRD_PARTY_FOLDER})
##---------------------------- end glew ----------------------------##


##---------------------------- glfw ----------------------------##
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS ON)
set(GLFW_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glfw")
add_subdirectory(${GLFW_PROJECT_DIR} ${GLFW_PROJECT_DIR}/build)
set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")

set_target_properties(glfw PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
##---------------------------- end glfw ----------------------------##


##---------------------------- glm ----------------------------##
set(BUILD_STATIC_LIBS_SAVED "${BUILD_STATIC_LIBS}")
set(BUILD_STATIC_LIBS ON)
set(GLM_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm")
add_subdirectory(${GLM_PROJECT_DIR} ${GLM_PROJECT_DIR}/build)
set(BUILD_STATIC_LIBS "${BUILD_STATIC_LIBS_SAVED}")

set_target_properties(glm_static PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

##---------------------------- end glm ----------------------------##


##---------------------------- imgui ----------------------------##
set(IMGUI_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
add_subdirectory(${IMGUI_PROJECT_DIR} ${IMGUI_PROJECT_DIR}/build EXCLUDE_FROM_ALL)

set_target_properties(imgui PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end lua ----------------------------##


##---------------------------- lua ----------------------------##
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
set(BUILD_SHARED_LIBS OFF)
set(LUA_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lua")
add_subdirectory(${LUA_PROJECT_DIR} ${LUA_PROJECT_DIR}/build EXCLUDE_FROM_ALL)
set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")

set_target_properties(liblua PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})

target_compile_definitions(liblua PRIVATE -DLUA_BUILD_AS_DLL)
#---------------------------- end lua ----------------------------##


##---------------------------- SOIL2 ----------------------------##
set(SOIL2_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SOIL2")
add_subdirectory(${SOIL2_PROJECT_DIR} ${SOIL2_PROJECT_DIR}/build)

set_target_properties(SOIL2 PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end lua ----------------------------##


##---------------------------- sol2 ----------------------------##
set(SOL2_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sol2")
add_subdirectory(${SOL2_PROJECT_DIR} ${SOL2_PROJECT_DIR}/build)
#---------------------------- end sol2 ----------------------------##


##---------------------------- StaticTypeInfo ----------------------------##
set(STATIC_TYPE_INFO_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/StaticTypeInfo")
add_subdirectory(${STATIC_TYPE_INFO_PROJECT_DIR} ${STATIC_TYPE_INFO_PROJECT_DIR}/build EXCLUDE_FROM_ALL)
#---------------------------- end sol2 ----------------------------##


##---------------------------- tinyxml2 ----------------------------##
set(TINYXML2_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2")
add_subdirectory(${TINYXML2_PROJECT_DIR} ${TINYXML2_PROJECT_DIR}/build)

set_target_properties(tinyxml2 PROPERTIES
    FOLDER ${THIRD_PARTY_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_LIB_DIR})
#---------------------------- end tinyxml2 ----------------------------##