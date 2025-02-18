if(WIN32)

elseif(APPLE)
	include(cmake/FindFreetype.cmake)
	include(cmake/Findassimp.cmake)
	include(cmake/FindGLEW.cmake)
	include(cmake/FindGLFW.cmake)
	include(cmake/FindOpenGL.cmake)
elseif(UNIX)

endif()






