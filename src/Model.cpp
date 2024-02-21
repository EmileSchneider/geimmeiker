#include "Model.hpp"
#include "objloader.hpp"

Model::Model(const char *path) {
  bool res = loadOBJ(path, vertices, uvs, normals);

  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
               &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &uvbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
  glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0],
               GL_STATIC_DRAW);
}

void Model::render() {
  opengl_bind_vertexbuffer();
  opengl_bind_uvbuffer();
  opengl_draw();
}

void Model::opengl_bind_vertexbuffer() {
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

void Model::opengl_bind_uvbuffer() {
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
  glVertexAttribPointer(1,
                        2,        // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
  );
}

void Model::opengl_draw() {
  glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 3);
}

Model::~Model() {}
