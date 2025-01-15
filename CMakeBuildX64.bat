SET ASSIMP="%~dp0\OpenGL\ThirdLib\Assimp"
SET FreeType="%~dp0\OpenGL\ThirdLib\freetype"
SET GLM="%~dp0\OpenGL\ThirdLib\glm"
SET GLFW="%~dp0\OpenGL\ThirdLib\glfw"
SET GLEW="%~dp0\OpenGL\ThirdLib\glew"
SET IMGUI="%~dp0\OpenGL\ThirdLib\ImGui"
SET STB_IMAGE="%~dp0\OpenGL\ThirdLib\stb_image"
SET THIRD_LUA="%~dp0\OpenGL\ThirdLib\lua"
SET IRRKLANG="%~dp0\OpenGL\ThirdLib\irrklang"
SET VULKAN="%~dp0\OpenGL\ThirdLib\vulkan"
SET GFSDK="%~dp0\OpenGL\ThirdLib\gfsdk"

SET LIB_CEGUI="%~dp0\ThridParty\cegui"
SET LIB_GLFW="%~dp0\ThridParty\glfw"
SET LIB_GLM="%~dp0\ThridParty\glm"

mkdir build_x64
cd build_x64
cmake.exe -L -DCMAKE_CXX_FLAGS_RELWITHDEBINFO:STRING="/MD /Zi /Od /Ob0 /D NDEBUG /D VLD_FORCE_ENABLE /fp:fast" -DCMAKE_C_FLAGS_RELWITHDEBINFO:STRING="/MD /Zi /Od /Ob0 /D NDEBUG /D VLD_FORCE_ENABLE /fp:fast" -DCMAKE_CXX_FLAGS_RELEASE:STRING="/MD /O2 /Ob2 /Zi /D NDEBUG /fp:fast" -DX64:BOOL=ON -DASSIMP:PATH=%ASSIMP% -DFreeType:PATH=%FreeType% -DGLM:PATH=%GLM% -DGLFW:PATH=%GLFW% -DIMGUI:PATH=%IMGUI% -DGLEW:PATH=%GLEW% -DTHIRD_LUA:PATH=%THIRD_LUA% -DIRRKLANG:PATH=%IRRKLANG% -DSTB_IMAGE:PATH=%STB_IMAGE% -DVULKAN:PATH=%VULKAN% -DGFSDK:PATH=%GFSDK% -DLIB_CEGUI:PATH=%LIB_CEGUI% -DLIB_GLFW:PATH=%LIB_GLFW% -DLIB_GLM:PATH=%LIB_GLM% ../ -G"Visual Studio 17 2022" -A"x64"