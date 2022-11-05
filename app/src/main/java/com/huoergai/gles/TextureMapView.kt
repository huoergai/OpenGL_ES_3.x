package com.huoergai.gles

import android.content.Context
import android.content.res.AssetManager
import android.util.AttributeSet
import timber.log.Timber
import java.nio.ByteBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * D&T: 2022-11-03 15:18
 * DES: 纹理映射
 */
class TextureMapView @JvmOverloads constructor(context: Context, attr: AttributeSet? = null) :
  BaseGLSurfaceView(context, attr) {

  companion object {
    init {
      System.loadLibrary("native_texture")
    }
  }

  private external fun init(assetManager: AssetManager)
  private external fun setImgData(fmt: Int, w: Int, h: Int, bytes: ByteArray)
  private external fun surfaceCreated()
  private external fun surfaceChanged(w: Int, h: Int)
  private external fun drawFrame()

  init {
    setEGLContextClientVersion(3)
    setRenderer(TextureMapRender())
    renderMode = RENDERMODE_WHEN_DIRTY
    queueEvent {
      init(context.assets)
    }
  }

  private inner class TextureMapRender : Renderer {
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
      surfaceCreated()

      val bitmap = ResUtil.drawable2Bitmap(context, R.drawable.lake)
      val buff = ByteBuffer.allocate(bitmap.byteCount)
      bitmap.copyPixelsToBuffer(buff)
      setImgData(IMG_FMT_RGBA, bitmap.width, bitmap.height, buff.array())
      Timber.tag("GLES3.x").d("onSurfaceCreated")
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
      surfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
      drawFrame()
    }

  }

}