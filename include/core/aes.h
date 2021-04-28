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
   * Makes an instance of the class
   */
  AES(int keyLength);
  
  void Encrypt(unsigned char* in, unsigned char* out, unsigned char* key);
  
  /**
   * Encrypts data
   * @param message message to encrypt 
   * @param key key, atm just 128bit, planning to add 196 and 256 bit
   * @return pointer to the result
   */
  void EncryptBlock(const unsigned char in[], unsigned char out[]);

  /**
   * Decrypts data
   * @param message message to decrypt 
   * @param key key, atm just 128bit, planning to add 196 and 256 bit
   * @return pointer to the result
   */
  void DecryptBlock(const unsigned char in[], unsigned char out[]);

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
  std::vector<std::tuple<step, unsigned char*>> all_states_; 
  
  void MakeKeyExpansion(const unsigned char key[], unsigned char expanded_key[]) const;
  void AddRoundKey(const unsigned char* current_key);
  
  void MixColumns();
  void MixColumn(size_t column);
  void ShiftRows();
  void ShiftRow(size_t row, size_t how_many);
  void SubBytes();
  static void SubWord(unsigned char* word);
  static void RotWord(unsigned char* word);
  static void RotateConstant(unsigned char *to_change, int amount);
  static unsigned char xtime(unsigned char in);
  static void xOrWords(const unsigned char *in1, const unsigned char *in2, unsigned char *output);
  
  void InverseMixColumns();
  void InverseMixColumn(size_t column);
  void InverseShiftRows();

  void InvSubBytes();
  
  unsigned char **state_;
  
  unsigned char *message_;
  unsigned char *key_;
  unsigned char *expanded_key_;
  size_t key_block_length_; //Nk
  size_t block_size_; //Nb
  size_t num_rounds_; //Nr
};

}  // namespace aes