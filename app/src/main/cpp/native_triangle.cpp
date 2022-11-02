#include <jni.h>
#include "simple_triangle.h"

// D&T: 2022-11-02 16:43
// DES: 
//


simple_triangle simpleTriangle;
extern "C" {
JNIEXPORT void JNICALL
Java_com_huoergai_gles_NativeTriangle_init(JNIEnv *env, jobject thiz, jobject asset_manager) {
  AAssetManager *assetManager = AAssetManager_fromJava(env, asset_manager);
  simpleTriangle.init(assetManager);
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_NativeTriangle_surfaceCreated(JNIEnv *env, jobject thiz) {
  simpleTriangle.onSurfaceCreated();
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_NativeTriangle_surfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                     jint height) {
  simpleTriangle.onSurfaceChanged(width, height);
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_NativeTriangle_onDraw(JNIEnv *env, jobject thiz) {
  simpleTriangle.onDraw();
}
}