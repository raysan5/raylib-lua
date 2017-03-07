<img src="logo/raylib-lua_256x256.png" width=256>

# raylib-lua

Lua bindings for raylib, a simple and easy-to-use library to learn videogames programming (www.raylib.com)

raylib-lua binding is self-contained in a header-only single file: [rlua.h](src/rlua.h). Just include that file
in your project to allow loading and execution of raylib code written in Lua. Check [code examples](examples) for reference.

Together with the binding, raylib-lua launcher is also provided: [rlua](src/rlua.c). This launcher allows to run raylib-lua
programs from command line, or just *drag&drop* .lua files into *rlua.exe*.

Note that launcher can also be compiled for other platforms, just need to link with Lua library and raylib library.

# License

raylib-lua is licensed under an unmodified zlib/libpng license, which is an OSI-certified, 
BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.
	
*Copyright (c) 2016-2017 Ghassan Al-Mashareqa and Ramon Santamaria (@raysan5)*