#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#ifndef MODEL_HPP
#define MODEL_HPP

class Model {

public:
  Model(const char *path);
  ~Model();
  void render();

  
private:
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;

  GLuint vertexbuffer;
  GLuint uvbuffer;

  void opengl_bind_vertexbuffer();
  void opengl_bind_uvbuffer();
  void opengl_draw();
};
#endif
