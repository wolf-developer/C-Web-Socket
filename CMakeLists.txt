cmake_minimum_required(VERSION 3.9)



## Use the variable PROJECT_NAME for changing the target name
set( PROJECT_NAME "DLInterface" )
## Set our project name
project(${PROJECT_NAME} CXX )

include(cmake/StandardProjectSettings.cmake)

# link this library to set the c++ standard /compile-time options requested
add_library(project_options INTERFACE)

target_compile_features(project_options INTERFACE cxx_std_17)
#target_compile_features(project_options INTERFACE)

set(CMAKE_CXX_FLAGS -pthread)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if (ENABLE_BUILD_WITH_TIME_TRACE)
    add_compile_definitions(project_options INTERFACE -ftime-trace)
  endif()
endif()
 
# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

#standard compiler warnings
include (cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)


#include(cmake/Sanitizers.cmake)
#enable_sanitizers(project_options)



add_subdirectory(src)
