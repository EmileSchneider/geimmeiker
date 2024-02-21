#include <GLFW/glfw3.h>

#ifndef GMWINDOW_HPP
#define GMWINDOW_HPP

class GMWindow {
  GMWindow();
  ~GMWindow();
  GLFWwindow* window;
  int get_height();
  int get_width();

private:
  int height;
  int width;
};

#endif
