# Change Log #
## Version 0.0.56 (OSX) ##
  * wxWidgets 3.0.0 used
  * all latest features included
  * window size/position stored
  * AY/YM option
  * sound chip stereo option
  * zoom/filtering option

## Version 0.0.55 (android) ##
  * russian localization added
  * .szx snapshots support
  * more .rzx replays supported (with .szx snapshots inside)
  * bugfix with encoding conversion when getting url's from VTRDOS/games

## Version 0.0.54 (google chrome NaCl) - on [Chrome Web Store](https://chrome.google.com/webstore/detail/jfkpejkiedieehgdecgcjbmcbpihimmb) ##
  * [RZX Archive](http://rzxarchive.co.uk) support
  * games & demos sections updated in [VTRDos](http://vtrdos.ru)

## Version 0.0.53 (iOS) ##
  * used custom ui
  * GLESv2 video acceleration
  * OpenAL audio

## Version 0.0.52 (symbian s60v3) ##
  * .fdi file format support
  * rzx replays support
  * auto play files option
  * reset to service rom option
  * true rom in 48k mode
  * memory leaks, uninitialized vars, etc. fixed
  * fixed crash when r/w beyond of disk image
  * bugfixes with snapshots loading
You need to install Open C++ plugin (read [readme\_symbian](readme_symbian.md) for more info)

## Version 0.0.51 (android) ##
  * VTRDOS source updated (games & demos sections)
  * Reset to service ROM option added

## Version 0.0.50 (windows) ##
  * .fdi file format support
  * .rzx replays support
  * gamepad support
  * auto play files option
  * reset to service rom option
  * mouse sensivity improved
  * true rom in 48k mode
  * memory leaks, uninitialized vars, etc. fixed
  * fixed crash when r/w beyond of disk image

## Version 0.0.49 (google chrome NaCl) - on [Chrome Web Store](https://chrome.google.com/webstore/detail/jfkpejkiedieehgdecgcjbmcbpihimmb) ##
  * mouse sensitivity improved
  * experimental joystick (gamepad) support (look at [readme\_chrome](readme_chrome.md) for more info)

## Version 0.0.48 (android) ##
  * authentic rubber keyboard view
  * bugfix with ugly pixels on the view edges

## Version 0.0.47 (google chrome NaCl) - on [Chrome Web Store](https://chrome.google.com/webstore/detail/jfkpejkiedieehgdecgcjbmcbpihimmb) ##
  * arm chromebooks support added
  * mouse locking improved
  * zoom modes option
  * filtering option
  * new GLESv2 shader

## Version 0.0.46 (android) ##
  * display progress bars on long time operations with web
  * cancelable file selector operations (get items/apply)
  * skip frames option implemented in GLESv1 view
  * correct "mono" volume in AY/YM to match other volumes
  * fixed crash when r/w beyond of disk image
  * download file to ".tmp" first
  * memory leaks, uninitialized vars, etc. fixed

## Version 0.0.45 (android) ##
  * bugfix with opening tape files when .rzx replay working
  * fixed crash while downloading file from web & display orientation change
  * bugfix: use hq keyboard & joystick on big screens or hdpi
  * android 2.1 compatibility (fix with latest NDK)

## Version 0.0.44 (android) ##
  * added http://zxaaa.untergrund.net/ huge demos database

## Version 0.0.43 (Raspberry Pi) ##
  * files sorting in open file dialog
  * select last opened file
  * new keys binded:
    * F12 - reset
    * F7 - pause
    * F2 - quick save
    * F3 - quick load
    * F5 - start/stop tape

## Version 0.0.42 (Raspberry Pi) ##
  * native GLES v2 render with indexed textures & uber-shader ;)
  * SDL for keyboard input & sound

## Version 0.0.41 (android) ##
  * rzx replays support
  * http://www.rzxarchive.co.uk/ browser
  * true rom in 48k mode
  * bugfix with R register emulation when interrupt occured
  * bugfixes with snapshots loading

## Version 0.0.40 (Dingoo A320) ##
  * perfect vsync, including ILI9338
  * menu & list cycling
  * fixed some bugs with sound

## Version 0.0.38 (Sony PSP) ##
  * PSP native platform support

## Version 0.0.37.0 - 0.0.37.1 (google chrome NaCl) - on [Chrome Web Store](https://chrome.google.com/webstore/detail/jfkpejkiedieehgdecgcjbmcbpihimmb) ##
  * android-style [vtrdos.ru](http://vtrdos.ru/) browser added
  * bugfix with crash when leaving fullscreen (waiting for chrome devs to fix mouse lock)
  * manifest migrated to version 2

## Version 0.0.36.1 (android) - on [Google Play](https://play.google.com/store/apps/details?id=app.usp) ##
  * [vtrdos.ru demos](http://vtrdos.ru/demos/demoz.htm) section browser improved

## Version 0.0.36 (android) ##
  * sound lag minimized
  * video filtering option added
  * sync by timer option added (smoother playback on devices with huge min. sound buffers)
  * A, B, X, Y keys binded (JXD s5110 support)
  * bugfix with cursor joystick (CAPS releasing when > 1 key pressed)

## Version 0.0.35 (android) ##
  * auto play files option
  * MIPS architecture support
  * fast scroller added in file selector lists
  * bugfix with sound buffer overrun

## Version 0.0.34.1 - 0.0.34.3 ([google chrome NaCl](readme_chrome.md)) ##
  * bugfix with invalid glEnable call
  * correct cleanup on instance destroying
  * full screen mode
  * mouse emulation in full screen mode
  * google chrome native client first launch

## Version 0.0.32 (android) ##
  * controls in landscape mode
  * .fdi file format support
  * x86 platform support
  * bugfix with multitouch (using joystick in hardcore games)
  * hw keys processing improved

## Version 0.0.31 (android) ##
  * motion events processing fixed (crash on tablets)

## Version 0.0.30 (symbian s60v3) ##
  * 'no border' mode (some kind of zoom)
  * skip frames '1' mode added
  * keyboard events processing improved

## Version 0.0.29 (android) ##
  * OpenGL ES rendering (hardware scaling)
  * new zooming options (none, fill screen, small border, no border)
  * tablets support (large screens)
  * skip frames & filtering options removed

## Version 0.0.28 (android) ##
  * sound mixer added

## Version 0.0.27 (android) ##
  * [vtrdos.ru](http://vtrdos.ru) & [worldofsperctum.org](http://www.worldofspectrum.org) browsers
  * bugfix with trimmed .trd's opening

## Version 0.0.26 (symbian) ##
  * Qt framework used (see [readme\_symbian](readme_symbian.md) for install it)
  * touch screens support added
  * S60v5 (9.4), Symbian<sup>^1</sup>, Symbian<sup>^3</sup> support (tested on N97, 5800 Express Music)

## Version 0.0.24, 0.0.25 (android) ##
  * onscreen full 40 keys zx-keyboard added
  * keyboard/joystick toggle by 'back' key
  * multi-touch support
  * joystick sensor (accelerometer) control
  * bugfix with hdpi screens

## Version 0.0.23 (android) ##
  * zooming & filtering options added
  * quit kills process
  * skip frame option
  * .apk size reduced

## Version 0.0.22 (android) ##
  * ad banners removed
  * compiled with most optimizations flags (-O3)
  * armeabi-v7a architecture support added (need to test)

## Version 0.0.21 (android) ##
  * bugfix with sorting in file open dialog
  * file sorting improved and in file selector dialog
  * select last file when file open dialog appears
  * display only supported file types in file open dialog
  * able to start/stop tape from preferences
  * tape traps added
  * fast tape option added
  * bugfix with audio buffer overrun when fast tape used
  * move to sd card feature added (android 2.2 and higher)

## Version 0.0.20 (android) ##
  * native menu/preferences/open file dialog added
  * full screen mode (320x240 devices in landscape mode support)
  * stop render thread when app not active (battery save)
  * prevent phone from locking when emulator active
  * auto start tape when file opened

## Version 0.0.19 ##
  * android platform launch

## Version 0.0.18 ##
  * screen flip/rotate option for any lcd controller (dingoo)
  * tv out support (dingoo)
  * file associations - .sim version (dingoo)
  * able to open files from SD card (dingoo)
  * ay stereo mode switch option
  * font/roms inside .app/.sim (dingoo)
  * quick save/load snapshot (dingoo & symbian)
  * bugfix: option "drive" not works

## Version 0.0.14 - 0.0.17 ##
  * full screen mode
  * 300% window size option
  * correct aspect ratio
  * filtering when window size not multiple of original
  * .png screenshots
  * new command line options

## Version 0.0.13 ##
  * symbian platform launch
  * config file support (load/store)
  * open files from .zip archives
  * 48k option
  * screen & joystick rotate option (symbian)
  * bugfix with emulator startup code (now start much faster on symbian & dingoo)

## Version 0.0.9 - 0.0.12 ##
  * added "true speed" option (50 Hz, jerky conversion to 60 Hz monitor, but sound looks better)
  * snapshots (.sna) storing (F2 key)
  * added file associations (Win/Linux)
  * added pause/resume function
  * added icon
  * added command line options
  * added about box
  * bugfix with snapshots loading, .z80 format support

## Version 0.0.8 ##
  * dingoo lcd ILI9325 support added

## Version 0.0.7 ##
  * dingoo version launch (ILI9331 lcd controller)

## Version 0.0.4 - 0.0.6 ##
  * mac (i386) version launch
  * linux (debian/ubuntu) i386 & amd64 versions tested
  * bugfix with beeper sound (Last Nynja 2)
  * mouse capturing improved

## Version 0.0.1 - 0.0.3 ##
  * first windows/linux launches