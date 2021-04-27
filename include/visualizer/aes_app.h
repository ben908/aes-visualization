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
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;
  
  /** constants for layout */
  const double kWindowSize = 875;
  const double kMargin = 100;
  const size_t kImageDimension = 28;

 private:


};

}  // namespace visualizer

}  // namespace aes
