package com.huoergai.gles

import android.content.Context
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView

/**
 * D&T: 2022-11-03 14:48
 * DES:
 */
class PagerViewAdapter(private val pages: List<Class<out BaseGLSurfaceView>>) :
  RecyclerView.Adapter<PagerViewAdapter.PagerViewHolder>() {

  class PagerViewHolder(view: View) : RecyclerView.ViewHolder(view)

  override fun getItemViewType(position: Int): Int = position

  override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PagerViewHolder {
    val view = pages[viewType].getDeclaredConstructor(Context::class.java)
      .newInstance(parent.context)
    view.layoutParams = ViewGroup.LayoutParams(
      ViewGroup.LayoutParams.MATCH_PARENT,
      ViewGroup.LayoutParams.MATCH_PARENT
    )
    return PagerViewHolder(view)
  }

  override fun onBindViewHolder(holder: PagerViewHolder, position: Int) {}

  override fun getItemCount(): Int = pages.size
}