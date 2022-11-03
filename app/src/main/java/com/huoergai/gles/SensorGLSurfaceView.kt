package com.huoergai.gles

import android.content.Context
import android.content.res.AssetManager
import android.util.AttributeSet
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * D&T: 2022-10-31 15:52
 * DES:
 */
class SensorGLSurfaceView(context: Context, attr: AttributeSet? = null) :
  BaseGLSurfaceView(context, attr) {

  private external fun init(assetManager: AssetManager)
  private external fun surfaceCreated()
  private external fun surfaceChanged(width: Int, height: Int)
  private external fun drawFrame()
  private external fun pause()
  private external fun resume()

  companion object {
    init {
      System.loadLibrary("native_sensor")
    }
  }

  init {
    setEGLContextClientVersion(3)
    setEGLConfigChooser(8, 8, 8, 8, 16, 0)
    setRenderer(SensorSurfaceRender())
    queueEvent { init(context.assets) }
  }

  override fun onResume() {
    super.onResume()
    queueEvent { resume() }
  }

  override fun onPause() {
    super.onPause()
    queueEvent { pause() }
  }

  inner class SensorSurfaceRender : Renderer {
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
      surfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
      surfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
      drawFrame()
    }
  }
}