################################################################################
# Custom cmake module for GameRenderEngine to find GLEW
################################################################################

find_path(GLEW_H_PATH NAMES GL/glew.h)
find_library(GLEW_LIB NAMES GLEW libGLEW glew glew32 libglew )


message("Found GLEW LIbrary !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
set (GLEW_INCLUDE_DIR ${GLEW_H_PATH})
set (GLEW_LIBRARIES ${GLEW_LIB})


