#include <visualizer/aes_app.h>

namespace aes {

namespace visualizer {

AESApp::AESApp() {
  
  ci::app::setWindowSize((int) kDefaultWindowSize, (int) kDefaultWindowSize);

}

void AESApp::draw() {
  if (maxY_ != ci::app::getWindowHeight()) {
    maxY_ = ci::app::getWindowHeight();
    UpdateSizing();
  }
  if (maxX_ != ci::app::getWindowWidth()) {
    maxX_ = ci::app::getWindowWidth();
    UpdateSizing();
  }
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);


}

void AESApp::UpdateSizing() {
  progressBarHeight_ = maxY_ * kProgressBarHeightPercent;
  mainHeight_ = maxY_ * kMainHeightPercent;
  bottomButtonHeight_ = maxY_ * kBottomButtonHeightPercent;
  menuHeightIndividual_ = maxY_ * kMenuHeightIndividualPercent;
  
  mainWidth_ = maxX_ * kMainWidthPercent;
  secondaryWidth_ = maxX_ * kSecondaryWidthPercent;
  buttonWidth_ = maxX_ * kButtonWidthPercent;
  
}

void AESApp::mouseDown(ci::app::MouseEvent event) {
//  sketchpad_.HandleBrush(event.getPos());
}

void AESApp::mouseDrag(ci::app::MouseEvent event) {
//  sketchpad_.HandleBrush(event.getPos());
}

void AESApp::keyDown(ci::app::KeyEvent event) {
//  cout << event.getCode() << endl;
//  switch (event.getCode()) {
//    case ci::app::KeyEvent::KEY_RETURN:
//      current_prediction_ = Analyzer::GetIndexWithHighestValue(
//          Analyzer::GetDigitProbabilities(
//              sketchpad_.GetShading(),
//              training_model_.GetProcessedProbabilities(),
//              training_model_.GetGeneralClassProbability()));
//      break;
//
//    case ci::app::KeyEvent::KEY_BACKSPACE:
//      sketchpad_.Clear();
//      break;
//  }
}

}  // namespace visualizer

}  // namespace aes
