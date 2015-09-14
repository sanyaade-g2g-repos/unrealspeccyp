# Building windows version #

## Using mingw32 (x86) ##

  * download mingw compiler here: http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/rubenvb/gcc-4.8-release/i686-w64-mingw32-gcc-4.8.0-win32_rubenvb.7z/download
  * unpack it.
  * open new console (mingw build console) and set PATH variable to unpacked mingw32\bin folder:
```
set PATH=%PATH%;<path to mingw32\bin>
```
  * or just run
```
mingw32\mingw32env.cmd
```
  * download [wx widgets](http://www.wxwidgets.org/) here: http://sourceforge.net/projects/wxwindows/files/2.8.12/wxWidgets-2.8.12.zip/download?use_mirror=ignum
  * create “lib” folder. the path can’t contain spaces (due to buggy wx widgets makefiles).
  * unpack wx widgets into “lib”
  * open "lib\wxWidgets-2.8.12\include\wx\msw\setup.h"
  * change #defines of **wxUSE\_UNICODE**, **wxUSE\_GLCANVAS** from 0 to 1, also change **wxUSE\_HTML**, **wxUSE\_MS\_HTML\_HELP**, **wxUSE\_WXHTML\_HELP**, **wxUSE\_RICHTEXT**, **wxUSE\_EXCEPTIONS** from 1 to 0.
  * cd to “lib\wxWidgets-2.8.12\build\msw\” folder in the mingw build console, then type:
```
mingw32-make -f makefile.gcc SHARED=0 UNICODE=1 USE_OPENGL=1 USE_EXCEPTIONS=0 USE_HTML=0 USE_MEDIA=0 BUILD=release
```

  * download and install OpenAL SDK: http://connect.creativelabs.com/openal/Downloads/OpenAL11CoreSDK.zip
  * create folder “lib\oal” then copy “include” folder from installed SDK to this folder. Also copy “libs” folder from installed SDK to “lib\oal” folder.

  * checkout unreal speccy portable source code to the folder near “lib” folder
```
svn checkout http://unrealspeccyp.googlecode.com/svn/trunk usp
cd usp\build\win
mingw32-make
```