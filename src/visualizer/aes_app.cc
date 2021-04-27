#include <visualizer/aes_app.h>

namespace aes {

namespace visualizer {

AESApp::AESApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);

}

void AESApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);


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
