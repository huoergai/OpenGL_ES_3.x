package com.huoergai.gles

import android.os.Bundle
import com.huoergai.gles.databinding.ActivityMainBinding

class MainActivity : BaseActivity() {

  private lateinit var binding: ActivityMainBinding

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)

    binding = ActivityMainBinding.inflate(layoutInflater)
    setContentView(binding.root)
  }

}