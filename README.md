# plotcraft

A c++ plotting library with a matplotlib like interface.  The library is designed to be platform independent and framework independent. 
It can be used together with various ui/drawing frameworks which support basic drawing operations (e.g. line, rect, ..). This makes it especially
suitable for cli only applications.

![Alt text](/docs/showcase1.png "Optional title")

:warning: The project is currently in the development phase. Breaking changes will happen quite often.

The project consists of the library itself and an example application which uses WxWidgets as presentation framework. 

## Prerequisites

The sample application uses wxWidgets. This must be provided to be able to compile it. All other dependencies are provided through git submodules. 

## Building from Git Sources

    $ git clone --recurse-submodules https://github.com/DocDilbert/plotcraft.git
    $ cd plotcraft && mkdir build && cd build
    $ cmake .. && make -j

Please use ``--recurse-submodules`` option with the initial git clone. If you had already cloned the repository without this option, please run git submodule update ``--init`` to also get all 3rd party libraries code. In the future you will also need to use git submodule update whenever any of the submodules change.

## Licenses for 3rd-party libraries used in plotcraft

This library contains parts of the "Perlin Simplex Noise C++ Implementation" from Sébastien Rombauts which is licensed under the MIT License. Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)



