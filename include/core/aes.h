#pragma once
#include <string>
#include <vector>

#include "constants.h"

namespace aes {
    
class AES {
 public:
  /**
   * Constants for 128-bit encryption, will add switch eventually to constructor
   * to say what size key using, 128, 196, or 256, and will set constants then
   */
  static const size_t kColumnCount = 4;
  
  /**
   * holds, all possible steps the algorithm takes, used to recording state history
   */
  enum step {
    Start,
    End,
    ByteSubstitution,
    RowShifting,
    ColumnMix,
    RoundKeyAddition,
    InvByteSubstitution,
    InvRowShift,
    InvColumnMix,
  };
  
  /**
   * destructor
   */
  ~AES();

  /**
   * Makes an instance of the class
   */
  AES(int keyLength);
  
  /**
   * Encrypts a block of chars
   * @param in, original message
   * @param out, pointer message will be saved to
   * @param key, key as char array pointer 
   */
  void Encrypt(unsigned char* in, unsigned char* out, unsigned char* key);
  
  /**
   * Encrypts a 128-bit block of data
   * @param message message to encrypt 
   * @param key key, atm just 128bit, planning to add 196 and 256 bit
   * @return pointer to the result
   */
  void EncryptBlock(const unsigned char* in, unsigned char* out);
  
  /**
   * Encrypts a block of chars
   * @param in, original message
   * @param out, pointer message will be saved to
   * @param key, key as char array pointer 
   */
  void Decrypt(unsigned char* in, unsigned char* out, unsigned char* key);
  
  /**
   * Decrypts a 128-bit block data
   * @param message message to decrypt 
   * @param key key, atm just 128bit, planning to add 196 and 256 bit
   * @return pointer to the result
   */
  void DecryptBlock(const unsigned char* in, unsigned char* out);

  /**
   * method that sets the key, used for testing
   * @param key, key to set key to
   */
  void SetKey(unsigned char key[16]);
  
  /**
   * get the pointer to the location of the key expansion
   * @return  pointer to the key's location
   */
  unsigned char* GetKeyExpansion();
  
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
   * variable that holds the history of all states
   */
  std::vector<std::tuple<step, unsigned char*>> all_states_; 
  
  /**
   * Helper that makes the key expansion
   * @param key original key
   * @param expanded_key place the saved key is saved to
   */
  void MakeKeyExpansion(const unsigned char* key, unsigned char* expanded_key) const;
  /**
   * Adds round key to state
   * @param current_key 
   */
  void AddRoundKey(const unsigned char* current_key);
  
  /**
   * Mixes columns through matrix multiplication
   */
  void MixColumns();
  
  /**
   * Mixes an individual column
   * @param column 
   */
  void MixColumn(size_t column);
  
  /**
   * Shifts all rows
   */
  void ShiftRows();
  
  /**
   * shifts individual row
   * @param row which row to shift
   * @param how_many how much to shift each row by
   */
  void ShiftRow(size_t row, size_t how_many);
  
  /**
   * sends bytes through s box
   */
  void SubBytes();
  
  /**
   * calculates the word to substitute in key expansion
   * @param word 
   */
  static void SubWord(unsigned char* word);
  
  /**
   * rots words of the key expansion
   * @param word 
   */
  static void RotWord(unsigned char* word);
  
  /**
   * rots individual key
   * @param to_change word to rotate
   * @param amount amount to rotate
   */
  static void RotateConstant(unsigned char *to_change, int amount);
  
  /**
   * xoring two words of the expanded key
   * @param in1 word1
   * @param in2 word2
   * @param output XORed result
   */
  static void xOrWords(const unsigned char *in1, const unsigned char *in2, unsigned char *output);
  
  /**
   * unmixes columns
   */
  void InverseMixColumns();
  
  /**
   * unmix individual column
   * @param column 
   */
  void InverseMixColumn(size_t column);
  
  /**
   * unshifts all rows
   */
  void InverseShiftRows();

  /**
   * shifts all rows
   */
  void InvSubBytes();

  /**
   * Current State
   */
  unsigned char **state_;
  
  /** Values stored throughout encryption*/
  unsigned char *key_;
  unsigned char *expanded_key_;
  size_t key_block_length_; //Nk
  size_t block_size_; //Nb
  size_t num_rounds_; //Nr
};

}  // namespace aes