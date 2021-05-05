#pragma once

#include <cinder/Color.h>

#include <glm/vec2.hpp>
#include <string>

namespace aes {

namespace visualizer {
using glm::vec2;
using std::string;

/**
 * Class that displays most of the app UI
 */
class DisplayHelper {
 public:
  /** Layout constants */
  static const ci::Color kBackgroundColor;
  static const ci::Color kBorderColor;
  static const ci::Color8u kProgressBarColor;
  static const std::string kFontName;

  static constexpr double kProgressBarHeightPercent = 0.09;
  static constexpr double kMainHeightPercent = 0.76;
  static constexpr double kBottomButtonHeightPercent = 0.15;
  static constexpr double kMenuHeightIndividualPercent = 0.19;

  static constexpr double kMainWidthPercent = 0.7;
  static constexpr double kSecondaryWidthPercent = 0.85;
  static constexpr double kButtonWidthPercent = 0.5;
  
  /**
   * Default constructor
   */
  DisplayHelper() = default;
  
  /**
   * Main constructor used to create an instance of the class
   * @param width the total width that the app ui can use
   * @param height the total height the app ui can use
   */
  DisplayHelper(size_t width, size_t height);
  
  /**
   * Called when the window size of the app changes
   * @param width, new app width
   * @param height, new app height
   */
  void SetDimensions(size_t width, size_t height);
  
  /**
   * Method that displays sub boxes with information about the state
   * of the program
   * @param percent, percent of operations of encryption complete 
   * @param message, message being encrypted 
   * @param key, key being used for the encryption
   * @param current_step, what just happened to bring the block state
   *                      to the the current state
   */
  void DisplayInfoForState(double percent,
                           string message,
                           string key,
                           string current_step);
  
  /**
   * Returns space available for the state grid, used with the method below 
   * @return vec2 of top left corner
   */
  vec2 GetStateDisplayAreaTopLeft();
  
  /**
   * Returns space available for the state grid, used with the method above
   * @return vec2 of the bottom right corner
   */
  vec2 GetStateDisplayAreaBottomRight();

  /**
   * Helper method that will return the center point of a grid box
   * @param top_left, top left corner of grid
   * @param bottom_right, bottom right corner of grid
   * @return center point of the grid
   */
  static vec2 TextLocation(vec2 top_left, vec2 bottom_right);

  /**
   * Displays text at the center of a given location box
   * @param top_left_corner, top left corner of the box
   * @param bottom_right_corner, bottom right corner of the box
   * @param text, text to be displayed
   */
  static void DisplayText(vec2 top_left_corner,
                   vec2 bottom_right_corner,
                   string text);
  
 private:
  
  /** Helpers that draw indivudal components of the UI */
  void DrawLoadBar(double percent);
  void DrawMessage(string message);
  void DrawKey(string key);
  void DrawStepBox(string current_step);
  void DrawMainButtons();
  void DrawInstructions();
  
  /** Layout Values for the entire UI */
  size_t max_X_;
  size_t max_Y_;
  
  size_t progress_bar_height_;
  size_t main_height_;
  size_t menu_height_individual_;

  size_t main_width_;

  vec2 loading_bar_top_left_;
  vec2 loading_bar_bottom_right_;

  vec2 message_box_top_left_;
  vec2 message_box_bottom_right_;

  vec2 key_box_top_left_;
  vec2 key_box_bottom_right_;

  vec2 step_box_top_left_;
  vec2 step_box_bottom_right_;

  vec2 main_buttons_top_left_;
  vec2 main_buttons_bottom_right_;

  vec2 instructions_top_left_;
  vec2 instructions_bottom_right_;
  
};

} //namespace visualizer

} //namespace aes