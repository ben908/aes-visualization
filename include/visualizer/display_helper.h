#pragma once

#include <cinder/Color.h>

#include <glm/vec2.hpp>
#include <string>

namespace aes {

namespace visualizer {
using glm::vec2;
using std::string;

class DisplayHelper {
 public:
  static const ci::Color kBackgroundColor;
  static const ci::Color kBorderColor;
  static const ci::Color8u kProgressBarColor;
  static const std::string kFontName;
  
  DisplayHelper() = default;
  
  DisplayHelper(size_t width, size_t height);
  
  void SetDimensions(size_t width, size_t height);
  
  void DisplayInfoForState(double percent,
                           string message,
                           string key,
                           string current_step);
  
  vec2 GetStateDisplayAreaTopLeft();
  vec2 GetStateDisplayAreaBottomRight();
  
 private:
  
  vec2 TextLocation(vec2 top_left, vec2 bottom_right);
  
  void DisplayText(vec2 top_left_corner,
                   vec2 bottom_right_corner,
                   string text);
  void DrawLoadBar(double percent);
  void DrawMessage(string message);
  void DrawKey(string key);
  void DrawStepBox(string current_step);
  void DrawMainButtons();
  void DrawInstructions();
  void DrawKeyButtons();
  
  
  
  size_t max_X_;
  size_t max_Y_;
  
  size_t progress_bar_height_;
  size_t main_height_;
  size_t bottom_button_height_;
  size_t menu_height_individual_;

  size_t main_width_;
  size_t secondary_width_;
  size_t button_width_;

  vec2 loading_bar_top_left_;
  vec2 loading_bar_bottom_right_;

  vec2 state_displayer_top_left_;
  vec2 state_displayer_bottom_right_;

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

  vec2 key_length_buttons_top_left_;
  vec2 key_length_buttons_bottom_right_;

  double kProgressBarHeightPercent = 0.09;
  double kMainHeightPercent = 0.76;
  double kBottomButtonHeightPercent = 0.15;
  double kMenuHeightIndividualPercent = 0.19;

  double kMainWidthPercent = 0.7;
  double kSecondaryWidthPercent = 0.85;
  double kButtonWidthPercent = 0.5;
};

} //namespace visualizer

} //namespace aes