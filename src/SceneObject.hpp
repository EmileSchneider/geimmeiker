#include "Model.hpp"
#include "Shader.hpp"

#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP


class SceneObject {
public:
  SceneObject(Model m, std::string vs_path, std::string fs_path);
  ~SceneObject();

  glm::mat4 get_modelmatrix();
  void set_modelmatrix(glm::mat4 new_modelmatrix);
  void render(const glm::mat4& view, const glm::mat4& projection);
private:
  glm::mat4 modelmatrix;
  GLuint shaderProgramID;
  Model model;
  Shader vertexshader;
  Shader fragmentshader;
};

#endif
