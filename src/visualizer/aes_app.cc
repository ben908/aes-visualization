#include <cinder/gl/gl.h>
#include <visualizer/aes_app.h>

namespace aes {

namespace visualizer {


AESApp::AESApp() {
  ci::app::setWindowSize((int) kDefaultWindowSize, (int) kDefaultWindowSize);
  state_displayer_ = StateDisplayer(kDefaultWindowSize, kDefaultWindowSize);
  clock_ = 0;
  current_state_ = 0;
  is_animating_ = false;
}

void AESApp::draw() {
  if (max_Y_ != ci::app::getWindowHeight()) {
    max_Y_ = ci::app::getWindowHeight();
    UpdateSizing();
  }
  if (max_X_ != ci::app::getWindowWidth()) {
    max_X_ = ci::app::getWindowWidth();
    UpdateSizing();
  }
  ci::gl::clear(DisplayHelper::kBackgroundColor);
  
  DrawMainShapes();

}

void AESApp::DrawMainShapes() {

  ci::gl::color(DisplayHelper::kBackgroundColor);
//  ci::gl::drawStrokedRect(ci::Rectf(topLeftCorner, bottomRightCorner));
  state_displayer_.DisplaySecondaryInfo();
  
}



void AESApp::update() {
  clock_++;
  if (clock_ % 10 == 0) {
    current_state_++;
  }
  if (current_state_ > aes_.GetAllState().size()) {
    is_animating_ = false;
  }
}

void AESApp::UpdateSizing() {
  state_displayer_.SetDimensions(max_X_, max_Y_);
}

void AESApp::mouseDown(ci::app::MouseEvent event) {
//  sketchpad_.HandleBrush(event.getPos());
}

void AESApp::mouseDrag(ci::app::MouseEvent event) {
//  sketchpad_.HandleBrush(event.getPos());
}

}  // namespace visualizer

}  // namespace aes
