#pragma once

#include <tuple>
#include "aes_app.h"
#include <core/aes.h>


using glm::vec2;
using std::tuple;
namespace aes {

namespace visualizer {

class StateDisplayer {
 public:
  StateDisplayer(vec2 top_left, vec2 bottom_right);
  
  void DisplayStateChange(tuple<AES::step, unsigned char*> currentState,
                          tuple<AES::step, unsigned char*> nextState);

  void SetDimensions(vec2 top_left, vec2 bottom_right);
  
 private:
  void DisplaySubBytes();
  void DisplayRowShift();
  void DisplayColumnMix();
  void DisplayKeyAdd();
  
  
  vec2 top_left_;
  vec2 bottom_right_;
  
  vec2 left_state_top_left_;
  vec2 left_state_bottom_right_;
  unsigned char **left_state_values;
  
  vec2 right_state_top_left_;
  vec2 right_state_bottom_right_;
  
  double kPaddingPercent = 0.1;
  
  size_t rectangle_height_;
  size_t rectangle_width_;
};



}

}
