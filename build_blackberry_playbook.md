# QNX Playbook / BB10-Phone builds #


The Playbook build is identical to a Linux SDL build with a couple of tweaks...
2 libraries are required SDL and TouchControlOverlay (TCO). These libraries provide SDL1.2 with touch interface support and enable the porting of applications like this. IF your interested in general porting of apps to the QNX/BB10 platform there is a good article here:

General BB porting info [here](https://bdsc.webapps.blackberry.com/native/documentation/porting_overview_1970891_11.html):

  1. Download the latest NDK for blackberry playbook
    * typically the toolchain is installed under /opt/bbndk-2.0.0/ etc
    * Point your browser [here](https://bdsc.webapps.blackberry.com/native)
    * Install the NDK which is basically Java Eclipse modified for the QNX environment. The IDE is called Momentics and offers all the Eclipse functionality but tons of Profiling, Debugging and other crazy features. The toolchain is a modified GNU GCC with a special frontend tool called 'qcc' this frontend is invoked by momentics and all compilations.
  1. Get the 2 dependant libraries we need ...
    * To compile the emulator we are targetting SDL so we need
    * SDL library and a special touch interface library called TouchControlOverlay
    * THese are stored on github.com currently:
      * https://github.com/blackberry/TouchControlOverlay.git
      * https://github.com/blackberry/SDL.git
    * I recommend using the Momentics built in git import feature only because the makefile and pbcheck.sh scripts expect the code to be stored in the home directory but it's not critical you can 'git clone' the repo's anywhere.
  1. Compile the SDL and TCO libraries
    * If you imported the libraries using the Momentics IDE, they are normally stored in your home dir:
      * SDL will be here ->  ~/git/SDL
      * TCO will be here ->  ~/git/TouchControlOverlay
    * If you used Momentics Git import and default location you should end up with the following directories and objects:
      * $(HOME)/git/SDL/include
      * $(HOME)/git/SDL/Device-Release/libSDL12.so
      * $(HOME)/git/SDL/TouchControlOverlay/inc
      * $(HOME)/git/SDL/TouchControlOverlay/libTouchControlOverlay.so
    * Device-Relese is the general term for the ARM target build
    * Device-Simulator is the general term for the x86 simulator environment
  1. Set environment up for QNX compile
    * A small script called pbcheck.sh looks for TCO,SDL libraries in the default Momentics installation. pbcheck.sh will look for the paths in step 3. and report any errors. If there are no errors it will trigger the make to build the executable
    * You can modify the makefile directly and change the the paths to the SDL and TCO libraries also.
  1. type 'make'  to build the executable
  1. Packaging the "bar" file for installation on the device
    * cd bar
    * make

## bar packaging information: ##

This is Blackberry's equivalant of an Android .apk a self contained installation package that is given to users for installation. It requires signing to be deployed to users and this section gives some brief links and [help on how this is done](https://bdsc.webapps.blackberry.com/native/reference/com.qnx.doc.native_sdk.devguide/com.qnx.doc.native_sdk.devguide/topic/package_your_application_cmd_line.html):

A 'bar' file is a zip file  with a uniquely tagged/key'd collection of files defined by a file called bar-descriptor.xml. We use some extra tools from RIM package up all resources and files we need.  THe tools that perform this are blackberr-signer , blackberry-deploy and there are a number of other tools.

For developing on a real playbook you need a debug token which is an expiring 'key' that allows you to install native and other apps on the device and only the device with the token you request...

blackberry-debugtokenrequest

  1. We need to package up our files into a .bar file
    * blackberry-nativepackager
  1. We need to sign the package if it is to be used by other PB owners
    * blackberry-signer
  1. load it ...
    * blackberry-deploy