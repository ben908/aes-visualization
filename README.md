This is an implementation of the AES encryption algorithm, as
specified by NIST, here: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf.
When running the app, the UI has some instructions in it.
But here are all the commands you have,
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
* If you press the Left Arrow, you will move to the previous state
  and the animation will stop
* If you press the Right Arrow, you will move to the next state
  and the animation will stop
* If you press `1` a new 128-bit key and 128-bit length message
will generate
* If you press `2` a new 192-bit key and 128-bit length message
will generate
* If you press `3` a new 256-bit key and 128-bit length message
will generate

With A Mouse:
* If you click someplace, the animation will
stop and go to the relative place on the time bar your cursor is
* If you drag your mouse around, you will be able to move
to previous or future states depending on the mouse's
  x-position is relative to the progress bar
  
To compile the app, run cmake, with the attacked `CMakeLists.txt`. To do so
run with the proper value for your computer for `<cinder file projects folder>`:
```
cmake.exe --build <cinder file projects folder>\final-project-ben908\cmake-build-debug --target aes-visualized
```
All messages are the same length, 128-bits, since the AES algorithm, 
despite the key length, encrypts messages in batches of 128-bits.

On startup, the default is a 128-bit key, which can be easily changed
the keyboard.

In the visualization all information is in Hex, not decimal,
including state values, the message, and the key. For brevity,
the message and key exclude the standard 0x of unsigned char hex
values.

