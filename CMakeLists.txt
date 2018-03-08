###############################################################################
cmake_minimum_required (VERSION 3.0)
project (VVR_OGL_LABORATORY)

###############################################################################

find_package(OpenGL REQUIRED)

# for rdm
set(CMAKE_EXPORT_COMPILE_COMMANDS=1)

# c++11
if(${CMAKE_CXX_COMPILER_ID} MATCHES GNU OR ${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  # Using C++11 on OSX requires using libc++ instead of libstd++.
  # libc++ is an implementation of the C++ standard library for OSX.
  if(APPLE)
    if(XCODE)
      set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
      set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
    endif()
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif()
endif()

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
    message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
    message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

###############################################################################

include_directories(
    external/glfw-3.1.2/include/GLFW/
    external/glm-0.9.7.1/
    external/glew-1.13.0/include/
    external/Simple-OpenGL-Image-Library/include/
    external/tinyxml2/include/
    external/tinyobjloader/include/
    .
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1130
    SOIL
    TINYXML2
)

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
)

###############################################################################
# lab06

add_executable(lab06 
    lab06/lab.cpp
    
    common/util.cpp
    common/util.h
    common/shader.cpp
    common/shader.h
    common/camera.cpp
    common/camera.h
    common/ModelLoader.cpp
    common/ModelLoader.h
    common/texture.cpp
    common/texture.h
    common/skeleton.cpp
    common/skeleton.h
    common/stb_image.h
    common/stb_image.c
    lab06/Box.cpp
    lab06/Box.h 
    lab06/Collision.cpp
    lab06/Collision.h
    lab06/RigidBody.cpp
    lab06/RigidBody.h
    lab06/Sphere.cpp
    lab06/Sphere.h

    
    lab06/StandardShading.fragmentshader
    lab06/StandardShading.vertexshader
    lab06/cube.fragmentshader
    lab06/cube.vertexshader
    lab06/shadertest.fragmentshader
    lab06/Shader.geometryshader
    lab06/Shader.vertexshader
    lab06/StandardShading.vertexshader
    lab06/StandardShading.fragmentshader
    lab06/StandardShading1.vertexshader
    lab06/StandardShading1.fragmentshader
)
target_link_libraries(lab06
    ${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(lab06 
    PROPERTIES 
    XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lab06/"
    PROJECT_LABEL "Lab 06 - Skinning and Animation"
    FOLDER "Exercise"
)
create_target_launcher(lab06 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lab06/")
create_default_target_launcher(lab06 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lab06/") 

###############################################################################

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )
SOURCE_GROUP(obj REGULAR_EXPRESSION ".*/.*obj$" )

###############################################################################
# copy 
if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

add_custom_command(
   TARGET lab06 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lab06${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/lab06/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

