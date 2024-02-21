#include "Grid.hpp"


Grid::Grid(int gridSize, float step) {
  for (int i = -gridSize; i <= gridSize; ++i) {
    float iStep = i * step;
    // Vertical line
    vertices.push_back(glm::vec3(iStep, 0, -gridSize * step));
    vertices.push_back(glm::vec3(iStep, 0, gridSize * step));
    // Horizontal line
    vertices.push_back(glm::vec3(-gridSize * step, 0, iStep));
    vertices.push_back(glm::vec3(gridSize * step, 0, iStep));
  }

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
               &vertices[0], GL_STATIC_DRAW);
}

Grid::~Grid() {
  
}
void Grid::bind_vertexbuffer() {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(0,
                        3,        // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
}

void Grid::opengl_draw() {
  bind_vertexbuffer();
  glDrawArrays(GL_LINES, 0, vertices.size() * 3);  
}
