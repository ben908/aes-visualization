#include <core/aes.h>

#include <functional>
#include <iostream>

namespace aes {

AES::AES(int keyLength) {
  block_size_ = 4;
  if (keyLength == 128) {
    key_block_length_ = 4;
    num_rounds_ = 10;
    return;
  }
  if (keyLength == 192) {
    key_block_length_ = 6;
    num_rounds_ = 12;
    return;
  }
  if (keyLength == 256) {
    key_block_length_ = 8;
    num_rounds_ = 14;
    return;
  }
  throw std::bad_function_call();
}

void AES::Encrypt(unsigned char* in, unsigned char* out, unsigned char* message_key) {
  message_ = in;
  key_ = message_key;
  MakeKeyExpansion(key_, expanded_key_);
  
  size_t length = strlen(reinterpret_cast<const char *>(in));
  size_t padded_length = length;
  if ((padded_length % 16) != 0) {
    padded_length = (padded_length / 16 + 1) * 16;
  }
}

//in length is 4*block_size_, out same, word is block_size_*(num_rounds_ + 1)
void AES::EncryptBlock(const unsigned char* in, unsigned char* out) {
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < block_size_; j++) {
      state_[i][j] = in[i + 4 * j];
    }
  }
  AddRoundKey(expanded_key_);
  for (size_t current_round = 1; current_round < num_rounds_; ++current_round) {
    SubBytes();
    ShiftRows();
    MixColumns();
    AddRoundKey(expanded_key_ + current_round * 4 * block_size_);
  }
  
  SubBytes();
  ShiftRows();
  AddRoundKey(expanded_key_ + num_rounds_ * 4 * block_size_);
}

void AES::DecryptBlock(const unsigned char *in, unsigned char *out) {
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      state_[i][j] =  in[i + 4 * j];
    }
  }
  
  AddRoundKey(expanded_key_ + num_rounds_ * 4 * block_size_);
  
  for (size_t current_round = num_rounds_ - 1; current_round > 0; --current_round) {
    InvSubBytes();
    InverseShiftRows();
    AddRoundKey(expanded_key_ + current_round * 4 * block_size_);
    InverseMixColumns();
  }
  
  InvSubBytes();
  InverseShiftRows();
  AddRoundKey(expanded_key_);
  
}

void AES::SubBytes() {
  for (size_t i = 0; i < kColumnCount; ++i) {
    for (size_t j = 0; j < kColumnCount; ++j) {
      unsigned char t = state_[i][j];
      state_[i][j] = kS_Box[t / 16][t % 16];
    }
  }
}

void AES::InvSubBytes() {
  for (size_t i = 0; i < kColumnCount; ++i) {
    for (size_t j = 0; j < kColumnCount; ++j) {
      unsigned char t = state_[i][j];
      state_[i][j] = kS_Box[t / 16][t % 16];
    }
  }
}

void AES::ShiftRows() {
//  ShiftRow(0, 0); keep for logical step
  ShiftRow(1, 1);
  ShiftRow(2, 2);
  ShiftRow(3, 3);
}

void AES::ShiftRow(size_t row, size_t how_many) {
  //state_[row][column]
  
  //get the shifted info
  unsigned char info[kColumnCount];
  for (size_t i = 0; i < kColumnCount; ++i) {
    info[i] = state_[row][(i + how_many) % kColumnCount];
  }
  //move info into state_
  for (size_t i = 0; i < kColumnCount; ++i) {
    state_[row][i] = info[i];
  }
}

void AES::MixColumns() {
  MixColumn(0);
  MixColumn(1);
  MixColumn(2);
  MixColumn(3);
}

void AES::MixColumn(size_t column) {
  //implemented form NIST matrix multiplication spec
  
  unsigned char val0 = state_[0][column];
  unsigned char val1 = state_[1][column];
  unsigned char val2 = state_[2][column];
  unsigned char val3 = state_[3][column];
  
  state_[0][column] = FiniteMultiply(0x02, val0) ^ FiniteMultiply(0x03, val1) ^ val2 ^ val3;
  state_[1][column] = val0 ^ FiniteMultiply(0x02, val1) ^ FiniteMultiply(0x03, val2) ^ val3;
  state_[2][column] = val0 ^ val1 ^ FiniteMultiply(0x02, val2) ^ FiniteMultiply(0x03, val3);
  state_[3][column] = FiniteMultiply(0x03, val0) ^ val1 ^ val2 ^ FiniteMultiply(0x02, val3);
}

void AES::InverseMixColumns() {
  InverseMixColumn(0);
  InverseMixColumn(1);
  InverseMixColumn(2);
  InverseMixColumn(3);
}

void AES::InverseMixColumn(size_t column) {
  unsigned char val0 = state_[0][column];
  unsigned char val1 = state_[1][column];
  unsigned char val2 = state_[2][column];
  unsigned char val3 = state_[3][column];

  state_[0][column] =   FiniteMultiply(0x0e, val0)
                     ^ FiniteMultiply(0x0b, val1)
                     ^ FiniteMultiply(0x0d, val2)
                     ^ FiniteMultiply(0x09, val3);
  state_[1][column] =   FiniteMultiply(0x09, val0)
                     ^ FiniteMultiply(0x0e, val1)
                     ^ FiniteMultiply(0x0b, val2)
                     ^ FiniteMultiply(0x0d, val3);
  state_[2][column] =   FiniteMultiply(0x0d, val0)
                     ^ FiniteMultiply(0x09, val1)
                     ^ FiniteMultiply(0x0e, val2)
                     ^ FiniteMultiply(0x0b, val3);
  state_[3][column] =   FiniteMultiply(0x0b, val0)
                     ^ FiniteMultiply(0x0d, val1)
                     ^ FiniteMultiply(0x09, val2)
                     ^ FiniteMultiply(0x0e, val3);
}

void AES::PrintState() {
  for (size_t i = 0; i < kColumnCount; i++) {
    for (size_t j = 0; j < kColumnCount; ++j) {
      std::cout << state_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

//multiplication of val0 and val1 in the galois field
unsigned char AES::FiniteMultiply(unsigned char val1, unsigned char val2) {
  //implementation inspired by https://en.wikipedia.org/wiki/Finite_field_arithmetic
  
  unsigned char p = 0; //end product
  unsigned char single_limit = 0x80; // limiting bit individual bit value (half ff)
  unsigned char high_byte = 0; //value from second val
  unsigned char mod = 0x1B; // limit of x^8 + x^4 + x^3 + x + 1
  
  for (size_t i = 0; i < 8; ++i) {
    //1 is a byte value here
    if ((val2 & 1) != 0) {
      p = p ^ val1;
    }

    high_byte = val1 & single_limit;
    val1 = val1 << 1;
    if (high_byte != 0) {
      val1 = val1 ^ mod;
    }
    val2 = val2 >> 1;
  }

  return p;
}

//key_ length is 4 * key_block_length_, word length is block_size_ * (num_rounds_+1)
void AES::MakeKeyExpansion(const unsigned char key[], unsigned char expanded_key[]) const {
  
  size_t i = 0;
  while (i < 4 * key_block_length_) {
    expanded_key[i] = key[i];
    i++;
  }
  i = 4 * key_block_length_;
  
  unsigned char tmpWord[4];
  unsigned char rotateWord[4];
  while (i < 4 * block_size_ * (num_rounds_ + 1)) {
    tmpWord[0] = expanded_key[i - 4 + 0];
    tmpWord[1] = expanded_key[i - 4 + 1];
    tmpWord[2] = expanded_key[i - 4 + 2];
    tmpWord[3] = expanded_key[i - 4 + 3];

    if (i / 4 % key_block_length_ == 0) {
      RotWord(tmpWord);
      SubWord(tmpWord);
      RotateConstant(rotateWord, i / (key_block_length_ * 4));
      xOrWords(tmpWord, rotateWord, tmpWord);
    } else if (key_block_length_ > 6 && i / 4 % key_block_length_ == 4){
      SubWord(tmpWord);
    }

    expanded_key[i + 0] = expanded_key[i + 0 - 4 * key_block_length_] ^ tmpWord[0];
    expanded_key[i + 1] = expanded_key[i + 1 - 4 * key_block_length_] ^ tmpWord[1];
    expanded_key[i + 2] = expanded_key[i + 2 - 4 * key_block_length_] ^ tmpWord[2];
    expanded_key[i + 3] = expanded_key[i + 3 - 4 * key_block_length_] ^ tmpWord[3];
    i += 4;
  }
}

void AES::RotateConstant(unsigned char *to_change, int amount) {
  unsigned char temp = 1;
  for (size_t i = 0; i < (size_t) amount - 1; ++i) {
    temp = xtime(temp);
  }
  to_change[0] = temp;
  to_change[1] = 0;
  to_change[2] = 0;
  to_change[3] = 0;
}

unsigned char AES::xtime(unsigned char in) {
  return (in << 1) ^ (((in >> 7) & 1) * 0x1b);
}

void AES::xOrWords(const unsigned char *in1, const unsigned char *in2, unsigned char *out) {
  for (size_t i = 0; i < 4; ++i) {
    out[i] = in1[i] ^ in2[i];
  }
}

void AES::AddRoundKey(const unsigned char* current_key) {
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < block_size_; ++j) {
      state_[i][j] = state_[i][j] ^ current_key[i + 4 * j];
    }
  }
}

void AES::SubWord(unsigned char* word) {
  for (size_t byte_num = 0; byte_num < 4; ++byte_num) {
    word[byte_num] = kS_Box[word[byte_num] / 16][word[byte_num] % 16]; 
  }
}

void AES::RotWord(unsigned char* word) {
  unsigned char byte0 = word[0];
  word[0] = word[1];
  word[1] = word[2];
  word[2] = word[3];
  word[3] = byte0;
}

void AES::InverseShiftRows() {
//ShiftRow(0, block_size_ - 0); keep for logical step
  ShiftRow(1, block_size_ - 1);
  ShiftRow(2, block_size_ - 2);
  ShiftRow(3, block_size_ - 3);
}

void AES::SetKey(unsigned char* new_key) {
  key_ = new_key;
}

unsigned char* AES::GetKeyExpansion() {
  return expanded_key_;
}

void AES::SetState(unsigned char to_set_state[4][4]) {
//  state_ = to_set_state_;
}

unsigned char* AES::GetState() {
  return *state_;
}

}  // namespace aes