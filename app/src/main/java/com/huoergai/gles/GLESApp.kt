package com.huoergai.gles

import android.app.Application
import timber.log.Timber

/**
 * D&T: 2022-11-03 13:44
 * DES: OpenGL ES 3.x Android 学习实践
 */
class GLESApp : Application() {

  override fun onCreate() {
    super.onCreate()

    setupLog()
  }

  private fun setupLog() {
    if (BuildConfig.DEBUG) {
      Timber.plant(Timber.DebugTree())
    }
  }

}