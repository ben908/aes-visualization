This is an implementation of the AES encryption algorithm, as
specified by NIST, here: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf. If running the app,
the UI has some information in it. But here are all the commands you have,
which are completed through either the keyboard or the mouse

For the Keyboard:
* If you Press `e` (encrypt) on a keyboard, the animation will run
through, at a constant pace, the encryption process for a
randomly generated message and key
* If you press `p` (pause) or `s` (stop), the encryption will
stop on the current step
* If you press `r` (resume) or `c` (continue), the encryption
will continue on
* If you press `d` (decrypt), the message will start decrypting
from that point
* If you press `1` a new 128-bit key and 128-bit length message
will generate
* If you press `2` a new 192-bit key and 128-bit length message
will generate
* If you press `3` a new 256-bit key and 128-bit length message
will generate

With A Mouse:
* If you click someplace, the automation encryption pace will
stop
* If you drag your mouse around, you will be able to move
to previous or future states depending on the mouse's
  x-position is relative to the progress bar
  
To compile the app, run cmake, with the attacked `CMakeLists.txt`

All messages are the same length, since the AES algorithm, 
despite the key length, encrypts messages in batches of 128-bits.

On startup, the default is a 128-bit key, which can be easily changed
the keyboard.

In the visualization all information is in Hex, not decimal,
including state values, the message, and the key

