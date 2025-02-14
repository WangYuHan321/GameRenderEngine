
find_path(GLFW_H_PATH NAMES GLFW/glfw3.h glfw3.h)
find_library(GLFW_LIB NAMES lglfw3 glfw )
message("Found GLFW LIbrary !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
set (GLFW_INCLUDE_DIR ${GLFW_H_PATH})
set (GLFW_LIBRARIES ${GLFW_LIB})
