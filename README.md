<img align="left" src="logo/raylib-lua_256x256.png" width=256>

Lua bindings for raylib, a simple and easy-to-use library to enjoy videogames programming (www.raylib.com)

raylib-lua binding is self-contained in a header-only file: [raylib-lua.h](src/raylib-lua.h). Just include that file
in your project to allow loading and execution of raylib code written in Lua. Check [code examples](examples) for reference.

raylib-lua could be useful for prototyping, tools development, graphic applications, embedded systems and education.

<br><br>

**WARNING: Current raylib-lua binding is outdated! It's based on raylib 1.7 and it's being ported to raylib 2.x. Not ready yet, sorry.**

### rLuaLauncher

A raylib-lua launcher is also provided: [rluaLauncher](tools/rLuaLauncher/rlualauncher.c). This launcher allows you to run raylib-lua
programs from command line, or just with *drag & drop* of .lua files into *rlualauncher.exe*.

Note that launcher can also be compiled for other platforms, just need to link with Lua library and raylib library. 
For more details, just check comments on sources.

### rLuaParser

In an effort to automatize raylib-lua binding generation I created [rLuaParser](https://github.com/raysan5/raylib-lua/tree/master/tools/rLuaParser), unfortunately there are several side cases that are not solved yet on the parsing, specially when dealing with opaque data types. Any help or contribution is welcome!

# License

raylib-lua is licensed under an unmodified zlib/libpng license, which is an OSI-certified, 
BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.
	
*Copyright (c) 2016-2019 Ghassan Al-Mashareqa and Ramon Santamaria ([@raysan5](https://twitter.com/raysan5))*
