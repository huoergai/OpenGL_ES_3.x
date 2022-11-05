#include <jni.h>

// D&T: 2022-11-03 15:57
// DES: 
//
#include "texture_map.h"

texture_map textureMap;
extern "C" {
JNIEXPORT void JNICALL
Java_com_huoergai_gles_TextureMapView_init(JNIEnv *env, jobject thiz, jobject asset_manager) {
  AAssetManager *assetManager = AAssetManager_fromJava(env, asset_manager);
  textureMap.init(assetManager);
}

JNIEXPORT void JNICALL
Java_com_huoergai_gles_TextureMapView_setImgData(JNIEnv *env, jobject thiz, jint fmt, jint w,
                                                 jint h, jbyteArray bytes) {
  int len = env->GetArrayLength(bytes);
  auto *buf = new uint8_t[8];
  env->GetByteArrayRegion(bytes, 0, len, reinterpret_cast<jbyte *>(buf));

  ImageData imageData;
  imageData.fmt = fmt;
  imageData.w = w;
  imageData.h = h;
  imageData.ppPlane[0] = buf;

  switch (fmt) {
    case IMG_FMT_NV12:
    case IMG_FMT_NV21:
      imageData.ppPlane[1] = imageData.ppPlane[0] + w * h;
      break;
    case IMG_FMT_I420:
      imageData.ppPlane[1] = imageData.ppPlane[0] + w * h;
      imageData.ppPlane[2] = imageData.ppPlane[1] + w * h / 4;
      break;
    default:
      break;
  }

  // load img
  textureMap.loadImage(&imageData);

  delete[] buf;
  env->DeleteLocalRef(bytes);
  LOGD("image loaded");
}

JNIEXPORT void JNICALL
Java_com_huoergai_gles_TextureMapView_surfaceCreated(JNIEnv *env, jobject thiz) {
  textureMap.onSurfaceCreated();
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_TextureMapView_surfaceChanged(JNIEnv *env, jobject thiz, jint w, jint h) {
  textureMap.onSurfaceChanged(w, h);
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_TextureMapView_drawFrame(JNIEnv *env, jobject thiz) {
  textureMap.onDraw();
}

}
