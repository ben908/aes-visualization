#pragma once
#include <string>

#include "constants.h"

namespace aes {
    
class AES {
 public:
  /**
   * Constants for 128-bit encryption, will add switch eventually to constructor
   * to say what size key using, 128, 196, or 256, and will set constants then
   */
  static const size_t kColumnCount = 4;
  //todo: might need to change these constants if going above 128bit encryption
  static const size_t kWordCount = 4;
  static const size_t kNumberRound = 10;
  static const size_t kBlockLength = 128;

  /**
   * Makes an instance of the class
   */
  AES();

  /**
   * Encrypts data
   * @param message message to encrypt 
   * @param key key, atm just 128bit, planning to add 196 and 256 bit
   * @return pointer to the result
   */
  unsigned char* Encrypt(unsigned char message[], unsigned char key[]);

  /**
   * Decrypts data
   * @param message message to decrypt 
   * @param key key, atm just 128bit, planning to add 196 and 256 bit
   * @return pointer to the result
   */
  unsigned char* Decrypt(unsigned char message[], unsigned char key[]);

  /**
   * method that sets the key, used for testing
   * @param key, key to set key to
   */
  void SetKey(unsigned char key[16]);
  
  /**
   * allows to access individual parts of the cipher key expansion
   * @param word_number, words are the columns in the current state block
   *                    this allows you to access the key expansion value that
   *                    will be XORed with a given column
   * @return  pointer to the key's location
   */
  unsigned char* GetKeyExpansion(size_t word_number);
  
  /**
   * allows the current state block to be changed, used for testing
   * @param state 
   */
  void SetState(unsigned char state[4][4]);
  
  /**
   * Gets the current state block
   * @return the state 
   */
  unsigned char* GetState();
  
  /**
   * Helpful debugger that lets me print the state as the program executes
   * so i can check each step is going well.
   */
  void PrintState();
  
  /**
   * Helper method that multiplies two unsigned char values in the Galois
   * finite field (the 256 bit field, which is the size of unsigned chars)
   * @param val0 first value
   * @param val1 second value
   * @return result as unsigned char
   */
  static unsigned char FiniteMultiply(unsigned char val0, unsigned char val1);
  
 private:
  /**
   * Creates the key expansion, saves in private variable
   */
  void MakeKeyExpansion(); 
  
  /**
   * adds the round key to current state block
   */
  void AddRoundKey();
  
  /**
   * Mixes the columns through by hand, longwise matrix multiplication
   */
  void MixColumns();
  
  /**
   * mixes individual columns
   * @param column column to mix
   */
  void MixColumn(size_t column);
  
  /**
   * shits all rows by the correct values
   */
  void ShiftRows();
  
  /**
   * shifts a given row by a certain amount
   * @param row, row to shift
   * @param how_many, how many positions to shift row
   */
  void ShiftRow(size_t row, size_t how_many);
  
  /**
   * Method that switches current state values through s box (substitute box)
   */
  void SubBytes();
  
  /**
   * switches the key expansion word to new value, also through s box
   */
  void SubWord();
  
  /**
   * Another adjustment to the words that are XORed with the colmns, made by
   * rotating the values in the words
   */
  void RotWords();
  
  /**
   * Undoes the mixing of columns
   */
  void InverseMixColumns();
  
  /**
   * unmixes an individual column
   * @param column, which column to unmix
   */
  void InverseMixColumn(size_t column);
  
  /**
   * undoes the shift of rows
   */
  void InverseShiftRows();
  
  /**
   * unshifts an individual row
   * @param row, which row to change
   * @param how_many, how much to change by
   */
  void InverseShiftRow(size_t row, size_t how_many);
  
  /**
   * Puts current state through the inverse s box that was orginally used
   */
  void InvSubBytes();
  
  
  /** True if try to encrypt message, false if decrypting */
  bool is_encrypting;

  /**
   * current board state
   */
  unsigned char state[4][4];
  
  /**
   * Calculated key expansion
   */
  unsigned char* key_expansion[kWordCount * (kNumberRound + 1)];
    
};

}  // namespace aes