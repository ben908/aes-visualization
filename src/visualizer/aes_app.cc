#include <visualizer/aes_app.h>

namespace aes {

namespace visualizer {

const ci::Color AESApp::kBackgroundColor = "white";
const ci::Color AESApp::kBorderColor = "black";
const ci::Color8u AESApp::kProgressBarColor = ci::Color8u(0, 204, 0);
const std::string AESApp::kFontName = "Arial";

AESApp::AESApp() {
  ci::app::setWindowSize((int) kDefaultWindowSize, (int) kDefaultWindowSize);
//  state_displayer_ = StateDisplayer();
//  state_displayer_.SetDimensions(
//      vec2(0,0),
//      vec2(kDefaultWindowSize, kDefaultWindowSize));
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

void AESApp::DrawMainShapes() {

  ci::gl::color(AESApp::kBackgroundColor);
//  ci::gl::drawStrokedRect(ci::Rectf(topLeftCorner, bottomRightCorner));
  DrawLoadBar();
  DrawMessage();
  DrawKey();
  DrawCurrentStep();
}

void AESApp::DrawLoadBar() {
  ci::gl::color(kBorderColor);
  ci::gl::drawStrokedRect(
      ci::Rectf(loading_bar_top_left_, loading_bar_bottom_right_));
  //TODO::add green % part
  
}

void AESApp::DrawMessage() {
  ci::gl::color(kBorderColor);
  ci::gl::drawStrokedRect(
      ci::Rectf(message_box_top_left_, message_box_bottom_right_));
  //TODO:: display message text

}

void AESApp::DrawKey() {
  ci::gl::color(kBorderColor);
  ci::gl::drawStrokedRect(
      ci::Rectf(key_box_top_left_, key_box_bottom_right_));
  //TODO:: display key text

}

void AESApp::DrawCurrentStep() {
  ci::gl::color(kBorderColor);
  ci::gl::drawStrokedRect(
      ci::Rectf(state_displayer_top_left_, state_displayer_bottom_right_));
  
  if (is_animating_) {
//    state_displayer_.DisplayStateChange(); //TODO:: vector location
  } else {
//    state_displayer_.DisplaySingleState(); //TODO:: current state
  }
  
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
  progress_bar_height_ = max_Y_ * kProgressBarHeightPercent;
  main_height_ = max_Y_ * kMainHeightPercent;
  bottom_button_height_ = max_Y_ * kBottomButtonHeightPercent;
  menu_height_individual_ = max_Y_ * kMenuHeightIndividualPercent;
  
  main_height_ = max_X_ * kMainWidthPercent;
  secondary_width_ = max_X_ * kSecondaryWidthPercent;
  button_width_ = max_X_ * kButtonWidthPercent;
  
  loading_bar_top_left_ = vec2(0, 0);
  loading_bar_bottom_right_ = vec2(max_X_, progress_bar_height_);
  
  state_displayer_top_left_ = vec2(0, progress_bar_height_);
  state_displayer_bottom_right_ = vec2(main_height_, progress_bar_height_ + main_height_);
  
  message_box_top_left_ = vec2(main_width_, progress_bar_height_);
  message_box_bottom_right_ = vec2(max_X_, progress_bar_height_ + 1 * menu_height_individual_);
  
  key_box_top_left_ = vec2(main_width_, progress_bar_height_ + 1 * menu_height_individual_);
  key_box_bottom_right_ = vec2(max_X_, progress_bar_height_ + 2 * menu_height_individual_);
  
  step_box_top_left_ = vec2(main_width_, progress_bar_height_ + 2 * menu_height_individual_);
  step_box_bottom_right_ = vec2(max_X_, progress_bar_height_ + 3 * menu_height_individual_);
  
  main_buttons_top_left_ = vec2(main_width_, progress_bar_height_ + 3 * menu_height_individual_);
  main_buttons_bottom_right_ = vec2(max_X_, progress_bar_height_ + 4 * menu_height_individual_);
  
  instructions_top_left_ = vec2(0, progress_bar_height_ + main_height_);
  instructions_bottom_right_ = vec2(secondary_width_, max_Y_);
  
  key_box_top_left_ = vec2(secondary_width_, progress_bar_height_ + 4 * menu_height_individual_);
  key_box_bottom_right_ = vec2(max_X_, max_Y_);

//  state_displayer_.SetDimensions(
//      state_displayer_top_left_, state_displayer_bottom_right_);
  
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
