#include <core/aes.h>

#include <iostream>

namespace aes {

//void AES::Encrypt(std::string message) {
//  if(message.length() != 32) {
//    std::cout<<"bad message length" << std::endl;
//    throw std::invalid_argument("bad length");
//  }
  
//  for (size_t i = 0, j = 0; j < kColumnCount;) {
//    state[i][j] = message[i+j];
//    std::cout << i << "," << j << "= " << state[i][j] << std::endl;
//    ++i;
//    if (i == kColumnCount) {
//      ++j;
//      i = 0;
//    }
//  }
//  
//  PrintState();
//}

AES::AES() = default;

void AES::SubBytes() {
  for (size_t i = 0; i < kColumnCount; ++i) {
    for (size_t j = 0; j < kColumnCount; ++j) {
      unsigned char t = state[i][j];
      state[i][j] = kForwardS_Box[t / 16][t % 16];
    }
  }
}

void AES::InvSubBytes() {
  for (size_t i = 0; i < kColumnCount; ++i) {
    for (size_t j = 0; j < kColumnCount; ++j) {
      unsigned char t = state[i][j];
      state[i][j] = kBackwardsS_Box[t / 16][t % 16];
    }
  }
}

void AES::ShiftRows() {
  
//  ShiftRow(0, 0); keep for logical step
  ShiftRow(1, 1);
  ShiftRow(2, 3);
  ShiftRow(3, 3);
}

void AES::ShiftRow(size_t row, size_t how_many) {
  //state[row][column]
  
  //get the shifted info
  unsigned char info[kColumnCount];
  for (size_t i = 0; i < kColumnCount; ++i) {
    info[i] = state[row][(i + how_many) % kColumnCount];
  }
  //move info into state
  for (size_t i = 0; i < kColumnCount; ++i) {
    state[row][i] = info[i];
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
  
  unsigned char val0 = state[0][column];
  unsigned char val1 = state[1][column];
  unsigned char val2 = state[2][column];
  unsigned char val3 = state[3][column];
  
  state[0][column] = FiniteMultiply(0x02, val0) ^ FiniteMultiply(0x03, val1) ^ val2 ^ val3;
  state[1][column] = val0 ^ FiniteMultiply(0x02, val1) ^ FiniteMultiply(0x03, val2) ^ val3;
  state[2][column] = val0 ^ val1 ^ FiniteMultiply(0x02, val2) ^ FiniteMultiply(0x03, val3);
  state[3][column] = FiniteMultiply(0x03, val0) ^ val1 ^ val2 ^ FiniteMultiply(0x02, val3);
}

void AES::InverseMixColumns() {
  InverseMixColumn(0);
  InverseMixColumn(1);
  InverseMixColumn(2);
  InverseMixColumn(3);
}

void AES::InverseMixColumn(size_t column) {
  unsigned char val0 = state[0][column];
  unsigned char val1 = state[1][column];
  unsigned char val2 = state[2][column];
  unsigned char val3 = state[3][column];

  state[0][column] =   FiniteMultiply(0x0e, val0)
                     ^ FiniteMultiply(0x0b, val1)
                     ^ FiniteMultiply(0x0d, val2)
                     ^ FiniteMultiply(0x09, val3);
  state[1][column] =   FiniteMultiply(0x09, val0)
                     ^ FiniteMultiply(0x0e, val1)
                     ^ FiniteMultiply(0x0b, val2)
                     ^ FiniteMultiply(0x0d, val3);
  state[2][column] =   FiniteMultiply(0x0d, val0)
                     ^ FiniteMultiply(0x09, val1)
                     ^ FiniteMultiply(0x0e, val2)
                     ^ FiniteMultiply(0x0b, val3);
  state[3][column] =   FiniteMultiply(0x0b, val0)
                     ^ FiniteMultiply(0x0d, val1)
                     ^ FiniteMultiply(0x09, val2)
                     ^ FiniteMultiply(0x0e, val3);
}

void AES::PrintState() {
  for (size_t i = 0; i < kColumnCount; i++) {
    for (size_t j = 0; j < kColumnCount; ++j) {
      std::cout << state[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

unsigned char AES::FiniteMultiply(unsigned char val0, unsigned char val1) {
  //TODO:: implement Galois finite field multiplication
  return 0x00;
}

    unsigned char *AES::Encrypt(unsigned char *message, unsigned char *key) {
        return nullptr;
    }

    unsigned char *AES::Decrypt(unsigned char *message, unsigned char *key) {
        return nullptr;
    }

    void AES::SetKey(unsigned char *key) {

    }

    unsigned char *AES::GetKeyExpansion(size_t word_number) {
        return nullptr;
    }

    void AES::SetState(unsigned char (*state)[4]) {

    }

    unsigned char *AES::GetState() {
        return nullptr;
    }

    void AES::MakeKeyExpansion() {

    }

    void AES::AddRoundKey() {

    }

    void AES::SubWord() {

    }

    void AES::RotWords() {

    }

    void AES::InverseShiftRows() {

    }

    void AES::InverseShiftRow(size_t row, size_t how_many) {

    }


}  // namespace aes