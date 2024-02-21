#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {


public:  
  Shader();
  ~Shader();
  void compile(const char* path, GLuint programID, bool vertexShaderp);
  static void linkProgram(GLuint programID);
};


#endif
