#pragma once

#include <core/aes.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace aes {

namespace visualizer {
using glm::vec2;

class AESApp : public ci::app::App {
 public:
  static const ci::Color kBackgroundColor;
  static const ci::Color kBorderColor;
  static const ci::Color8u kProgressBarColor;
  
  /** Main Constructor */
  AESApp();

  /** methods from cinder to deal with UI */
  void draw() override;
  
  /**will be used to all the user to change the progress bar/key length*/
  void mouseDown(ci::app::MouseEvent event) override;
  
  /** used to drag along progress bar */
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;
  
  /** constants for layout */
  const size_t kDefaultWindowSize = 875;
  
 private:
  /** Main algorithm */
  AES aes_ = AES(128);
  
  /** Called when the window size changes */
  void UpdateSizing();
  
  /** Draws the main app structures */
  void DrawMainShapes();
  
  void DrawLoadBar();
  void DrawMessage();
  void DrawKey();
  void DrawCurrentStep();
  
  
  /** layout values */
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

}  // namespace visualizer

}  // namespace aes
