#include "visualizer/state_displayer.h"

#include <tuple>

namespace aes {

namespace visualizer {

StateDisplayer::StateDisplayer(size_t width, size_t height) {
  display_helper_ = DisplayHelper(width, height);
  
}

void StateDisplayer::DisplayStateChange(
    tuple<AES::Step, unsigned char *> currentState,
    tuple<AES::Step, unsigned char *> nextState) {}

void StateDisplayer::SetDimensions(size_t width, size_t height) {
  display_helper_.SetDimensions(width, height);
  top_left_ = display_helper_.GetStateDisplayAreaTopLeft();
  bottom_right_ = display_helper_.GetStateDisplayAreaBottomRight();
}

void StateDisplayer::DisplaySecondaryInfo() {
  display_helper_.DisplayInfoForState(10.0, "test1", "test2", "test3");
}

void StateDisplayer::DisplaySingleState(tuple<AES::Step, unsigned char*> currentState) {
  
}

} //namespace visualizer

} //namespace aes