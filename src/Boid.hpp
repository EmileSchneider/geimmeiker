#include "SceneObject.hpp"

#ifndef BOID_HPP
#define BOID_HPP

class Boid {
public:
  Boid();
  ~Boid();
  
  void render(const glm::mat4& view, const glm::mat4& projection);
private:
  SceneObject sceneObject;
};
#endif
