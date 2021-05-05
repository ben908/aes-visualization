#include "visualizer/display_helper.h"

#include <cinder/gl/gl.h>

#pragma once

namespace aes {

namespace visualizer {

const ci::Color DisplayHelper::kBackgroundColor = "white";
const ci::Color DisplayHelper::kBorderColor = "black";
const ci::Color8u DisplayHelper::kProgressBarColor = ci::Color8u(0, 204, 0);
const std::string DisplayHelper::kFontName = "Arial";

void DisplayHelper::DisplayInfoForState(double percent, string message,
                                        string key, string current_step) {
  DrawLoadBar(percent);
  DrawMessage(message);
  DrawKey(key);
  DrawStepBox(current_step);
  DrawMainButtons();
  DrawInstructions();
  DrawKeyButtons();
}

DisplayHelper::DisplayHelper(size_t width, size_t height) {
  SetDimensions(width, height);
}

vec2 DisplayHelper::GetStateDisplayAreaTopLeft() {
  return glm::vec2(0, progress_bar_height_);
}
vec2 DisplayHelper::GetStateDisplayAreaBottomRight() {
  return glm::vec2(main_width_, progress_bar_height_ + main_height_);
}


void DisplayHelper::SetDimensions(size_t width, size_t height) {
  max_X_ = width;
  max_Y_ = height;
  
  progress_bar_height_ = max_Y_ * kProgressBarHeightPercent;
  main_height_ = max_Y_ * kMainHeightPercent;
  bottom_button_height_ = max_Y_ * kBottomButtonHeightPercent;
  menu_height_individual_ = max_Y_ * kMenuHeightIndividualPercent;

  main_width_ = max_X_ * kMainWidthPercent;
  secondary_width_ = max_X_ * kSecondaryWidthPercent;
  button_width_ = max_X_ * kButtonWidthPercent;

  loading_bar_top_left_ = vec2(0, 0);
  loading_bar_bottom_right_ = vec2(max_X_, progress_bar_height_);

  state_displayer_top_left_ = vec2(0, progress_bar_height_);
  state_displayer_bottom_right_ = vec2(main_width_, progress_bar_height_ + main_height_);

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

  key_length_buttons_top_left_ = vec2(secondary_width_, progress_bar_height_ + 4 * menu_height_individual_);
  key_length_buttons_bottom_right_ = vec2(max_X_, max_Y_);
  
}

void DisplayHelper::DrawLoadBar(double percent) {
  ci::gl::color(ci::Color("green"));
  ci::gl::drawStrokedRect(
      ci::Rectf(loading_bar_top_left_, loading_bar_bottom_right_));
  //TODO::add green % part

}

void DisplayHelper::DrawMessage(string message) {
  ci::gl::color(ci::Color("red"));
  ci::gl::drawStrokedRect(
      ci::Rectf(message_box_top_left_, message_box_bottom_right_));
  float mid_y = (message_box_bottom_right_.y + message_box_top_left_.y) / 2;
  
  vec2 top_block_top_left = message_box_top_left_;
  vec2 top_block_bottom_right = vec2(message_box_bottom_right_.x, mid_y);
  vec2 low_block_top_left = vec2(message_box_top_left_.x, mid_y);
  vec2 low_block_bottom_right = message_box_bottom_right_;
  
  DisplayText(top_block_top_left, top_block_bottom_right, "Original Message:");
  DisplayText(low_block_top_left, low_block_bottom_right, message);
}

void DisplayHelper::DrawKey(string key) {
  ci::gl::color(ci::Color("yellow"));
  ci::gl::drawStrokedRect(
      ci::Rectf(key_box_top_left_, key_box_bottom_right_));
  float mid_y = (key_box_top_left_.y + key_box_bottom_right_.y) / 2;
  
  vec2 top_block_top_left = key_box_top_left_;
  vec2 top_block_bottom_right = vec2(key_box_bottom_right_.x, mid_y);
  vec2 low_block_top_left = vec2(key_box_top_left_.x, mid_y);
  vec2 low_block_bottom_right = key_box_bottom_right_;

  DisplayText(top_block_top_left, top_block_bottom_right, "Current Key:");
  DisplayText(low_block_top_left, low_block_bottom_right, key);
}

void DisplayHelper::DrawStepBox(string step) {
  ci::gl::color(ci::Color("purple"));
  ci::gl::drawStrokedRect(
      ci::Rectf(step_box_top_left_, step_box_bottom_right_));
  DisplayText(step_box_top_left_, step_box_bottom_right_, step);
}

void DisplayHelper::DrawMainButtons() {
  ci::gl::color(ci::Color("blue"));
  ci::gl::drawStrokedRect(
      ci::Rectf(main_buttons_top_left_, main_buttons_bottom_right_));
  float mid_y = (main_buttons_top_left_.y + main_buttons_bottom_right_.y) / 2;

  vec2 top_block_top_left = main_buttons_top_left_;
  vec2 top_block_bottom_right = vec2(main_buttons_bottom_right_.x, mid_y);
  vec2 low_block_top_left = vec2(main_buttons_top_left_.x, mid_y);
  vec2 low_block_bottom_right = main_buttons_bottom_right_;

  DisplayText(top_block_top_left, top_block_bottom_right, "Encrypt");
  DisplayText(low_block_top_left, low_block_bottom_right, "Decrypt");
  

}

void DisplayHelper::DrawInstructions() {
  ci::gl::color(ci::Color("grey"));
  ci::gl::drawStrokedRect(
      ci::Rectf(instructions_top_left_, instructions_bottom_right_));
  float mid_y = (instructions_top_left_.y + instructions_bottom_right_.y) / 2;

  vec2 top_block_top_left = instructions_top_left_;
  vec2 top_block_bottom_right = vec2(instructions_bottom_right_.x, mid_y);
  vec2 low_block_top_left = vec2(instructions_top_left_.x, mid_y);
  vec2 low_block_bottom_right = instructions_bottom_right_;

  DisplayText(top_block_top_left, top_block_bottom_right, "Click Encrypt or Decrypt to activate the display, click the bit sizes to change the key length");
  DisplayText(low_block_top_left, low_block_bottom_right, "Adjust the window size if text is too hard to read. Also, drag the mouse on progress bar above");

}

void DisplayHelper::DrawKeyButtons() {
  ci::gl::color(ci::Color("red"));
  ci::gl::drawStrokedRect(
      ci::Rectf(key_length_buttons_top_left_, key_length_buttons_bottom_right_));
  //TODO:: display key text
}

vec2 DisplayHelper::TextLocation(vec2 top_left, vec2 bottom_right) {
  float xAverage = (top_left.x + bottom_right.x) / 2;
  float yLocation = (top_left.y + bottom_right.y) / 2;

  return vec2(xAverage, yLocation);
}

void DisplayHelper::DisplayText(vec2 topLeftCorner,
                                      vec2 bottomRightCorner,
                                      string text) {
  
  
  const float fontSize = bottomRightCorner.y - topLeftCorner.y;
  const ci::Font font = ci::Font(kFontName, fontSize * 0.5);
  ci::gl::drawStringCentered(text,
                             TextLocation(topLeftCorner, bottomRightCorner),
                             kBorderColor,
                             font);
}


} //namespace visualizer

} //namespace aes