#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

#include <GL/glew.h>

#include "Controls.hpp"
#include "GMApp.hpp"
#include "Grid.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "objloader.hpp"
#include "texture.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace glm;

GMApp::GMApp() : window(nullptr) {}

GMApp::~GMApp() { terminate(); }

bool GMApp::initialize(int width, int height, const char *title) {
  glewExperimental = true; // Needed for core profile
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return false;
  }

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);

  if (window == NULL) {
    fprintf(stderr,
            "Failed to open GLFW window. If you have an Intel GPU, they are "
            "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window); // Initialize GLEW
  glewExperimental = true;        // Needed in core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return false;
  }

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  return true;
}

void GMApp::run() { mainLoop(); }

void GMApp::mainLoop() {

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  GLuint programID = glCreateProgram();

  Shader vertexShader;
  Shader fragmentShader;

  vertexShader.compile("SimpleVertexShader.vertexshader", programID, true);
  fragmentShader.compile("SimpleFragmentShader.fragmentshader", programID,
                         false);

  Shader::linkProgram(programID);

  GLuint gridShaderProgramID = glCreateProgram();
  Shader gridVertexShader;
  Shader gridFragmentShader;
  gridVertexShader.compile("GridShader.vs", gridShaderProgramID, true);
  gridFragmentShader.compile("GridShader.fs", gridShaderProgramID, false);

  Shader::linkProgram(gridShaderProgramID);

  GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  Controls controls = Controls(window);

  Model model = Model("simple_model.obj");

  /*
   * 3D-Grid setup
   */
  Grid grid = Grid(50, 1.0);

  GLuint Texture = loadBMP_custom("bmp_24.bmp");

  GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

  // BOID
  Model boid = Model("boid.obj");

  GLuint boidShaderProgramID = glCreateProgram();
  Shader boidVertexShader;
  Shader boiddFragmentShader;
  gridVertexShader.compile("BoidShader.vs", boidShaderProgramID, true);
  gridFragmentShader.compile("BoidShader.fs", boidShaderProgramID, false);

  Shader::linkProgram(boidShaderProgramID);
  
  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUseProgram(programID);
    controls.computeMatricesFromInputs();

    glm::mat4 Projection = controls.getProjectionMatrix();
    glm::mat4 View = controls.getViewMatrix();
    glm::mat4 ModelMatrix = glm::mat4(
        1.0f); // glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
    glm::mat4 MVP = Projection * View * ModelMatrix;

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(TextureID, 0);

    model.render();

    for (int i = 0; i < 10; i++) {
      glm::mat4 tModelMatrix =
          glm::translate(ModelMatrix, glm::vec3(i * 5.0f, i * 1.0f, i * 1.0f));
      glm::mat4 tMVP = Projection * View * tModelMatrix;

      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tMVP[0][0]);

      model.render();
    }

    glUseProgram(gridShaderProgramID);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    grid.opengl_draw();

    glUseProgram(boidShaderProgramID);

    glm::mat4 bMVP = Projection * View * glm::translate(ModelMatrix, glm::vec3(3.0f, 3.0f, 3.0f));  
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &bMVP[0][0]);
    
    boid.render();
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glfwSwapBuffers(window);
    glfwPollEvents();

  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
}

void GMApp::terminate() { glfwTerminate(); }
