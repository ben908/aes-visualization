  For my final project I want to create a visualization of the advanced encryption
standard algorithm. I have some knowledge in about the history of cryptography
and ciphers but have never programmed one myself. I am interested in exploring
the AES algorithm since two of my prime interests in CS are web development and
security and AES is almost the epitome of the intersection of the two sectors.

  For a rough timeline of the project, I believe by the end of week one I 
should have the encryption implementation up and running and should have started 
on the decryption part. By the end of week two I hope to be done with visualizing
the encryption of a value with a key and hopefully have finished the decryption
part of the algorithm as well. For week three, I plan to finish implementing the
visualization of the decryption of a message and make it interactive by having people 
  able to move along a timeline at the top of the screen.

  If I were to finish the project early, the most I would spend my time on is
improving the visualization. In my opinion, one of the coolest parts about AES is
the column and row shifting using matrix manipulation. The algorithm is one of
the best demonstrations of the power of linear algebra and the visualization I
think would be cool to look at. Making edges in the display smoother and things
less boxy would be a goal.

  Testing of the algorithm itself I believe will be quite straight forward,
since there are already test vectors out there that given a known key, the
expected result is known. I just need to compare the cipher my code gives
compared to known good code. The goal is not to implement the most efficient
AES algorithm, but implement the AES algorithm in a way that I can understand
the process enough to be able to make a visualization of it. A stretch goal
would be to implement all variants of the AES algorithm using both 128-bit,
196-bit, and 256-bit keys and then letting the user choose how long to make
their key. However, at the moment, I am only planning on implementing the
128-bit one.
