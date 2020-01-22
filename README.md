# Development notes
```
# Libraries
cd external
hg clone https://hg.libsdl.org/SDL
hg clone https://hg.libsdl.org/SDL_image
git clone https://github.com/KhronosGroup/Vulkan-Headers.git
cd Vulkan-Headers
git checkout sdk-1.1.106

git clone https://github.com/KhronosGroup/Vulkan-Loader.git
cd Vulkan-Loader
git checkout sdk-1.1.106
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

# Windows - Cross-Compile from linux
## Vulkan
dnf install mingw64-vulkan-tools mingw64-vulkan-loader mingw64-vulkan-headers mingw64-vulkan-validation-layers
## Other
dnf install mingw64-zlib
cmake -DCMAKE_TOOLCHAIN_FILE=../windows-toolchain.cmake ..
make
make install

# Windows
cmake ..
cmake --build .
cmake --install . --prefix install --config Debug
```

## Notes
### Vulkan
- FindVulkan.cmake cannot find mingw64 vulkan from dnf. Path's must be in lower case e.g $ENV{VULKAN_SDK}/Lib" -> $ENV{VULKAN_SDK}/lib"
- Vulkan-Headers and Vulkan-Loader must be the same release/branch. Master on both will most likly yield wierd result.
- Vulkan-Loader + MinGW64: WinSock2.h -> winsock2.h, Cfgmgr32.h -> cfgmgr32.h
- Vulkan-Loader: asm_offset.exe must run to generate gen_defines.asm, a.k.a cannot cross-compile Vulkan-Loader from source code.