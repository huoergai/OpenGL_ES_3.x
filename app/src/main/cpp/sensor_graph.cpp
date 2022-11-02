// D&T: 2022-10-14 16:06
// DES: 
//

#include <dlfcn.h>
#include <android/log.h>
#include <android/api-level.h>
#include <cassert>
#include "gles_util.h"
#include "util.h"

#include "sensor_graph.h"

#define  LOG_TAG    "sensor_graph"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void SensorGraph::setupSensor() {
  sensorManager = getASensorManager("com.huoergai.gles");
  assert(sensorManager != nullptr);
  accelerometer = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
  assert(accelerometer != nullptr);
  looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
  assert(looper != nullptr);
  eventQueue = ASensorManager_createEventQueue(sensorManager, looper, LOOPER_EVENT_ID,
                                               nullptr, nullptr);
  assert(eventQueue != nullptr);
  auto status = ASensorEventQueue_enableSensor(eventQueue, accelerometer);
  assert(status >= 0);
  status = ASensorEventQueue_setEventRate(eventQueue, accelerometer, REFRESH_PERIOD_US);
  assert(status >= 0);
}

void SensorGraph::generateXPos() {
  for (auto i = 0; i < SENSOR_HISTORY_LEN; i++) {
    float t = static_cast<float>(i) / static_cast<float>(SENSOR_HISTORY_LEN - 1);
    // xPos[i] = -1.f * (1.f - t) + 1.f * t; // [-1,1]
    xPos[i] = 2.0f * t - 1.0f;
  }
}

void SensorGraph::init(AAssetManager *assetManager) {
  vertexShaderSource = readAsset(assetManager, "sensor_graph.glslv");
  fragmentShaderSource = readAsset(assetManager, "sensor_graph.glslf");
  setupSensor();
  generateXPos();
}

void SensorGraph::surfaceCreated() {
  LOGI("GL_VERSION: %s", glGetString(GL_VERSION));
  LOGI("GL_VENDOR: %s", glGetString(GL_VENDOR));
  LOGI("GL_RENDERER: %s", glGetString(GL_RENDERER));
  LOGI("GL_EXTENSIONS: %s", glGetString(GL_EXTENSIONS));

  shaderProgram = createProgram(vertexShaderSource, fragmentShaderSource);
  assert(shaderProgram != 0);
  GLint getPositionLocationRet = glGetAttribLocation(shaderProgram, "vPosition");
  assert(getPositionLocationRet != -1);
  vPositionHandle = (GLuint) getPositionLocationRet;
  GLint getSensorValueLocationRet = glGetAttribLocation(shaderProgram, "vSensorValue");
  assert(getSensorValueLocationRet != -1);
  vSensorValueHandle = (GLuint) getSensorValueLocationRet;
  GLint getFragColorLocationRet = glGetUniformLocation(shaderProgram, "uFragColor");
  assert(getFragColorLocationRet != -1);
  uFragColorHandle = (GLuint) getFragColorLocationRet;
}

void SensorGraph::surfaceChanged(int w, int h) {
  glViewport(0, 0, w, h);
}

void SensorGraph::readSensor() {
  ALooper_pollAll(0, nullptr, nullptr, nullptr);
  ASensorEvent event;
  float a = SENSOR_FILTER_ALPHA;
  while (ASensorEventQueue_getEvents(eventQueue, &event, 1) > 0) {
    sensorDataSample.x = a * event.acceleration.x + (1.0f - a) * sensorDataSample.x;
    sensorDataSample.y = a * event.acceleration.y + (1.0f - a) * sensorDataSample.y;
    sensorDataSample.z = a * event.acceleration.z + (1.0f - a) * sensorDataSample.z;
  }
  sensorData[sensorDataIndex] = sensorDataSample;
  sensorData[SENSOR_HISTORY_LEN + sensorDataIndex] = sensorDataSample;
  sensorDataIndex = (sensorDataIndex + 1) % SENSOR_HISTORY_LEN;
}

void SensorGraph::render() {
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);

  glEnableVertexAttribArray(vPositionHandle);
  glVertexAttribPointer(vPositionHandle, 1, GL_FLOAT, GL_FALSE, 0, xPos);

  glEnableVertexAttribArray(vSensorValueHandle);

  glVertexAttribPointer(vSensorValueHandle, 1, GL_FLOAT, GL_FALSE, sizeof(AccelerometerData),
                        &sensorData[sensorDataIndex].x);
  glUniform4f(uFragColorHandle, 1.0f, 0.0f, 0.0f, 1.0f);
  glDrawArrays(GL_LINE_STRIP, 0, SENSOR_HISTORY_LEN);

  glVertexAttribPointer(vSensorValueHandle, 1, GL_FLOAT, GL_FALSE, sizeof(AccelerometerData),
                        &sensorData[sensorDataIndex].y);
  glUniform4f(uFragColorHandle, 0.0f, 1.0f, 0.0f, 1.0f);
  glDrawArrays(GL_LINE_STRIP, 0, SENSOR_HISTORY_LEN);

  glVertexAttribPointer(vSensorValueHandle, 1, GL_FLOAT, GL_FALSE, sizeof(AccelerometerData),
                        &sensorData[sensorDataIndex].z);
  glUniform4f(uFragColorHandle, 1.0f, 1.0f, 0.0f, 1.0f);
  glDrawArrays(GL_LINE_STRIP, 0, SENSOR_HISTORY_LEN);
}

void SensorGraph::pause() {
  ASensorEventQueue_disableSensor(eventQueue, accelerometer);
}

void SensorGraph::resume() {
  auto status = ASensorEventQueue_enableSensor(eventQueue, accelerometer);
  assert(status >= 0);
  status = ASensorEventQueue_setEventRate(eventQueue, accelerometer, REFRESH_PERIOD_US);
  assert(status >= 0);
}

