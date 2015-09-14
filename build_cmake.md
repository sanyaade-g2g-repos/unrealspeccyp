# Building Windows/Linux version using CMake #

## For Windows Users additional preparation steps are required ##

### wvWidgets + OpenAL + OpenGL version: ###

  * Download & build [wxWidgets](http://www.wxwidgets.org/downloads/).
  * Prepare environment:
```
set WXWIN=<path to the wxWidgets root>
```

  * Download & install [OpenAL SDK](http://connect.creativelabs.com/developer/Wiki/OpenAL%20SDK%20for%20Windows.aspx):
  * Prepare environment:
```
set OPENALDIR=<path to the OpenAL SDK root>
```

### SDL version: ###
  * Downdload [SDL development libraries](http://www.libsdl.org/download-1.2.php) and unpack them
  * Prepare environment:
```
set SDLDIR=<path to unpacked SDL development libraries>
```

## Building ##

  * checkout unreal speccy portable source code
```
svn checkout http://unrealspeccyp.googlecode.com/svn/trunk usp
cd usp\build\cmake
mkdir build
cd build
cmake ..
```