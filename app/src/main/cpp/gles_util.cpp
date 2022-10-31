// D&T: 2022-10-31 16:07
// DES: 
//

#include "gles_util.h"
#include <cassert>

GLuint loadShader(GLenum shaderType, const std::string &source) {
  GLuint shader = glCreateShader(shaderType);
  assert(shader != 0);

  const char *sourceRef = source.c_str();
  glShaderSource(shader, 1, &sourceRef, nullptr);
  glCompileShader(shader);
  GLint compileStatus = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
  assert(compileStatus != 0);
  return shader;
}

GLuint createProgram(const std::string &vtxSource, const std::string &frgmtSource) {
  GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vtxSource);
  GLuint frgmtShader = loadShader(GL_FRAGMENT_SHADER, frgmtSource);

  GLuint program = glCreateProgram();
  assert(program != 0);

  glAttachShader(program, vertexShader);
  glAttachShader(program, frgmtShader);
  glLinkProgram(program);

  GLint linkStatus = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
  assert(linkStatus != 0);

  glDeleteShader(vertexShader);
  glDeleteShader(frgmtShader);

  return program;
}
