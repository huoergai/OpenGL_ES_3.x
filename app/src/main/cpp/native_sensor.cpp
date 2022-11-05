// D&T: 2022-10-17 08:16
// DES: 
//

#include <jni.h>
#include "sensor_graph.h"

SensorGraph gSensorGraph;
extern "C" {
JNIEXPORT void JNICALL
Java_com_huoergai_gles_SensorGraphView_init(JNIEnv *env, jobject thiz, jobject asset_manager) {
  AAssetManager *nativeAssetManager = AAssetManager_fromJava(env, asset_manager);
  gSensorGraph.init(nativeAssetManager);
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_SensorGraphView_surfaceCreated(JNIEnv *env, jobject thiz) {
  gSensorGraph.surfaceCreated();
}
extern "C" JNIEXPORT void JNICALL
Java_com_huoergai_gles_SensorGraphView_surfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                      jint height) {
  gSensorGraph.surfaceChanged(width, height);
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_SensorGraphView_drawFrame(JNIEnv *env, jobject thiz) {
  gSensorGraph.readSensor();
  gSensorGraph.render();
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_SensorGraphView_pause(JNIEnv *env, jobject thiz) {
  gSensorGraph.pause();
}
JNIEXPORT void JNICALL
Java_com_huoergai_gles_SensorGraphView_resume(JNIEnv *env, jobject thiz) {
  gSensorGraph.resume();
}

}