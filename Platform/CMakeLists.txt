cmake_minimum_required(VERSION 3.6)

build_library(NAME Platform FOLDER Celeste/Packages TYPE STATIC)

set_target_properties(Platform PROPERTIES LINKER_LANGUAGE CXX)