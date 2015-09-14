# Building S60v3 version #

## Using Linux ##

Build instructions based on [Martin Storsjö](http://martin.st/symbian/) GnuPoc package (EKA2 toolchain).

Download it to your home dir & unpack it:
```
cd ~
tar -zxvf ./gnupoc-package-1.21.tar.gz
```

Also [download](https://sourcery.mentor.com/sgpp/lite/arm/portal/subscription?@template=lite) Sourcery CodeBench Lite Edition for ARM (SymbianOS version)

unpack it to your home folder:

```
tar -jxvf ./arm-2011.09-67-arm-none-symbianelf-i686-pc-linux-gnu.tar.bz2
mv ./arm-2011.09 ./csl-gcc
```

Install GnuPoc package:
```
cd gnupoc-package-1.21/
cd tools/
./install_eka2_tools ~/csl-gcc/
```

[Download](http://www.developer.nokia.com/info/sw.nokia.com/id/ec866fab-4b76-49f6-b5a5-af0631419e9c/S60_All_in_One_SDKs.html) & install Symbian C++ SDK (3rd Edition FP2 v1.1):
```
cd ../sdks/
./install_gnupoc_s60_32 ../../S60_3rd_Edition_SDK_Feature_Pack_2_v1_1_en.zip ~/symbian-sdks/s60_32
```

[Download](http://developer.nokia.com/info/sw.nokia.com/id/91d89929-fb8c-4d66-bea0-227e42df9053/Open_C_SDK_Plug-In.html) & install Open C/C++ Plug-in
```
./install_openc_175_s60 ../../s60_open_c_cpp_plug_in_v1_7_en.zip ~/symbian-sdks/s60_32
```

Install build wrapper helper & prepare environment:
```
./install_wrapper ~/gnupoc
export PATH=~/gnupoc:${PATH}
export EPOCROOT=~/symbian-sdks/s60_32
export CC_INSTALL_PATH=~/csl-gcc
```

Go to [checkout](http://code.google.com/p/unrealspeccyp/source/checkout)'ed unreal\_speccy\_portable folder with symbian makefile & build it:
```
cd unreal_speccy_portable/build/symbian/
make pack
```

After successfull build & pack sis file will be placed in sis folder.