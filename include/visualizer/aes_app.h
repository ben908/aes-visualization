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
  
  /** Speed the display changes, default is once every 20 update calls */
  static const size_t kAnimationSpeed =         20;
  
  /** Defaults for algorithm*/
  static const size_t kDefaultKeySize =         128;
  static const size_t kMediumKeySize =          192;
  static const size_t kLargeKeySize =           256;
  static const size_t kMessageSize =            16;
  static const size_t kSmallKeyByteCount =      16;
  static const size_t kMediumKeyByteCount =     24;
  static const size_t kLargeKeyByteCount =      32;

  /** constants for layout */
  static const size_t kDefaultWindowSize =      875;
  static constexpr double kSizeReduceRatio =    0.5;
  static constexpr double kSizeIncreaseRatio =  2.0;
  
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
  
  /** called every cycle, changes the clock which determines animation state */
  void update() override;
  
  /** Used to give commands to the program */
  void keyDown(ci::app::KeyEvent event) override;
  
 private:
  /** Helper that remakes all values for when a key-length changes */
  void Reset();
  
  /** Makes a random key and message for a given key size */
  void MakeRandomInfo();
  
  /**Checks if the current state has a valid value, and adjusts it if needed */
  void StateCheck();
  
  /** Information about the current app state */
  size_t          current_key_size_;
  unsigned char*  message_;
  unsigned char*  key_;
  unsigned char*  encrypted_message_;
  int             current_state_; //not size_t since if state goes below 0, no underflow
  bool            is_animating_;
  bool            is_encrypting_;
  size_t          key_size_;
  
  /** History of all states that are used to encrypt a single block */
  std::vector<std::tuple<AES::Step, unsigned char*>*> all_states_;

  /** Internal clock used if "e" is pressed and the progress is automatic */
  size_t clock_;
  
  /** Helper that displays most of the app UI */
  StateDisplayer state_displayer_;
  
  /** Main algorithm, defaults to a 128-bit key */
  AES* aes_;
  
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
