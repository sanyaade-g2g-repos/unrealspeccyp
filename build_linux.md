# Building in Linux environment (Debian/Ubuntu) #

Before building you need to install some developer tools:

```
sudo apt-get install subversion g++ make
```

Checkout latest version:
```
mkdir usp
cd usp
svn checkout http://unrealspeccyp.googlecode.com/svn/trunk/ .
cd build/linux
```

There are two versions you can build:
  1. [wxWidgets](http://www.wxwidgets.org) + [OpenGL](http://www.opengl.org) + [OpenAL](http://connect.creativelabs.com/openal) version.
  1. [SDL](http://www.libsdl.org) version.

For building first version type:
```
sudo apt-get install libwxgtk2.8-dev libgl1-mesa-dev libopenal-dev
make
```

For building SDL version type:
```
sudo apt-get install libsdl1.2-dev
make SDL=1
```

After successfull building binary will be placed in "Release" folder.
For launching emulator you need to place it near "usp/res" folder.
Type following commands:
```
cp Release/unreal_speccy_portable ../..
cd ../..
```

Launch it:
```
./unreal_speccy_portable
```