# Once found, defines:
#  LuaJit_FOUND
#  LuaJit_INCLUDE_DIRS
#  LuaJit_LIBRARIES

include(LibFindMacros)

libfind_pkg_detect(LuaJit luajit
        FIND_PATH luajit.h
        PATH_SUFFIXES luajit
        FIND_LIBRARY NAMES luajit-5.1 luajit
        )

libfind_process(LuaJit)