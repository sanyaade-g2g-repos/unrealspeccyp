# Info #
Dingoo version 0.0.18 with any lcd controller support for Native OS.
Supported images: sna z80 tap tzx csw scl trd.
Images associated in OS: trd scl sna z80 tzx.
Reset only in service rom (madrom by AXLR).

For install, unzip archive in your dingoo folder.
Now resources placed inside .sim, you can delete "res" folder from previous version.
You must disconnect Dingoo from computer correctly, so associated file types will be refreshed in the OS.
For launching image, go to "interesting games" in OS, and select associated image.
Use "unreal\_speccy\_portable.scl" for simple launch (dummy image).

Something about ray mode/sync options.
If you really annoying from diagonal artifacts when screen flashes, try to setup ray sync.
First turn on ray sync option. Then, if screen flipped/rotated, adjust ray mirror option.
Ray sync now work only for LCD controller. Please turn off ray sync when connecting to TV.
For TV-out ray sync wait for the next release.

# Controls #
## Keys in emul ##
  * SELECT    - menu
  * START     - virtual keys
  * LT        - reset
  * RT        - change sound source
  * DPAD      - joystick
  * A         - joystick fire
  * B         - enter
  * X         - 1
  * Y         - space

  * SELECT+START – quit

## Keys in virt keys ##
  * A/B       - push key
  * Y         - toggle key
  * LT        - caps shift
  * RT        - symbol shift

## Keys in service rom (after reset) ##
  * U        - menu 128
  * S        - trdos 128
  * I        - basic 48
  * ENTER    - max petrov commander

# How to open image #

## tape (tap/tzx/csw) ##
  1. press reset
  1. open image in menu
  1. press ‘I’ to enter in basic
  1. type LOAD "" enter in virtual keys
  1. press start tape in menu
  1. choose tape sound source for sound (optional)

## disk (scl/trd) ##
  1. press reset
  1. open image in menu
  1. press enter to enter in max petrov commander
  1. select file and press enter