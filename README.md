# Development notes
```
# Libraries
cd external
hg clone https://hg.libsdl.org/SDL
hg clone https://hg.libsdl.org/SDL_image
```

```
# Linux
cmake ..
make
make install

# MacOS
/Applications/CMake.app/Contents/bin/cmake
make
make install

# Windows - Cross-Compile
cmake -DCMAKE_TOOLCHAIN_FILE=../windows-toolchain.cmake ..
make
make install
```