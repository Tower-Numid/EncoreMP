cmake_minimum_required(VERSION 2.6)
GETCURRENTFOLDER()
FINDPORTAUDIO()
project(${current_folder})

IF(WIN32 AND NOT UNIX)
	FILE(GLOB ALL_CPP_SRCS *.cpp ${CrabNet_SOURCE_DIR}/DependentExtensions/RakVoice.cpp)
	FILE(GLOB ALL_HEADER_SRCS *.h ${CrabNet_SOURCE_DIR}/DependentExtensions/RakVoice.h)
	FILE(GLOB PORTAUDIOFILES ${portaudio_SOURCE_DIR}/pa_common/*.c ${portaudio_SOURCE_DIR}/pa_win_wmme/pa_win_wmme.c ${portaudio_SOURCE_DIR}/pa_common/*.h)
	FILE(GLOB SPEEXFILES ${speex_SOURCE_DIR}/win32/*.h ${speex_SOURCE_DIR}/include/*.h ${speex_SOURCE_DIR}/libspeex/*.h ${speex_SOURCE_DIR}/include/speex/*.h ${speex_SOURCE_DIR}/libspeex/*.c)
	LIST(REMOVE_ITEM SPEEXFILES 
	  ${speex_SOURCE_DIR}/libspeex/pcm_wrapper.h)
	LIST(REMOVE_ITEM SPEEXFILES 
	  ${speex_SOURCE_DIR}/libspeex/pcm_wrapper.c)
	SOURCE_GROUP(Speex FILES ${SPEEXFILES})
	SOURCE_GROUP(PortAudio FILES ${PORTAUDIOFILES})
	ADDCPPDEF(HAVE_CONFIG_H)
	include_directories(${CRABNETHEADERFILES} ./ ${PORTAUDIO_INCLUDE_DIR} ${CrabNet_SOURCE_DIR}/DependentExtensions ${speex_SOURCE_DIR}/include ${portaudio_SOURCE_DIR} ${speex_SOURCE_DIR}/win32)
	add_executable(${current_folder} ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} ${PORTAUDIOFILES} ${SPEEXFILES} readme.txt)
	target_link_libraries(${current_folder} ${CRABNET_COMMON_LIBS})
	VSUBFOLDER(${current_folder} Samples/Voice)
ELSE(WIN32 AND NOT UNIX)
	FILE(GLOB ALL_CPP_SRCS *.cpp)
	FILE(GLOB ALL_HEADER_SRCS *.h)
	include_directories(${CRABNETHEADERFILES} ./ ${PORTAUDIO_INCLUDE_DIR} ${CrabNet_SOURCE_DIR}/DependentExtensions)
	add_executable(${current_folder} ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS})
	target_link_libraries(${current_folder} ${CRABNET_COMMON_LIBS} ${PORTAUDIO_LIBRARIES} LibRakVoice)
ENDIF(WIN32 AND NOT UNIX)





