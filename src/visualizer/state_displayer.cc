#include "visualizer/state_displayer.h"


namespace aes {

namespace visualizer {

StateDisplayer::StateDisplayer(vec2 top_left, vec2 bottom_right) {
  top_left_ = top_left;
  bottom_right_ = bottom_right;
}

void StateDisplayer::DisplayStateChange(
    tuple<AES::step, unsigned char *> currentState,
    tuple<AES::step, unsigned char *> nextState) {}

void StateDisplayer::SetDimensions(vec2 top_left, vec2 bottom_right) {
  top_left_ = top_left_;
  bottom_right_ = bottom_right;
}

void StateDisplayer::DisplaySubBytes() {}

void StateDisplayer::DisplayRowShift() {}

void StateDisplayer::DisplayColumnMix() {}

void StateDisplayer::DisplayKeyAdd() {
  
}
}

}