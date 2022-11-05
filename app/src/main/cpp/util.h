// D&T: 2022-10-15 11:12
// DES: 
//

#ifndef COOK_UTIL_H
#define COOK_UTIL_H

#include <android/asset_manager_jni.h>
#include <android/sensor.h>
#include <string>
#include <android/log.h>

#define  TAG    "GLES3.x"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

ASensorManager *getASensorManager(const char *pkgName);

std::string readAsset(AAssetManager *assetManager, const char *filename);

#endif //COOK_UTIL_H
