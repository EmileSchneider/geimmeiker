#include "SceneObject.hpp"
#include <glm/gtc/type_ptr.hpp>

SceneObject::SceneObject(Model m, std::string vs_path, std::string fs_path)
    : model(m) {
  shaderProgramID = glCreateProgram();
  vertexshader.compile(vs_path.c_str(), shaderProgramID, true);
  fragmentshader.compile(fs_path.c_str(), shaderProgramID, false);

  Shader::linkProgram(shaderProgramID);

  modelmatrix = glm::mat4(1.0f);
}

SceneObject::~SceneObject() {}

void SceneObject::render(const glm::mat4 &view, const glm::mat4 &projection) {
  glm::mat4 modelMatrix = get_modelmatrix();
  glm::mat4 mvp = projection * view * modelMatrix;

  glUseProgram(shaderProgramID);

  // Assuming you have a uniform location for the MVP matrix in your shader
  GLuint mvpLocation = glGetUniformLocation(shaderProgramID, "MVP");
  glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
  model.render();
}

glm::mat4 SceneObject::get_modelmatrix() { return modelmatrix; }

void SceneObject::set_modelmatrix(glm::mat4 new_modelmatrix) {
  modelmatrix = new_modelmatrix;
}
