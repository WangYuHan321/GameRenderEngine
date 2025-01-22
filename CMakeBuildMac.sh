#!/bin/sh
export curPath=${PWD}

export ASSIMP=$curPath/OpenGL/ThirdLib/Assimp
export FreeType=$curPath/OpenGL/ThirdLib/freetype
export GLM=$curPath/OpenGL/ThirdLib/glm
export GLFW=$curPath/OpenGL/ThirdLib/glfw
export GLEW=$curPath/OpenGL/ThirdLib/glew
export IMGUI=$curPath/OpenGL/ThirdLib/ImGui

export STB_IMAGE=$curPath/OpenGL/ThirdLib/stb_image
export THIRD_LUA=$curPath/OpenGL/ThirdLib/lua
export IRRKLANG=$curPath/OpenGL/ThirdLib/irrklang
export VULKAN=$curPath/OpenGL/ThirdLib/vulkan
export GFSDK=$curPath/OpenGL/ThirdLib/gfsdk

export LIB_CEGUI=$curPath/ThridParty/cegui
export LIB_GLFW=$curPath/ThridParty/glfw
export LIB_GLM=$curPath/ThridParty/glm

mkdir build_x64
cd build_x64
cmake -L -DCMAKE_CXX_FLAGS_RELWITHDEBINFO:STRING="/MD /Zi /Od /Ob0 /D NDEBUG /D VLD_FORCE_ENABLE /fp:fast" -DCMAKE_C_FLAGS_RELWITHDEBINFO:STRING="/MD /Zi /Od /Ob0 /D NDEBUG /D VLD_FORCE_ENABLE /fp:fast" -DCMAKE_CXX_FLAGS_RELEASE:STRING="/MD /O2 /Ob2 /Zi /D NDEBUG /fp:fast" -DX64:BOOL=ON -DASSIMP:PATH=$ASSIMP -DFreeType:PATH=$FreeType -DGLM:PATH=$GLM -DGLFW:PATH=$GLFW -DIMGUI:PATH=$IMGUI -DGLEW:PATH=$GLEW -DTHIRD_LUA:PATH=$THIRD_LUA -DIRRKLANG:PATH=$IRRKLANG -DSTB_IMAGE:PATH=$STB_IMAGE -DVULKAN:PATH=$VULKAN -DGFSDK:PATH=$GFSDK -DLIB_CEGUI:PATH=$LIB_CEGUI -DLIB_GLFW:PATH=$LIB_GLFW -DLIB_GLM:PATH=$LIB_GLM ../ -G"Xcode"
