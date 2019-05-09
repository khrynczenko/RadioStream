
# RadioStream  
Branches:  
**master** [![Build Status](https://travis-ci.org/khrynczenko/RadioStream.svg?branch=master)](https://travis-ci.org/khrynczenko/RadioStream)  
**develop** [![Build Status](https://travis-ci.org/khrynczenko/RadioStream.svg?branch=develop)](https://travis-ci.org/khrynczenko/RadioStream)  

Simple, fast and light-weight internet radio player for desktop. 


RadioStream is still in really early phase of development.
Do not consider master branch to be stable release, for now it contains
the fundamental features in their basic form.
Latest tested release goes on the master branch, while develop branch 
is used for creating new content before releasing.
You should branch from develop if You want to make changes.

## How to build
### Requirements
- CMake 3.12
- Compiler with C++17 support ( tested with gcc-8 / Visual Studio 15 2017)

The easiest way to build is using CMake.
Just open terminal in the project directory and run:

`cmake`

### Info when building for the first time
First time CMake is run the dependencies are going to be downloaded. 
This may take some time depending on your connection. The first time you build 
the project dependencies are also going to get build so it might also take quite 
a while to finish. Consecutive builds should be much quicker.


**Visual Studio**

`cmake -G "Visual Studio 15 2017 Win64"`

If you have any problems You should post an issue.

## Dependencies
nana https://github.com/cnjinhao/nana  
BASS https://www.un4seen.com/  
JSON for Modern C++ https://nlohmann.github.io/json/  
POCO C++ Libraries https://pocoproject.org/index.html

Screens:  
![search-page](static/search-page.png)
![play-page](static/play-page.png)