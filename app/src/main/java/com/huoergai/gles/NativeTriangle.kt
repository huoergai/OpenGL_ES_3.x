package com.huoergai.gles

import android.content.res.AssetManager

/**
 * D&T: 2022-11-02 16:43
 * DES:
 */
object NativeTriangle {
  init {
    System.loadLibrary("native_triangle")
  }

  external fun init(assetManager: AssetManager)
  external fun surfaceCreated()
  external fun surfaceChanged(width: Int, height: Int)
  external fun onDraw()
}