// D&T: 2022-11-02 15:14
// DES: 
//

#ifndef GLES_SIMPLE_TRIANGLE_H
#define GLES_SIMPLE_TRIANGLE_H

#include <android/asset_manager_jni.h>
#include <GLES3/gl32.h>
#include <string>

class simple_triangle {
private:
    int VERTEX_POSITION_SIZE = 3;
    int FRAG_COLOR_SIZE = 4;
    float vertices[9] = {-0.5f, -0.5f, 0.0f,
                         0.5f, -0.5f, 0.0f,
                         0.0f, 0.5f, 0.0f,};

    float fragColors[12] = {1.0f, 0.0f, 0.0f, 1.0f,
                            0.0f, 1.0f, 0.0f, 1.0f,
                            0.0f, 0.0f, 1.0f, 1.0f};

    std::string vertexSource;
    std::string fragmtSource;
    GLuint program;
    GLuint vPositionHandle = 0;
    GLuint uFragColorHandle = 1;
public:
    void init(AAssetManager *assetManager);

    void onSurfaceCreated();

    void onSurfaceChanged(int w, int h);

    void onDraw();

};

#endif //GLES_SIMPLE_TRIANGLE_H
