// D&T: 2022-10-31 16:07
// DES: 
//

#ifndef GLES_GLES_UTIL_H
#define GLES_GLES_UTIL_H

#include <GLES3/gl32.h>
#include <string>

GLuint loadShader(GLenum shaderType, const std::string &source);

GLuint createProgram(const std::string &vtxSource, const std::string &frgmtSource);

#endif //GLES_GLES_UTIL_H
