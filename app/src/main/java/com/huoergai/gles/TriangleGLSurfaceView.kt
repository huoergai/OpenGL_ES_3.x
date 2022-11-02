package com.huoergai.gles

import android.content.Context
import android.util.AttributeSet
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * D&T: 2022-11-02 17:00
 * DES:
 */
class TriangleGLSurfaceView(context: Context, attr: AttributeSet? = null) :
  BaseGLSurfaceView(context, attr) {

  init {
    setEGLContextClientVersion(3)
    // setEGLConfigChooser(8, 8, 8, 8, 16, 0)
    // renderMode = RENDERMODE_WHEN_DIRTY
    setRenderer(TriangleRender())
    queueEvent { NativeTriangle.init(context.assets) }
  }

  class TriangleRender : Renderer {
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
      NativeTriangle.surfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
      NativeTriangle.surfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
      NativeTriangle.onDraw()
    }

  }

}