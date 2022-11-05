// D&T: 2022-10-31 16:07
// DES: 
//

#ifndef GLES_GLES_UTIL_H
#define GLES_GLES_UTIL_H

#include <GLES3/gl32.h>
#include <string>

const int IMG_FMT_RGBA = 0x01;
const int IMG_FMT_NV21 = 0x02;
const int IMG_FMT_NV12 = 0x03;
const int IMG_FMT_I420 = 0x04;
const int IMG_FMT_YUYV = 0x05;
const int IMG_FMT_GRAY = 0x06;
const int IMG_FMT_I444 = 0x07;
const int IMG_FMT_P010 = 0x08;

const std::string IMG_FMT_RGBA_EXT = "RGB32";
const std::string IMG_FMT_NV21_EXT = "NV21";
const std::string IMG_FMT_NV12_EXT = "NV12";
const std::string IMG_FMT_I420_EXT = "I420";
const std::string IMG_FMT_YUYV_EXT = "YUYV";
const std::string IMG_FMT_GRAY_EXT = "GRAY";
const std::string IMG_FMT_I444_EXT = "I444";
const std::string IMG_FMT_P010_EXT = "P010"; // 16 bit NV21

struct ImageData {
    int w;
    int h;
    int fmt;
    uint8_t *ppPlane[3];

    ImageData() {
      w = 0;
      h = 0;
      fmt = 0;
      ppPlane[0] = nullptr;
      ppPlane[1] = nullptr;
      ppPlane[2] = nullptr;
    }
};

GLuint loadShader(GLenum shaderType, const std::string &source);

GLuint createProgram(const std::string &vtxSource, const std::string &frgmtSource);

#endif //GLES_GLES_UTIL_H
