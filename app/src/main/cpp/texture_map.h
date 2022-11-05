// D&T: 2022-11-03 15:56
// DES: 
//

#ifndef GLES_TEXTURE_MAP_H
#define GLES_TEXTURE_MAP_H

#include "util.h"
#include "gles_util.h"

class texture_map {
private:
    std::string vShaderSource;
    std::string fShaderSource;
    GLuint program;
    GLuint mTextureID;

    ImageData textureImg;

    GLuint vPositionLoc = 0;
    GLuint vTexCoordLoc = 1;
    GLint mSamplerLoc;

    GLint vertexSize = 3;
    GLint textureCoordSize = 2;
    GLfloat vertices[12] = {-1.0f, 0.5f, 0.0f,
                            -1.0f, -0.5f, 0.0f,
                            1.0f, -0.5f, 0.0f,
                            1.0f, 0.5f, 0.0f};

    GLfloat textureCoords[8] = {0.0f, 0.0f,
                                0.0f, 1.0f,
                                1.0f, 1.0f,
                                1.0f, 0.0f};

    GLushort indices[6] = {0, 1, 2, 0, 2, 3};

public:
    void init(AAssetManager *assetManager);

    void loadImage(ImageData *img);

    void onSurfaceCreated();

    void onSurfaceChanged(int w, int h);

    void onDraw();
};

#endif //GLES_TEXTURE_MAP_H
