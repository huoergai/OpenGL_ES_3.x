package com.huoergai.gles

import android.content.Context
import android.util.AttributeSet
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * D&T: 2022-10-31 15:52
 * DES:
 */
class SensorGLSurfaceView(context: Context, attr: AttributeSet? = null) :
  BaseGLSurfaceView(context, attr) {

  init {
    setEGLContextClientVersion(3)
    setEGLConfigChooser(8, 8, 8, 8, 16, 0)
    renderMode = RENDERMODE_WHEN_DIRTY
    setRenderer(SensorSurfaceRender())
    queueEvent { NativeSensor.init(context.assets) }
  }

  override fun onResume() {
    super.onResume()
    queueEvent { NativeSensor.resume() }
  }

  override fun onPause() {
    super.onPause()
    queueEvent { NativeSensor.pause() }
  }

  class SensorSurfaceRender : Renderer {
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
      NativeSensor.surfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
      NativeSensor.surfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
      NativeSensor.drawFrame()
    }
  }
}