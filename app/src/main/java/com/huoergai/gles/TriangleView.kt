package com.huoergai.gles

import android.content.Context
import android.content.res.AssetManager
import android.util.AttributeSet
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * D&T: 2022-11-02 17:00
 * DES: 绘制彩色三角形
 */
class TriangleView @JvmOverloads constructor(context: Context, attr: AttributeSet? = null) :
  BaseGLSurfaceView(context, attr) {

  private external fun init(assetManager: AssetManager)
  private external fun surfaceCreated()
  private external fun surfaceChanged(width: Int, height: Int)
  private external fun drawFrame()

  companion object {
    init {
      System.loadLibrary("native_triangle")
    }
  }

  init {
    setEGLContextClientVersion(3)
    setRenderer(TriangleRender())
    renderMode = RENDERMODE_WHEN_DIRTY
    queueEvent { init(context.assets) }
  }

  inner class TriangleRender : Renderer {
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