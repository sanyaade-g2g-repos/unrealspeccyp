# Building wxWidgets version for Mac #

[Download](https://sourceforge.net/projects/wxwindows/files/3.0.0/wxWidgets-3.0.0.tar.bz2/download) wxWidgets library.
Extract archive and build it.
```
./configure --enable-monolithic --disable-shared
make
```

[Checkout](http://code.google.com/p/unrealspeccyp/source/checkout) source code near extracted wxWidgets folder.

Open project file unreal\_speccy\_portable/build/mac/usp.xcodeproj in Xcode.

Press Run button.