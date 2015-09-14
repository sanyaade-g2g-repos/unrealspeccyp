# Building Sony PSP version #

## Using Linux (x86-64) ##

Download PSP SDK to your home dir & unpack it:
```
cd ~
wget http://downloads.sourceforge.net/project/minpspw/SDK%20%2B%20devpak/pspsdk%200.11.2/minpspw_0.11.2-amd64.tar.lzma
tar Jxvf minpspw_0.11.2-amd64.tar.lzma --strip=2
```

Prepare environment:
```
export PATH=~/pspsdk/bin:${PATH}
```

Checkout source code & build it:
```
mkdir usp
cd usp
svn checkout http://unrealspeccyp.googlecode.com/svn/trunk/ .
cd build/psp
make
```

After successfull build EBOOT.PBP will be placed in Release folder.