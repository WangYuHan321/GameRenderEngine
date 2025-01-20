######################################################################
# CT_PBR BUILD SYSTEM
# Welcome to the CMake build system for CT_PBR.
# This is the main file where we prepare the general build environment
# and provide build configuration options.
######################################################################

cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CEGUI_BASE_LIBNAME CEGUIBase)
set(GAMERENDERENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

option( CEGUI_BUILD_DYNAMIC_CONFIGURATION "Dynamic libs to be built. Always true except for Android" TRUE)

configure_file( cegui/include/CEGUI/Version.h.in cegui/include/CEGUI/Version.h )
configure_file( cegui/include/CEGUI/Config.h.in cegui/include/CEGUI/Config.h )
configure_file( cegui/include/CEGUI/ModuleConfig.h.in cegui/include/CEGUI/ModuleConfig.h )

#配置cmake全局变量
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE__CXX_EXTENSIONS OFF)

#################################################################################

################################################################################
# Set up version information
################################################################################
set( CEGUI_VERSION_MAJOR 9999)
set( CEGUI_VERSION_MINOR 0)
set( CEGUI_VERSION_PATCH 0)
set( CEGUI_VERSION ${CEGUI_VERSION_MAJOR}.${CEGUI_VERSION_MINOR}.${CEGUI_VERSION_PATCH} )


set( CEGUI_PUGIXML_PARSER_LIBNAME CEGUIPugiXMLParser )
set( CEGUI_EXPAT_PARSER_LIBNAME CEGUIExpatParser )
set( CEGUI_TINYXML2_PARSER_LIBNAME CEGUITinyXML2Parser )
set( CEGUI_XERCES_PARSER_LIBNAME CEGUIXercesParser )
set( CEGUI_LIBXML2_PARSER_LIBNAME CEGUILibXMLParser )

# ImageCodec module names
set( CEGUI_SILLY_IMAGECODEC_LIBNAME CEGUISILLYImageCodec )
set( CEGUI_DEVIL_IMAGECODEC_LIBNAME CEGUIDevILImageCodec )
set( CEGUI_FREEIMAGE_IMAGECODEC_LIBNAME CEGUIFreeImageImageCodec )
set( CEGUI_CORONA_IMAGECODEC_LIBNAME CEGUICoronaImageCodec )
set( CEGUI_TGA_IMAGECODEC_LIBNAME CEGUITGAImageCodec )
set( CEGUI_STB_IMAGECODEC_LIBNAME CEGUISTBImageCodec )
set( CEGUI_PVR_IMAGECODEC_LIBNAME CEGUIPVRImageCodec )
set( CEGUI_SDL2_IMAGECODEC_LIBNAME CEGUISDL2ImageCodec )

set( CEGUI_BUILD_XMLPARSER_TINYXML2 true)
set( CEGUI_BUILD_IMAGECODEC_STB true)

set( CEGUI_STRING_CLASS "UTF-32" CACHE STRING "CEGUI offers three CEGUI::String class configurations
UTF-8 : ASCII, UTF-8 and UTF-32 aware, minimal storage, slightly less efficient, stores code units as char (std::string) internally - mind this fact when manipulating the String
UTF-32 : ASCII, UTF-8 and UTF-32 aware, stores 32 bit per character, stores code points as char32_t (std::u32string) internally
std : regular std::string used as CEGUI::String, not Unicode aware"
)
set_property(CACHE CEGUI_STRING_CLASS PROPERTY STRINGS "UTF-8" "UTF-32" "std")

if (CEGUI_STRING_CLASS STREQUAL "UTF-8")
    set(CEGUI_STRING_CLASS 1)
elseif (CEGUI_STRING_CLASS STREQUAL "std")
    set(CEGUI_STRING_CLASS 3)
else()
    set(CEGUI_STRING_CLASS 2) # UTF-32 by default
endif()

################################################################################
# Select one of the XML parser modules to be the default, warning if none are
# available.
################################################################################
set(CEGUI_DEFAULT_XMLPARSER_TOOLTIP "Specifies the XMLParser module to use as the default")

if (CEGUI_BUILD_XMLPARSER_PUGIXML)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "PugiXMLParser" CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_PUGIXML_PARSER_LIBNAME} CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
elseif (CEGUI_BUILD_XMLPARSER_EXPAT)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "ExpatParser" CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_EXPAT_PARSER_LIBNAME} CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
elseif (CEGUI_BUILD_XMLPARSER_XERCES)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "XercesParser" CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_XERCES_PARSER_LIBNAME} CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
elseif (CEGUI_BUILD_XMLPARSER_LIBXML2)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "LibXMLParser" CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_LIBXML2_PARSER_LIBNAME} CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
elseif (CEGUI_BUILD_XMLPARSER_TINYXML2)
    set( CEGUI_OPTION_DEFAULT_XMLPARSER "TinyXML2Parser" CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
    set( CEGUI_STATIC_XMLPARSER_MODULE ${CEGUI_TINYXML2_PARSER_LIBNAME} CACHE STRING "${CEGUI_DEFAULT_XMLPARSER_TOOLTIP}" )
else()
    message(WARNING "None of the XML parser modules are going to be built.
You should ensure that CEGUI_OPTION_DEFAULT_XMLPARSER is set to something
appropriate.")
endif()

set_property(CACHE CEGUI_OPTION_DEFAULT_XMLPARSER PROPERTY STRINGS "PugiXMLParser" "ExpatParser" "XercesParser" "LibXMLParser" "TinyXML2Parser")

################################################################################
# Select one of the image codec modules to be the default, warning if none are
# available.
################################################################################
if (CEGUI_BUILD_IMAGECODEC_SILLY)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "SILLYImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_SILLY_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_DEVIL)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "DevILImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_DEVIL_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_FREEIMAGE)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "FreeImageImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_FREEIMAGE_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_STB)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "STBImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_STB_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_CORONA)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "CoronaImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_CORONA_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_SDL2)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "SDL2ImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_SDL2_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_TGA)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "TGAImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_TGA_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
elseif (CEGUI_BUILD_IMAGECODEC_PVR)
    set( CEGUI_OPTION_DEFAULT_IMAGECODEC "PVRImageCodec" CACHE STRING "Specifies the ImageCodec module to use as the default" )
    set( CEGUI_STATIC_IMAGECODEC_MODULE ${CEGUI_PVR_IMAGECODEC_LIBNAME} CACHE STRING "Specifies image codec library to link to samples in static builds." )
else()
    message(WARNING "None of the image codec modules are going to be built.
You should ensure that CEGUI_OPTION_DEFAULT_IMAGECODEC is set to something
appropriate.")
endif()

set_property(CACHE CEGUI_OPTION_DEFAULT_IMAGECODEC PROPERTY STRINGS "SILLYImageCodec" "DevILImageCodec" "FreeImageImageCodec" "STBImageCodec" "CoronaImageCodec" "SDL2ImageCodec" "TGAImageCodec" "PVRImageCodec")

####################################################################################
project(Project)

if(WIN32)
	set(PLATFORM "Windows")
	add_compile_definitions(WIN32=1)	
elseif(UNIX)

endif()

include(cmake/files.cmake)
include(cmake/CEGUIMacros.cmake)

add_subdirectory(OpenGL)
add_subdirectory(CEGUIApp)
add_subdirectory(cegui/src)




