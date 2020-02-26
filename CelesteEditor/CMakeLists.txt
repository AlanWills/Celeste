cmake_minimum_required(VERSION 3.6)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#limit cmake to only make these configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set platforms we will generate the project on
#set(CMAKE_GENERATOR_PLATFORM "x64")

project(CelesteEngineEditor VERSION 0.1.0 LANGUAGES CSharp CXX)

include(CSharpUtilities)

##------------------------------ Bindings ------------------------------##
	
INCLUDE_EXTERNAL_MSPROJECT(BindingsKernel ${PROJECT_SOURCE_DIR}/../BindingsKernel/BindingsKernel.csproj)
set_target_properties(BindingsKernel PROPERTIES FOLDER Bindings)

INCLUDE_EXTERNAL_MSPROJECT(CelesteEngineBindingsLib ${PROJECT_SOURCE_DIR}/../CelesteEngineBindingsLib/CelesteEngineBindingsLib.csproj)
set_target_properties(CelesteEngineBindingsLib PROPERTIES FOLDER Bindings)

INCLUDE_EXTERNAL_MSPROJECT(CelesteEngineBindings ${PROJECT_SOURCE_DIR}/../CelesteEngineBindings/CelesteEngineBindings.csproj)
set_target_properties(CelesteEngineBindings PROPERTIES FOLDER Bindings)
add_dependencies(CelesteEngineBindings 
	BindingsKernel
	CelesteEngineBindingsLib)
	
##------------------------------ Editor ------------------------------##

INCLUDE_EXTERNAL_MSPROJECT(CelesteEngineEditorLibrary ${PROJECT_SOURCE_DIR}/../CelesteEngineEditorLibrary/CelesteEngineEditorLibrary.csproj)
set_target_properties(CelesteEngineEditorLibrary PROPERTIES FOLDER Editor)
add_dependencies(CelesteEngineEditorLibrary
	BindingsKernel
	CelesteEngineBindingsLib
	CelesteEngineBindings)

INCLUDE_EXTERNAL_MSPROJECT(CelesteEngineEditor ${PROJECT_SOURCE_DIR}/CelesteEngineEditor.csproj)
set_target_properties(CelesteEngineEditor PROPERTIES FOLDER Editor)
add_dependencies(CelesteEngineEditor
	BindingsKernel
	CelesteEngineBindingsLib
	CelesteEngineBindings
	CelesteEngineEditorLibrary)
	
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CelesteEngineEditor)