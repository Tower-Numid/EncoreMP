cmake_minimum_required(VERSION 2.6)
project("Chat Example")
include_directories(${CRABNETHEADERFILES} ./)
add_executable(ChatServer "Chat Example Server.cpp" readme.txt)
add_executable(ChatClient "Chat Example Client.cpp" readme.txt)

target_link_libraries(ChatServer ${CRABNET_COMMON_LIBS})
VSUBFOLDER(ChatServer "Samples")

target_link_libraries(ChatClient ${CRABNET_COMMON_LIBS})
VSUBFOLDER(ChatClient "Samples")






