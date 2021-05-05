#include <cinder/gl/gl.h>
#include <visualizer/aes_app.h>

namespace aes {

namespace visualizer {

AESApp::~AESApp() {
  delete[] message_;
  delete[] key_;
  delete[] encrypted_message_;
}

AESApp::AESApp() {
  ci::app::setWindowSize((int) kDefaultWindowSize, (int) kDefaultWindowSize);
  state_displayer_ = StateDisplayer(kDefaultWindowSize, kDefaultWindowSize);
  clock_ = 0;
  current_state_ = 0;
  current_key_size_ = 128;
  MakeRandomInfo();
  aes_.Encrypt(message_, encrypted_message_, key_);
  all_states_ = aes_.GetAllState();
  is_animating_ = false;
}

void AESApp::MakeRandomInfo() {
  message_ = new unsigned char[16];
  encrypted_message_ = new unsigned char[16];
  if (current_key_size_ == 128) {
   key_ = new unsigned char[16]; 
  }
  if (current_key_size_ == 192) {
    key_ = new unsigned char[24];
  }
  if (current_key_size_ == 256) {
    key_ = new unsigned char[32];
  }
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
  if(all_states_.size() > current_state_+1) {
    state_displayer_.DisplayStateChange(all_states_[current_state_],
                                        all_states_[current_state_+1]);
    DrawMainShapes();
  }
  
}

void AESApp::DrawMainShapes() {
  double percent = current_state_ / all_states_.size();
  std::stringstream ss;
  for (size_t i = 0; i < 16; ++i) { //for message
    ss << " " << std::hex << (int)message_[i];
  }
  string message = ss.str();
  ss.str("");
  for (size_t i = 0; i < 16; ++i) { //for key TODO::make this dynamic
    ss << " " << std::hex << (int)key_[i];
  }
  string key = ss.str();
  string step = AES::EnumToString(std::get<0>(*all_states_[current_state_ + 1]));
  state_displayer_.DisplaySecondaryInfo(percent, message, key, step);
}



void AESApp::update() {
  if (is_animating_) {
    clock_++;
  }
  if (clock_ % 20 == 1) {
    current_state_++;
  }
  if (current_state_ >= aes_.GetAllState().size()) {
    is_animating_ = false;
  }
}

void AESApp::UpdateSizing() {
  state_displayer_.SetDimensions(max_X_, max_Y_);
}

void AESApp::mouseDown(ci::app::MouseEvent event) {
  current_state_ = (event.getX() * all_states_.size()) / max_X_;
  is_animating_ = false;
}

void AESApp::mouseDrag(ci::app::MouseEvent event) {
  current_state_ = (event.getX() * all_states_.size()) / max_X_;
  is_animating_ = false;
}

void AESApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_e:
      aes_.Encrypt(message_, encrypted_message_, key_);
      all_states_ = aes_.GetAllState();
      is_animating_ = true;
      break;

    case ci::app::KeyEvent::KEY_d:
      aes_.Decrypt(encrypted_message_, message_, key_);
      all_states_ = aes_.GetAllState();
      is_animating_ = false;
      break;

    case ci::app::KeyEvent::KEY_p:
    case ci::app::KeyEvent::KEY_s:
      is_animating_ = false;
      break;
      
    case ci::app::KeyEvent::KEY_r:
      is_animating_ = true;
      break;
      
    case ci::app::KeyEvent::KEY_1:
      current_key_size_ = 128;
      MakeRandomInfo();
      break;
      
    case ci::app::KeyEvent::KEY_2:
      current_key_size_ = 192;
      MakeRandomInfo();
      break;
      
    case ci::app::KeyEvent::KEY_3:
      current_key_size_ = 256;
      MakeRandomInfo();
      break;
  }
}

}  // namespace visualizer

}  // namespace aes
