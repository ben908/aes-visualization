#include "visualizer/state_displayer.h"

#include <cinder/gl/gl.h>

#include <tuple>

namespace aes {

namespace visualizer {

StateDisplayer::StateDisplayer(size_t width, size_t height) {
  display_helper_ = DisplayHelper(width, height);
  
}

void StateDisplayer::DisplayStateChange(
    tuple<AES::Step, unsigned char *>* currentState,
    tuple<AES::Step, unsigned char *>* nextState) {
  float mid_x = (top_left_.y + bottom_right_.y) / 2;

  vec2 right_block_top_left = top_left_;
  vec2 right_block_bottom_right = vec2(mid_x, bottom_right_.y);
  vec2 left_block_top_left = vec2(mid_x, top_left_.y);
  vec2 left_block_bottom_right = bottom_right_;

  DisplaySingleState(right_block_top_left,
                     right_block_bottom_right,
                     std::get<1>(*nextState));

  DisplaySingleState(left_block_top_left,
                     left_block_bottom_right,
                     std::get<1>(*currentState));
}

void StateDisplayer::SetDimensions(size_t width, size_t height) {
  display_helper_.SetDimensions(width, height);
  top_left_ = display_helper_.GetStateDisplayAreaTopLeft();
  bottom_right_ = display_helper_.GetStateDisplayAreaBottomRight();
}

void StateDisplayer::DisplaySecondaryInfo() {
  display_helper_.DisplayInfoForState(10.0, "test1", "test2", "test3");
}

void StateDisplayer::DisplaySingleState(vec2 top_left,
                                        vec2 bottom_right,
                                        unsigned char* currentState) {
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

//      ci::gl::drawSolidRect(pixel_bounding_box);

      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedRect(pixel_bounding_box);
    }
  }
  
  
}

} //namespace visualizer

} //namespace aes