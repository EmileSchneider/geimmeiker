#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Shader::Shader() {}
Shader::~Shader() {}

void Shader::compile(const char *path, GLuint programID, bool vertexShaderp) {
  GLuint shaderID;
  if (vertexShaderp) {
    shaderID = glCreateShader(GL_VERTEX_SHADER);
  } else {
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  std::string shaderCode;
  std::ifstream shaderStream(path, std::ios::in);
  if (shaderStream.is_open()) {
    std::stringstream sstr;
    sstr << shaderStream.rdbuf();
    shaderCode = sstr.str();
    shaderStream.close();
  } else {
    printf("Impossible to open %s. Are you in the right directory ? Don't "
           "forget to read the FAQ !\n",
           path);
    getchar();
  }

  const char *sourcePointer = shaderCode.c_str();
  glShaderSource(shaderID, 1, &sourcePointer, NULL);
  glCompileShader(shaderID);

  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

  if (InfoLogLength > 0) {
    std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
    printf("%s\n", &ShaderErrorMessage[0]);
  }

  glAttachShader(programID, shaderID);
}


void Shader::linkProgram(GLuint programID) {
  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Link the program
  printf("Linking program\n");
  glLinkProgram(programID);

  // Check the program
  glGetProgramiv(programID, GL_LINK_STATUS, &Result);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(programID, InfoLogLength, NULL,
                        &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }
}
