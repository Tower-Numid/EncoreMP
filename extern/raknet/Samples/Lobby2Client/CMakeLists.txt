cmake_minimum_required(VERSION 2.6)
project(Lobby2Client)
include_directories(${CRABNETHEADERFILES} ./ ${CrabNet_SOURCE_DIR}/DependentExtensions/Lobby2 ${CrabNet_SOURCE_DIR}/DependentExtensions/Lobby2/Rooms)
FILE(GLOB LOBBYFILES ${CrabNet_SOURCE_DIR}/DependentExtensions/Lobby2/*.cpp ${CrabNet_SOURCE_DIR}/DependentExtensions/Lobby2/*.h)
SOURCE_GROUP(Main FILES "Lobby2ClientSample.cpp")
add_executable(Lobby2Client "Lobby2ClientSample.cpp" ${LOBBYFILES})
target_link_libraries(Lobby2Client ${CRABNET_COMMON_LIBS})
IF(WIN32 AND NOT UNIX)
	VSUBFOLDER(Lobby2Client "Samples/Lobby2")
ENDIF(WIN32 AND NOT UNIX)






