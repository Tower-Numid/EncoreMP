cmake_minimum_required(VERSION 2.6)


IF(WIN32 AND NOT UNIX)
	GETCURRENTFOLDER()
	FINDPORTAUDIO()
	FINDDSOUND()
	project(${current_folder})
	FILE(GLOB ALL_CPP_SRCS *.cpp ${CrabNet_SOURCE_DIR}/DependentExtensions/RakVoice.cpp)
	FILE(GLOB ALL_HEADER_SRCS *.h ${CrabNet_SOURCE_DIR}/DependentExtensions/RakVoice.h)
	FILE(GLOB SPEEXFILES ${speex_SOURCE_DIR}/win32/*.h ${speex_SOURCE_DIR}/include/*.h ${speex_SOURCE_DIR}/libspeex/*.h ${speex_SOURCE_DIR}/include/speex/*.h ${speex_SOURCE_DIR}/libspeex/*.c)
	FINDREADMES()
	LIST(REMOVE_ITEM SPEEXFILES 
	  ${speex_SOURCE_DIR}/libspeex/pcm_wrapper.h)
	LIST(REMOVE_ITEM SPEEXFILES 
	  ${speex_SOURCE_DIR}/libspeex/pcm_wrapper.c)
	SOURCE_GROUP(Speex FILES ${SPEEXFILES})
	ADDCPPDEF(HAVE_CONFIG_H)
	ADDCPPDEF(_UNICODE)
	ADDCPPDEF(UNICODE)
	include_directories(${CRABNETHEADERFILES} ./ ${PORTAUDIO_INCLUDE_DIR} ${CrabNet_SOURCE_DIR}/DependentExtensions ${speex_SOURCE_DIR}/include ${portaudio_SOURCE_DIR} ${speex_SOURCE_DIR}/win32 ${DSOUND_INCLUDE_DIR})
	add_executable(${current_folder} ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} ${SPEEXFILES} ${READMES})
	target_link_libraries(${current_folder} ${CRABNET_COMMON_LIBS} winmm.lib ${DSOUND_LIBRARIES})
	VSUBFOLDER(${current_folder} Samples/Voice)
ENDIF(WIN32 AND NOT UNIX)





