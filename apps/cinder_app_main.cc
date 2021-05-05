#include <cinder/app/RendererGl.h>
#include <visualizer/aes_app.h>

using aes::visualizer::AESApp;

void prepareSettings(AESApp::Settings* settings) {
  settings->setResizable(true);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(AESApp, ci::app::RendererGl, prepareSettings);
