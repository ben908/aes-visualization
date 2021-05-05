#pragma once

#include <cinder/app/App.h>
#include <core/aes.h>

#include <glm/vec2.hpp>

#include "state_displayer.h"
namespace aes {

namespace visualizer {
using glm::vec2;

/**
 * App that visualizes the AES algorithm
 */
class AESApp : public ci::app::App {
 public:
  /** Destructor that deletes the key, message, and encrypted message */
  ~AESApp();
  
  /** Main Constructor */
  AESApp();

  /** methods from cinder to deal with UI */
  void draw() override;
  
  /**will be used to all the user to change the progress bar/key length*/
  void mouseDown(ci::app::MouseEvent event) override;
  
  /** used to drag along progress bar */
  void mouseDrag(ci::app::MouseEvent event) override;
  void update() override;
  
  /** Used to give commands to the program */
  void keyDown(ci::app::KeyEvent event) override;
  
  /** constants for layout */
  const size_t kDefaultWindowSize = 875;
  
 private:
  /** Makes a random key and message for a given key size */
  void MakeRandomInfo();
  
  /** Information about the current app state */
  size_t current_key_size_;
  unsigned char* message_;
  unsigned char* key_;
  unsigned char* encrypted_message_;
  size_t current_state_;
  bool is_animating_;
  size_t key_size_;
  
  /** History of all states that are used to encypt a single block */
  std::vector<std::tuple<AES::Step, unsigned char*>*> all_states_;

  /** Internal clock used if "e" is pressed and the progress is automatic */
  size_t clock_;
  
  /** Helper that displays most of the app UI */
  StateDisplayer state_displayer_;
  
  /** Main algorithm, defaults to a 128-bit key */
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
