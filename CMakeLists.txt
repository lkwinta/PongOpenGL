#set to your own paths
set(CMAKE_PREFIX_PATH D:/Coding/GLFW/lib/cmake/glfw3)

#copy files macro
macro(copy_files SRC DEST)
    message(STATUS "Configuring directory ${DEST}")
    make_directory(${DEST})

    file(GLOB templateFiles RELATIVE ${SRC} ${SRC}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${SRC}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${DEST}/${templateFile}
                    COPYONLY)
        else()
            copy_files(${SRC}/${templateFile} ${DEST}/${templateFile})
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(copy_files)

cmake_minimum_required(VERSION 3.22)
project(PongOpenGL)

set(CMAKE_CXX_STANDARD 20)

#include header files
include_directories(headers)

#include glad and glm headers
include_directories(libraries/glad/include)
include_directories(libraries/glm)

#lis all source files
set(SOURCE_FILES libraries/glad/src/glad.c src/main.cpp src/Shader.cpp src/Camera2D.cpp headers/Camera2D.h src/Rectangle.cpp headers/Rectangle.h headers/Color.h headers/Shader.h src/Text.cpp headers/Text.h src/Font.cpp headers/Font.h src/Window.cpp headers/Window.h)

add_executable(PongOpenGL ${SOURCE_FILES})

#link GLFW
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(PongOpenGL glfw)

#add OpenGL libraries
find_package(OpenGL REQUIRED)
target_link_libraries(PongOpenGL OpenGL::GL)

#add freetype library
set(FREETYPE_DIR ${CMAKE_SOURCE_DIR}/libraries/freetype)
include_directories(${FREETYPE_DIR}/include)
configure_file(${FREETYPE_DIR}/lib/freetype.dll ${CMAKE_CURRENT_BINARY_DIR}/freetype.dll COPYONLY)
target_link_libraries(PongOpenGL ${FREETYPE_DIR}/lib/freetype.lib)

#copy shader files to output directory
copy_files(${CMAKE_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders)

#copy font file
copy_files(${CMAKE_SOURCE_DIR}/fonts ${CMAKE_CURRENT_BINARY_DIR}/fonts)