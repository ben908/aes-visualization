#include <cinder/gl/gl.h>
#include <visualizer/aes_app.h>

namespace aes {

namespace visualizer {

const ci::Color AESApp::kBackgroundColor = "white";
const ci::Color AESApp::kBorderColor = "black";
const ci::Color8u AESApp::kProgressBarColor = ci::Color8u(0, 204, 0);
const std::string AESApp::kFontName = "Arial";

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
  ci::gl::clear(kBackgroundColor);
  
  DrawMainShapes();

}

//const void AESApp::DisplayHorizontalLabel(const vec2& topLeftCorner,
//                                                  const vec2& bottomRightCorner,
//                                                  const string& text) {
//  const float fontSize = bottomRightCorner.y - topLeftCorner.y;
//  const ci::Font font = ci::Font(IdealGasApp::kFontName, fontSize);
//  ci::gl::drawStringCentered(text,
//                             TextLocation(topLeftCorner, bottomRightCorner),
//                             IdealGasApp::kTextColor,
//                             font);
//}

void AESApp::DrawMainShapes() {

  ci::gl::color(AESApp::kBackgroundColor);
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
