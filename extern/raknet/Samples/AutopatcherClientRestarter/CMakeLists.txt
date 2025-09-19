cmake_minimum_required(VERSION 2.6)
project(AutopatcherClientRestarter)
include_directories(${CRABNETHEADERFILES} ./)
add_executable(AutopatcherClientRestarter "main.cpp" "readme.txt")
target_link_libraries(AutopatcherClientRestarter ${CRABNET_COMMON_LIBS})
VSUBFOLDER(AutopatcherClientRestarter "Samples/AutoPatcher/Client")





