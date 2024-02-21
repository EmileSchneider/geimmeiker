#include "Controls.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Controls::Controls(GLFWwindow *window) : c_window(window) {
  glfwSetInputMode(c_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Controls::~Controls() {}
glm::mat4 Controls::getViewMatrix() { return Controls::ViewMatrix; }
glm::mat4 Controls::getProjectionMatrix() { return Controls::ProjectionMatrix; }

void Controls::computeMatricesFromInputs() {
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(c_window, &xpos, &ypos);

	// Reset mouse position for next frame
    int window_w, window_h;
    glfwGetWindowSize(c_window, &window_w, &window_h);
    
	glfwSetCursorPos(c_window, (float) window_w/2, (float) window_h/2);


	// Compute new orientation
	horizontalAngle += mouseSpeed * float((float) window_w/2 - xpos );
	verticalAngle   += mouseSpeed * float((float) window_h/2 - ypos );

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);    
	
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	glm::vec3 up = glm::cross( right, direction );

    if (glfwGetKey(c_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS){
      speed = 6.0f;
	} else {
      speed = 3.0f;
    }
	// Move forward
	if (glfwGetKey(c_window, GLFW_KEY_W ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(c_window, GLFW_KEY_S ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(c_window, GLFW_KEY_D ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(c_window, GLFW_KEY_A ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

    if (glfwGetKey(c_window, GLFW_KEY_Q ) == GLFW_PRESS){
      position += glm::vec3(0, deltaTime * speed, 0);
	}

    if (glfwGetKey(c_window, GLFW_KEY_E ) == GLFW_PRESS){
      position -= glm::vec3(0, deltaTime * speed, 0);
	}
    

	float FoV = initialFoV;

	ProjectionMatrix = glm::perspective(glm::radians(FoV), ((float)window_w) / ((float) window_h), 0.1f, 100.0f);
	ViewMatrix       = glm::lookAt(
								position,
								position+direction,
								up
						   );

	lastTime = currentTime;  
}
