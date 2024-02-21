#ifndef GHAPP_H
#define GHAPP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GMApp {
 public:
  GMApp();
  ~GMApp();

  bool initialize(int width, int height, const char* title);
  void run();
  void terminate();
  
 private:
  GLFWwindow* window;
  void mainLoop();
};

#endif
