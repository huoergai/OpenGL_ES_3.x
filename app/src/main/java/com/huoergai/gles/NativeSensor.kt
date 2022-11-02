package com.huoergai.gles

import android.content.res.AssetManager

/**
 * D&T: 2022-10-14 16:09
 * DES:
 */
object NativeSensor {
  init {
    System.loadLibrary("native_sensor")
  }

  external fun init(assetManager: AssetManager)
  external fun surfaceCreated()
  external fun surfaceChanged(width: Int, height: Int)
  external fun drawFrame()
  external fun pause()
  external fun resume()
}