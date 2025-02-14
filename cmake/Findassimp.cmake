find_path(
	assimp_INCLUDE_DIRS
	NAMES assimp/postprocess.h assimp/scene.h assimp/version.h assimp/config.h assimp/cimport.h
	PATHS /usr/local/include
	PATHS /usr/include/

  )

  find_library(
	assimp_LIBRARIES
	NAMES assimp
	PATHS /usr/local/lib/
	PATHS /usr/lib64/
	PATHS /usr/lib/
  )







