#pragma once
#include <core/aes.h>

#include <glm/vec2.hpp>

#include "display_helper.h"
namespace aes {

namespace visualizer {
using glm::vec2;
using std::tuple;

/**
 * Class that Displays/Animates the changes between two states.
 */
class StateDisplayer {
 public:
  StateDisplayer() = default;
  
  /**
   * Makes an instance of th class
   * @param top_left top left of the area it can draw in
   * @param bottom_right bottom_right of the area it can draw in
   */
  StateDisplayer(size_t width, size_t height);
  
  /**
   * Main method called that shows the change between two states
   * @param currentState current state, tuple of the step it took to get there and the values
   * @param nextState next state, tuple of step to do and state that should be the result
   */
  void DisplayStateChange(tuple<AES::Step, unsigned char*> currentState,
                          tuple<AES::Step, unsigned char*> nextState);
  
  
  void DisplaySingleState(tuple<AES::Step, unsigned char*> currentState);
  
  /**
   * Method that changes the dimensions if the view size changes 
   * @param top_left 
   * @param bottom_right 
   */
  void SetDimensions(size_t width, size_t height);
  
  void DisplaySecondaryInfo();
  
 private:
  DisplayHelper display_helper_;
  
  /**Values for the places the data should be displayed in*/
  vec2 top_left_;
  vec2 bottom_right_;
  
  vec2 left_state_top_left_;
  vec2 left_state_bottom_right_;
  unsigned char **left_state_values;
  
  vec2 right_state_top_left_;
  vec2 right_state_bottom_right_;
  
  /** layout values */
  double kPaddingPercent = 0.1;
  
  size_t rectangle_height_;
  size_t rectangle_width_;
};



} //namespace visualizer

} //namespace aes
