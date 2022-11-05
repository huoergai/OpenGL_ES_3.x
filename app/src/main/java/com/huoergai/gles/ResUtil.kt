package com.huoergai.gles

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import timber.log.Timber

/**
 * D&T: 2022-11-04 09:05
 * DES:
 */
object ResUtil {
  fun drawable2Bitmap(context: Context, resID: Int): Bitmap {
    val bitmap = BitmapFactory.decodeResource(context.resources, resID)
    Timber.tag("ResUtil")
      .d("${bitmap.density} : ${bitmap.config.name} ${bitmap.width}x${bitmap.height}")
    return bitmap
  }
}