find_package(Freetype)

if(FREETYPE_FOUND)
    message("Found Freetype     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
endif()

find_path(FREETYPE_H_PATH_ft2build NAMES ft2build.h PATH_SUFFIXES include/freetype2 include freetype2)
find_path(FREETYPE_H_PATH_ftconfig NAMES freetype/config/ftconfig.h PATH_SUFFIXES freetype2)

find_library(FREETYPE_LIB NAMES freetype2 freetype libfreetype)
find_library(FREETYPE_LIB_DBG NAMES freetype_d libfreetype_d )

# set up output vars
if (FREETYPE_FOUND)
    set (FREETYPE_INCLUDE_DIR ${FREETYPE_H_PATH_ft2build} ${FREETYPE_H_PATH_ftconfig})
    set (FREETYPE_LIBRARIES ${FREETYPE_LIB})
else()
    set (FREETYPE_INCLUDE_DIR)
    set (FREETYPE_LIBRARIES)
endif()