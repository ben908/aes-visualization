#include "visualizer/state_displayer.h"

#include <cinder/gl/gl.h>

#include <tuple>

namespace aes {

namespace visualizer {

StateDisplayer::StateDisplayer(size_t width, size_t height) {
  display_helper_ = DisplayHelper(width, height);
  
}

void StateDisplayer::DisplayStateChange(
    tuple<AES::Step, unsigned char *>* currentState) {
  
  DisplaySingleState(top_left_,
                     bottom_right_,
                     std::get<1>(*currentState));
  
}

void StateDisplayer::SetDimensions(size_t width, size_t height) {
  display_helper_.SetDimensions(width, height);
  top_left_ = display_helper_.GetStateDisplayAreaTopLeft();
  bottom_right_ = display_helper_.GetStateDisplayAreaBottomRight();
}

void StateDisplayer::DisplaySecondaryInfo(double percent,
                                          const string& message,
                                          const string& key,
                                          const string& current_step) {
  display_helper_.DisplayInfoForState(percent, message, key, current_step);
}

void StateDisplayer::DisplaySingleState(const vec2& top_left,
                                        const vec2& bottom_right,
                                        const unsigned char* current_state) {
  size_t grid_box_width = (bottom_right.x - top_left.x) / 4;
  size_t grid_box_height = (bottom_right.y - top_left.y) / 4;
  
  for (size_t row = 0; row < 4; ++row) {
    for (size_t col = 0; col < 4; ++col) {
      
      ci::gl::color(DisplayHelper::kBorderColor);
      vec2 pixel_top_left = top_left + vec2(col * grid_box_width,
                                                    row * grid_box_height);

      vec2 pixel_bottom_right =
          pixel_top_left + vec2(grid_box_width, grid_box_height);
      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);


      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedRect(pixel_bounding_box);
      std::stringstream ss;
      ss << std::hex << (int)current_state[row + 4 * col];
      string data = ss.str();
      if (data.size() == 1) data = "0" + data;
      data = "0x" + data;
      DisplayHelper::DisplayText(pixel_top_left, pixel_bottom_right, data);
    }
  }
  
  
}

} //namespace visualizer

} //namespace aes