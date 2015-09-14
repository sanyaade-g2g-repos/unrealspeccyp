# Intro #
After some learning of Objective C/C++ i've done a quick port to iOS.
It uses GLESv2 renderer and OpenAL audio.

Here is a testing version for iPad's, iPhone's 3GS and higher - see [issue 49](https://code.google.com/p/unrealspeccyp/issues/detail?id=49).

Note: there is "True Speed" option like in desktop version. If you really want smooth scrollers on 60Hz iPad screen, you can disable "True Speed" option. But the sound will be ~20% faster.

# Installation #
  * Jailbreak your device.
  * scp ./unreal-speccy-portable`*`.deb root@<iphone ip>:/var/root
  * ssh as root and type dpkg -i ./unreal-speccy-portable`*`.deb.
  * Run 'uicache' from 'mobile' user.
  * Place ROMs to /User/Documents folder (for 'mobile' user).
  * Enjoy!

# Controls #
Tap left-upper corner for menu.
Tap right-upper corner for onscreen keyboard/joystick toggle.