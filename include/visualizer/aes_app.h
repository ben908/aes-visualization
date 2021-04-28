#pragma once

#include <core/aes.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace aes {

namespace visualizer {


class AESApp : public ci::app::App {
 public:
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
  AES aes_;
  
  /** Called when the window size changes */
  void UpdateSizing();
  
  /** Draws the main app structures */
  void DrawMainShapes();
  
  /** layout values */
  size_t maxX_;
  size_t maxY_;
  
  size_t progressBarHeight_;
  size_t mainHeight_;
  size_t bottomButtonHeight_;
  size_t menuHeightIndividual_;

  size_t mainWidth_;
  size_t secondaryWidth_;
  size_t buttonWidth_;
  
  double kProgressBarHeightPercent = 0.09;
  double kMainHeightPercent = 0.76;
  double kBottomButtonHeightPercent = 0.15;
  double kMenuHeightIndividualPercent = 0.19;
  
  double kMainWidthPercent = 0.7;
  double kSecondaryWidthPercent = 0.3;
  double kButtonWidthPercent = 0.5;
};

}  // namespace visualizer

}  // namespace aes
