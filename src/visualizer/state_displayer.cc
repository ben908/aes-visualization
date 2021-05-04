#include "visualizer/state_displayer.h"


namespace aes {

namespace visualizer {

StateDisplayer::StateDisplayer(vec2 top_left, vec2 bottom_right) {
  top_left_ = top_left;
  bottom_right_ = bottom_right;
}

void StateDisplayer::DisplayStateChange(
    tuple<AES::Step, unsigned char *> currentState,
    tuple<AES::Step, unsigned char *> nextState) {}

void StateDisplayer::SetDimensions(vec2 top_left, vec2 bottom_right) {
  top_left_ = top_left_;
  bottom_right_ = bottom_right;
}

  

} //namespace visualizer

} //namespace aes