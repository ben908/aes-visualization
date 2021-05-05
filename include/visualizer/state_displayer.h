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
  void DisplayStateChange(tuple<AES::Step, unsigned char*>* currentState);
  
  /**
   * Displays the grid of a single state at
   * @param top_left, top left corner of drawable area
   * @param bottom_right, bottom right corner of drawable area
   * @param currentState, state to draw
   */
  void DisplaySingleState(vec2 top_left, vec2 bottom_right,
                          unsigned char* currentState);
  
  /**
   * Method that changes the dimensions if the view size changes 
   * @param top_left 
   * @param bottom_right 
   */
  void SetDimensions(size_t width, size_t height);
  
  /**
   * Calls the helper class with all the necessary info for the UI
   * @param percent, progress bar percent
   * @param message, message being encrypted 
   * @param key, key being used to encrypt/decrypt message
   * @param current_step, most recent action of the algorithm that
   *                      brought it to the current state
   */
  void DisplaySecondaryInfo(double percent,
                            string message,
                            string key,
                            string current_step);
  
 private:
  /** Helper that displays all the non-state-grid information */
  DisplayHelper display_helper_;
  
  /**Values for the places the data should be displayed in*/
  vec2 top_left_;
  vec2 bottom_right_;
};



} //namespace visualizer

} //namespace aes
