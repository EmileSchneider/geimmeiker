#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;
#ifndef CONTROLS_HPP
#define CONTROLS_HPP

class Controls {

public:
  Controls(GLFWwindow *window);
  ~Controls();
  void computeMatricesFromInputs();
  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();

private:
  GLFWwindow *c_window;
  
  glm::vec3 position = glm::vec3(0, 0, 5);
  float horizontalAngle = 3.14f;
  float verticalAngle = 0.0f;
  float initialFoV = 45.0f;
  float speed = 3.0f;
  float speedFast = 3.0f;
  float mouseSpeed = 0.00025f;
  glm::mat4 ViewMatrix;
  glm::mat4 ProjectionMatrix;

};

#endif
