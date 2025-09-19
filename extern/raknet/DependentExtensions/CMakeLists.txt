cmake_minimum_required(VERSION 2.6)

option( CRABNET_ENABLE_EXTENSIONS 				"Enable extension projects that might need specific dependencies." TRUE )
option( CRABNET_EXTENSION_USEMYSQL 				"Enable extensions using MySQL" 		TRUE )
option( CRABNET_EXTENSION_USEPOSTGRESQL			"Enable extensions using PostgreSQL" 	TRUE )
option( CRABNET_EXTENSION_USEBOOST				"Enable extensions using Boost" 		TRUE )
option( CRABNET_EXTENSION_USESPEEX				"Enable extensions using Speex" 		TRUE )
option( CRABNET_EXTENSION_USEIRRLICHT			"Enable extensions using Irrlicht" 		TRUE )
option( CRABNET_EXTENSION_USEIRRKLANG			"Enable extensions using Irkklang" 		TRUE )
option( CRABNET_EXTENSION_USEOGRE3D				"Enable extensions using Ogre3D" 		TRUE )

option( CRABNET_EXTENSION_Autopatcher			"Enable Autopatcher extension" 			TRUE )


add_subdirectory("bzip2-1.0.6")
add_subdirectory("XML")

if( CRABNET_ENABLE_EXTENSIONS )
	IF(CRABNET_EXTENSION_USEMYSQL )
		add_subdirectory(MySQLInterface)
	ENDIF() 

	IF(CRABNET_EXTENSION_USEPOSTGRESQL)
		add_subdirectory(PostgreSQLInterface)
	ENDIF() 

endif()

if( CRABNET_EXTENSION_Autopatcher )
	add_subdirectory(Autopatcher)
endif()

IF (WIN32 AND NOT UNIX)
	IF(NOT ${CMAKE_GENERATOR} STREQUAL "MSYS Makefiles")
		add_subdirectory(portaudio_v18_1)
	ENDIF(NOT ${CMAKE_GENERATOR} STREQUAL "MSYS Makefiles")
	add_subdirectory(speex-1.1.12)
ENDIF(WIN32 AND NOT UNIX)

if( CRABNET_ENABLE_EXTENSIONS )

	IF(CRABNET_EXTENSION_USEBOOST)
		add_subdirectory(RPC3)
	ENDIF() 

endif()

IF(NOT WIN32 AND UNIX)
	IF(CRABNET_EXTENSION_USESPEEX AND CRABNET_ENABLE_EXTENSIONS)
		FINDSPEEX()
		include_directories(${CRABNETHEADERFILES} ${SPEEX_INCLUDE_DIRS})
		add_library(LibRakVoice STATIC RakVoice.h RakVoice.cpp)
		target_link_libraries(LibRakVoice ${CRABNET_COMMON_LIBS} ${SPEEX_LIBRARIES})
	ENDIF() 
ENDIF()

if( CRABNET_ENABLE_EXTENSIONS )

	IF( CRABNET_EXTENSION_USEIRRLICHT AND CRABNET_EXTENSION_USEIRRKLANG )
		add_subdirectory(IrrlichtDemo)
	ENDIF()

	IF( CRABNET_EXTENSION_USEOGRE3D )
		add_subdirectory(Ogre3DInterpDemo)
	ENDIF()

endif()



