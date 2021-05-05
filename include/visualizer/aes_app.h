#pragma once

#include <cinder/app/App.h>
#include <core/aes.h>

#include <glm/vec2.hpp>

#include "state_displayer.h"
namespace aes {

namespace visualizer {
using glm::vec2;

class AESApp : public ci::app::App {
 public:
  static const ci::Color kBackgroundColor;
  static const ci::Color kBorderColor;
  static const ci::Color8u kProgressBarColor;
  static const std::string kFontName;
  
  /** Main Constructor */
  AESApp();

  /** methods from cinder to deal with UI */
  void draw() override;
  
  /**will be used to all the user to change the progress bar/key length*/
  void mouseDown(ci::app::MouseEvent event) override;
  
  /** used to drag along progress bar */
  void mouseDrag(ci::app::MouseEvent event) override;
  void update() override;
  
  /** constants for layout */
  const size_t kDefaultWindowSize = 875;
  
 private:
  
  size_t clock_;
  size_t current_state_;
  bool is_animating_;
  
  StateDisplayer state_displayer_;
  
  /** Main algorithm */
  AES aes_ = AES(128);
  
  /** Called when the window size changes */
  void UpdateSizing();
  
  /** Draws the main app structures */
  void DrawMainShapes();
  
  /** layout values */
  size_t max_X_;
  size_t max_Y_;
  

};

}  // namespace visualizer

}  // namespace aes
