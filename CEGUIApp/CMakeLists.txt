file(GLOB INCLUDE_FILES include/*.hpp)
file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB INCLUDE_HFILES include/*.h)

project(CEGUIApp)

set(DEPENDENCY_FILES 
    opengl32.lib
	${LIB_GLFW}/win64/lib/glfw3.lib
	${LIB_CEGUI}/win64/lib/CEGUICommonDialogs-9999_d.lib
	${LIB_CEGUI}/win64/lib/CEGUIBase-9999_d.lib
	${LIB_CEGUI}/win64/lib/CEGUIOpenGLRenderer-9999_d.lib
	${LIB_CEGUI}/win64/lib/CEGUICoreWindowRendererSet_d.lib
	${LIB_CEGUI}/win64/lib/CEGUISTBImageCodec_d.lib
	${LIB_CEGUI}/win64/lib/CEGUITinyXML2Parser_d.lib
	)				

set(SRC_FILES 
	${INCLUDE_FILES}
	${INCLUDE_HFILES}
	${SOURCE_FILES}
	)
				
INCLUDE_DIRECTORIES( BEFORE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${LIB_CEGUI}/include
  ${LIB_GLFW}/include
  ${LIB_GLM}/include
)				

link_directories(
				${LIB_CEGUI}/lib/x64
				)
 
add_executable(CEGUIApp ${SRC_FILES})

set(EXECUTABLE_OUTPUT_PATH "../../Bin")

file(COPY ${LIB_CEGUI}/datafiles DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../Bin)

############################copy dll #############################

file(GLOB LIB_GLFWDLL ${LIB_GLFW}/win64/bin/*.dll) 
file(GLOB LIB_CEGUIDLL ${LIB_CEGUI}/win64/bin/*.dll) 

set (ALLFILE
	${LIB_GLFWDLL}
	${LIB_CEGUIDLL}	
	)
 
add_custom_command(TARGET CEGUIApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${ALLFILE} ${CMAKE_CURRENT_SOURCE_DIR}/../Bin)

############################copy dll #############################


target_link_libraries(CEGUIApp PRIVATE ${DEPENDENCY_FILES})	

set_target_properties(CEGUIApp PROPERTIES RUNTIME_WORKING_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set_target_properties(CEGUIApp PROPERTIES RUNTIME_WORKING_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
set_target_properties(CEGUIApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
set_target_properties(CEGUIApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
set_target_properties(CEGUIApp PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
