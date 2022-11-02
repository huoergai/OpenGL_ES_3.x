// D&T: 2022-10-17 08:17
// DES: 
//

#ifndef COOK_SENSOR_GRAPH_H
#define COOK_SENSOR_GRAPH_H

#include <jni.h>
#include <cstdint>
#include <string>
#include <GLES3/gl32.h>
#include <android/sensor.h>
#include <android/asset_manager_jni.h>

const int LOOPER_EVENT_ID = 3;
const int SENSOR_HISTORY_LEN = 100;
// refresh rate Hz
const int REFRESH_RATE_HZ = 100;
// refresh period us
constexpr int32_t REFRESH_PERIOD_US = int32_t(1'000'000 / REFRESH_RATE_HZ);
const float SENSOR_FILTER_ALPHA = 0.1f;

class SensorGraph {
private:
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    ASensorManager *sensorManager;
    const ASensor *accelerometer;
    ASensorEventQueue *eventQueue;
    ALooper *looper;

    GLuint shaderProgram;
    GLuint vPositionLocation = 0;
    GLuint vSensorValueLocation = 1;
    GLuint uFragColorLocation = 2;
    GLfloat xPos[SENSOR_HISTORY_LEN];

    struct AccelerometerData {
        GLfloat x = 0.1f;
        GLfloat y = 0.6f;
        GLfloat z = 0.8f;
    };
    AccelerometerData sensorData[SENSOR_HISTORY_LEN * 2];
    AccelerometerData sensorDataSample;
    int sensorDataIndex = 0;

    void setupSensor();

    void generateXPos();

public:
    void init(AAssetManager *assetManager);

    void surfaceCreated();

    void surfaceChanged(int w, int h);

    void readSensor();

    void render();

    void pause();

    void resume();
};

#endif //COOK_SENSOR_GRAPH_H
