// D&T: 2022-11-03 15:56
// DES: 
//

#include "texture_map.h"
#include "cassert"

void texture_map::init(AAssetManager *assetManager) {
  vShaderSource = readAsset(assetManager, "texture_map.vsh");
  fShaderSource = readAsset(assetManager, "texture_map.fsh");
}

void texture_map::loadImage(ImageData *img) {
  textureImg.fmt = img->fmt;
  textureImg.w = img->w;
  textureImg.h = img->h;
  if (textureImg.ppPlane[0] == nullptr) {
    // allocate image memory
    switch (textureImg.fmt) {
      case IMG_FMT_RGBA:
        textureImg.ppPlane[0] = static_cast<uint8_t *>(malloc(textureImg.w * textureImg.h * 4));
        break;
      case IMG_FMT_YUYV:
        textureImg.ppPlane[0] = static_cast<uint8_t *>(malloc(textureImg.w * textureImg.h * 2));
        break;
      case IMG_FMT_NV12:
      case IMG_FMT_NV21: {
        auto byteCnt = static_cast<size_t>(textureImg.w * textureImg.h * 1.5);
        textureImg.ppPlane[0] = static_cast<uint8_t *>(malloc(byteCnt));
        textureImg.ppPlane[1] = textureImg.ppPlane[0] + textureImg.w * textureImg.h;
      }
        break;
      case IMG_FMT_I420: {
        auto cnt = static_cast<size_t>(textureImg.w * textureImg.h * 1.5);
        textureImg.ppPlane[0] = static_cast<uint8_t *>(malloc(cnt));
        textureImg.ppPlane[1] = textureImg.ppPlane[0] + textureImg.w * textureImg.h;
        textureImg.ppPlane[2] = textureImg.ppPlane[1] + textureImg.w * (textureImg.h >> 2);
      }
        break;
      case IMG_FMT_I444:
        textureImg.ppPlane[0] = static_cast<uint8_t *>(malloc(textureImg.w * textureImg.h * 3));
        break;
      case IMG_FMT_GRAY:
        textureImg.ppPlane[0] = static_cast<uint8_t *>(malloc(textureImg.w * textureImg.h));
        break;
      case IMG_FMT_P010:
        textureImg.ppPlane[0] = static_cast<uint8_t *>(malloc(textureImg.w * textureImg.h * 3));
        textureImg.ppPlane[1] = textureImg.ppPlane[0] + textureImg.w * textureImg.h * 2;
        break;
      default:
        // shouldn't be here
        break;
    }
  }

  // copy pixel data
  switch (img->fmt) {
    case IMG_FMT_I420:
    case IMG_FMT_NV21:
    case IMG_FMT_NV12:
      memcpy(textureImg.ppPlane[0], img->ppPlane[0], static_cast<size_t>(img->w * img->h * 1.5));
      break;
    case IMG_FMT_YUYV:
      memcpy(textureImg.ppPlane[0], img->ppPlane[0], img->w * img->h * 2);
      break;
    case IMG_FMT_RGBA:
      memcpy(textureImg.ppPlane[0], img->ppPlane[0], img->w * img->h * 4);
      break;
    case IMG_FMT_GRAY:
      memcpy(textureImg.ppPlane[0], img->ppPlane[0], img->w * img->h);
      break;
    case IMG_FMT_P010:
    case IMG_FMT_I444:
      memcpy(textureImg.ppPlane[0], img->ppPlane[0], img->w * img->h * 3);
      break;
    default:
      // shouldn't be here
      break;
  }

}

void texture_map::onSurfaceCreated() {
  program = createProgram(vShaderSource, fShaderSource);

  mSamplerLoc = glGetUniformLocation(program, "sTextureMap");

  // create rgba texture
  glGenTextures(1, &mTextureID);
  glBindTexture(GL_TEXTURE_2D, mTextureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);

  LOGD("texture created");
}

void texture_map::onSurfaceChanged(int w, int h) {
  glViewport(0, 0, w, h);
}

void texture_map::onDraw() {
  LOGD("onDraw start");
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  LOGD("clear");

  // load image data
  glActiveTexture(GL_TEXTURE0);
  LOGD("onDraw 0");
  glBindTexture(GL_TEXTURE_2D, mTextureID);
  LOGD("onDraw 1");
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImg.w, textureImg.h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               textureImg.ppPlane[0]);
  LOGD("onDraw 2");
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
  LOGD("texture loaded");

  glUseProgram(program);

  // load vertex position
  glVertexAttribPointer(vPositionLoc, vertexSize, GL_FLOAT, GL_FALSE, 0, vertices);
  // load texture coordinate
  glVertexAttribPointer(vTexCoordLoc, textureCoordSize, GL_FLOAT, GL_FALSE, 0, textureCoords);

  glEnableVertexAttribArray(vPositionLoc);
  glEnableVertexAttribArray(vTexCoordLoc);
  LOGD("shader loaded");

  // bind rgba map
  glActiveTexture(GL_TEXTURE);
  glBindTexture(GL_TEXTURE_2D, mTextureID);
  LOGD("use texture");

  glUniform1i(mSamplerLoc, 0);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}