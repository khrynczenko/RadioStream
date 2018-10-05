
# RadioStream
**master** [![Build Status](https://travis-ci.org/JenioPY/RadioStream.svg?branch=master)](https://travis-ci.org/JenioPY/RadioStream) **develop** [![Build Status](https://travis-ci.org/JenioPY/RadioStream.svg?branch=develop)](https://travis-ci.org/JenioPY/RadioStream)  
  
Simple, fast and light-weight internet radio player for desktop. 


RadioStream is still in really early phase of development.
Do not consider master branch to be stable release, for now it contains
the fundamental features in their basic form.
Latest tested release goes on the master branch, while develop branch 
is used for creating new content before realeasing.
You should branch from develop if You want to make changes.
For more information about project (instructions, code, design decisions etc.)
consider visiting [project wiki](https://github.com/JenioPY/RadioStream/wiki).

## How to build
### Requirements
- CMake 3.11
- Compiler with C++17 support ( tested with gcc-8 / Visual Studio 15 2017)

The easiest way to build is using CMake.
Just open terminal in the project directory and run:

`cmake`

**info:** Because dependencies are downloaded by CMake it can take quite long time when 
running for the first time (about 5-20 minutes depending on connection).


**Visual Studio**


`cmake -G "Visual Studio 15 2017 Win64"`

If you have any problems You should post an issue.

## Dependencies
nana https://github.com/cnjinhao/nana  
BASS https://www.un4seen.com/  
JSON for Modern C++ https://nlohmann.github.io/json/  
POCO C++ Libraries https://pocoproject.org/index.html
