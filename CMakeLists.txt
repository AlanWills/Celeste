cmake_minimum_required(VERSION 3.6)

include(${CMAKE_CURRENT_SOURCE_DIR}/BuildTools/CMakeLists.txt)

##---------------------------- Globals ----------------------------##
if (NOT DEFINED BUILDS_DIR)
    set(BUILDS_DIR ${PROJECT_SOURCE_DIR}/Build/${CMAKE_VS_PLATFORM_NAME})
endif()

set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty)
##---------------------------- end Globals ----------------------------##


##---------------------------- Third Party ----------------------------##
add_subdirectory(${THIRD_PARTY_DIR} ${THIRD_PARTY_DIR}/build ${EXCLUDE})
#---------------------------- end Third Party ----------------------------##


##------------------------------ Platform ------------------------------##
set(PLATFORM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Platform)
add_subdirectory(${PLATFORM_DIR} ${PLATFORM_DIR}/Build)
##------------------------------ end Platform ------------------------------##


##------------------------------ CelesteStl ------------------------------##
set(CELESTE_STL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CelesteStl)
add_subdirectory(${CELESTE_STL_DIR} ${CELESTE_STL_DIR}/Build)
##------------------------------ end Assert ------------------------------##


##------------------------------ Assert ------------------------------##
set(ASSERT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Assert)
add_subdirectory(${ASSERT_DIR} ${ASSERT_DIR}/Build)

set_target_properties(Assert PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})
##------------------------------ end Assert ------------------------------##


##------------------------------ Log ------------------------------##
set(LOG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Log)
add_subdirectory(${LOG_DIR} ${LOG_DIR}/Build)

set_target_properties(Log PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})
##------------------------------ end Assert ------------------------------##


##---------------------------- FileSystem ----------------------------##
set(FILE_SYSTEM_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/FileSystem")
add_subdirectory(${FILE_SYSTEM_PROJECT_DIR} ${FILE_SYSTEM_PROJECT_DIR}/Build ${EXCLUDE})
#---------------------------- end FileSystem ----------------------------##


##---------------------------- Lua ----------------------------##
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Lua" "${CMAKE_CURRENT_SOURCE_DIR}/Lua/Build" ${EXCLUDE})

set_target_properties(Lua PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})
#---------------------------- end Lua ----------------------------##


##------------------------------ Dolce ------------------------------##
set(DOLCE_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dolce")
add_subdirectory(${DOLCE_PROJECT_DIR} ${DOLCE_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(Dolce PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ DolceLua ------------------------------##
set(DOLCE_LUA_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DolceLua")
add_subdirectory(${DOLCE_LUA_PROJECT_DIR} ${DOLCE_LUA_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(DolceLua PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ Celeste ------------------------------##
set(CELESTE_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Celeste)
add_subdirectory(${CELESTE_PROJECT_DIR} ${CELESTE_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(Celeste PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ CelesteLua ------------------------------##
set(CELESTE_LUA_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CelesteLua")
add_subdirectory(${CELESTE_LUA_PROJECT_DIR} ${CELESTE_LUA_PROJECT_DIR}/Build ${EXCLUDE})

set_target_properties(CelesteLua PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ Celeste Mocks Project ------------------------------##
set(CELESTE_LUA_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CelesteMocks")
add_subdirectory(${CELESTE_LUA_PROJECT_DIR} ${CELESTE_LUA_PROJECT_DIR}/Build)

set_target_properties(CelesteMocks PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ Celeste Test Resources Project ------------------------------##
set(CELESTE_TEST_RESOURCES_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CelesteTestResources")
add_subdirectory(${CELESTE_TEST_RESOURCES_PROJECT_DIR} ${CELESTE_TEST_RESOURCES_PROJECT_DIR}/Build)

set_target_properties(CelesteTestResources PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ Test Utils Project ------------------------------##
set(TEST_UTILS_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/TestUtils")
add_subdirectory(${TEST_UTILS_PROJECT_DIR} ${TEST_UTILS_PROJECT_DIR}/Build)

set_target_properties(TestUtils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ Celeste Test Utils Project ------------------------------##
set(CELESTE_TEST_UTILS_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CelesteTestUtils")
add_subdirectory(${CELESTE_TEST_UTILS_PROJECT_DIR} ${CELESTE_TEST_UTILS_PROJECT_DIR}/Build)

set_target_properties(CelesteTestUtils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ Test Celeste Project ------------------------------##
set(TEST_CELESTE_PROJECT_DIR ${CELESTE_PROJECT_DIR}/Tests)
add_subdirectory(${TEST_CELESTE_PROJECT_DIR} ${TEST_CELESTE_PROJECT_DIR}/Build)

set_target_properties(TestCeleste PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILDS_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${BUILDS_DIR})


##------------------------------ Dev Tools ------------------------------##
#INCLUDE_EXTERNAL_MSPROJECT(GuidGenerator ${CMAKE_CURRENT_SOURCE_DIR}/GuidGenerator/GuidGenerator.vcxproj)
#set_target_properties(GuidGenerator PROPERTIES FOLDER DevTools)


##------------------------------ Bindings ------------------------------##
#INCLUDE_EXTERNAL_MSPROJECT(BindingsGenerator ${CMAKE_CURRENT_SOURCE_DIR}/BindingsGenerator/BindingsGenerator.vcxproj)
#set_target_properties(BindingsGenerator PROPERTIES FOLDER Bindings)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteBindingsGenerator ${CMAKE_CURRENT_SOURCE_DIR}/CelesteBindingsGenerator/CelesteBindingsGenerator.vcxproj)
#set_target_properties(CelesteBindingsGenerator PROPERTIES FOLDER Bindings)
#add_dependencies(CelesteBindingsGenerator 
#	BindingsGenerator)
	
#INCLUDE_EXTERNAL_MSPROJECT(BindingsKernel ${CMAKE_CURRENT_SOURCE_DIR}/BindingsKernel/BindingsKernel.csproj)
#set_target_properties(BindingsKernel PROPERTIES FOLDER Bindings)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteBindingsLib ${CMAKE_CURRENT_SOURCE_DIR}/CelesteBindingsLib/CelesteBindingsLib.csproj)
#set_target_properties(CelesteBindingsLib PROPERTIES FOLDER Bindings)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteBindings ${CMAKE_CURRENT_SOURCE_DIR}/CelesteBindings/CelesteBindings.csproj)
#set_target_properties(CelesteBindings PROPERTIES FOLDER Bindings)
#add_dependencies(CelesteBindings 
#	BindingsKernel
#	CelesteBindingsLib)
	

##------------------------------ Editor ------------------------------##
#INCLUDE_EXTERNAL_MSPROJECT(CelesteEditorLibrary ${CMAKE_CURRENT_SOURCE_DIR}/CelesteEditorLibrary/CelesteEditorLibrary.csproj)
#set_target_properties(CelesteEditorLibrary PROPERTIES FOLDER Editor)
#add_dependencies(CelesteEditorLibrary
#	BindingsKernel
#	CelesteBindingsLib
#	CelesteBindings)

#INCLUDE_EXTERNAL_MSPROJECT(CelesteEditor ${CMAKE_CURRENT_SOURCE_DIR}/CelesteEditor/CelesteEditor.csproj)
#set_target_properties(CelesteEditor PROPERTIES FOLDER Editor)
#add_dependencies(CelesteEditor
#	BindingsKernel
#	CelesteBindingsLib
#	CelesteBindings
#	CelesteEditorLibrary)