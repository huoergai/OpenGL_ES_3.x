package com.huoergai.gles

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * D&T: 2022-10-31 15:52
 * DES:
 */
class SensorGLSurfaceView(context: Context, attr: AttributeSet? = null) :
  GLSurfaceView(context, attr) {

  init {
    setEGLContextClientVersion(3)
    setRenderer(SensorSurfaceRender())
    queueEvent { SensorGraph.init(context.assets) }
  }

  override fun onResume() {
    super.onResume()
    queueEvent { SensorGraph.resume() }
  }

  override fun onPause() {
    super.onPause()
    queueEvent { SensorGraph.pause() }
  }

  class SensorSurfaceRender : Renderer {
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
      SensorGraph.surfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
      SensorGraph.surfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
      SensorGraph.drawFrame()
    }
  }
}