#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#ifndef GRID_HPP
#define GRID_HPP

class Grid {

public:
  Grid(int gridSize, float step);
  ~Grid();
  void opengl_draw();

private:
  void bind_vertexbuffer();
  std::vector<glm::vec3> vertices;
  GLuint vertexbuffer;
};

#endif
