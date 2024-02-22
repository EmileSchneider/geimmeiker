#include "Boid.hpp"
#include <cstdlib>
#include <glm/ext/matrix_transform.hpp>

Boid::Boid()
    : sceneObject(Model("boid.obj"), "BoidShader.vs",
                  "BoidShader.fs") // Use initializer list here
{
  float x =
      static_cast<float>(rand() % 10); // Random position between -50 and 50
  float y = static_cast<float>(rand() % 10);
  float z = static_cast<float>(rand() % 10);
  sceneObject.set_modelmatrix(
      glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)));
}

Boid::~Boid() {}

void Boid::render(const glm::mat4 &view, const glm::mat4 &projection) {
  sceneObject.render(view, projection);
}
