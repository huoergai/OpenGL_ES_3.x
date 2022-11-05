package com.huoergai.gles

import android.os.Bundle
import com.google.android.material.tabs.TabLayoutMediator
import com.huoergai.gles.databinding.ActivityMainBinding

class MainActivity : BaseActivity() {

  private lateinit var binding: ActivityMainBinding
  private val viewTags = listOf("sensor", "triangle", "texture")
  private val clazzList = listOf(
    SensorGraphView::class.java,
    TriangleView::class.java,
    TextureMapView::class.java
  )

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    binding = ActivityMainBinding.inflate(layoutInflater)
    setContentView(binding.root)
    initView()
  }

  private fun initView() {
    val pager = binding.vp
    val tag = binding.tlTag
    pager.adapter = PagerViewAdapter(clazzList)
    TabLayoutMediator(tag, pager) { tab, pos ->
      tab.text = viewTags[pos]
    }.attach()
  }

}