CrabNet 1.001
============

Copyright (c) 2014, Oculus VR, Inc. (original RakNet)

Copyright (c) 2016-2018, TES3MP Team

Note
----
This fork is not compatible with the original RakNet.

Your compiler should support C++11.

You also need CMake 3.5 to generate project files.

Package notes
-------------
* The Help directory contains index.html, which provides full documentation and help
* The Source directory contain all files required for the core of CrabNet and is used
if you want to use the source in your program or create your own dll
* The Samples directory contains code samples and one game using an older version of RakNet.
The code samples each demonstrate one feature of CrabNet. The game samples cover several features.

Linux
-----
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j4
```

Windows
-------
If you have CMake in ``PATH`` environment:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target RakNetLibStatic \
                --config Release \
                --clean-first
```
