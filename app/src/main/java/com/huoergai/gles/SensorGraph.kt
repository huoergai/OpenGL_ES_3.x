package com.huoergai.gles

import android.content.res.AssetManager

/**
 * D&T: 2022-10-14 16:09
 * DES:
 */
object SensorGraph {
  init {
    System.loadLibrary("gles")
  }

  external fun init(assetManager: AssetManager)
  external fun surfaceCreated()
  external fun surfaceChanged(width: Int, height: Int)
  external fun drawFrame()
  external fun pause()
  external fun resume()
}