// D&T: 2022-11-02 15:14
// DES: 
//

#include "simple_triangle.h"
#include "gles_util.h"
#include "cassert"
#include "util.h"

void simple_triangle::init(AAssetManager *assetManager) {
  vertexSource = readAsset(assetManager, "simple_triangle.vs");
  fragmtSource = readAsset(assetManager, "simple_triangle.fs");
}

void simple_triangle::onSurfaceCreated() {
  program = createProgram(vertexSource, fragmtSource);
  assert(program != 0);
}

void simple_triangle::onSurfaceChanged(int w, int h) {
  glViewport(0, 0, w, h);
}

void simple_triangle::onDraw() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glUseProgram(program);

  // load vertex data
  glVertexAttribPointer(vPositionHandle, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, vertices);
  glEnableVertexAttribArray(vPositionHandle);

  // load color data
  glVertexAttribPointer(uFragColorHandle, FRAG_COLOR_SIZE, GL_FLOAT, GL_FALSE, 0, fragColors);
  glEnableVertexAttribArray(uFragColorHandle);

  // draw
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glUseProgram(GL_NONE);
}