// D&T: 2022-10-15 11:12
// DES: 
//

#ifndef COOK_UTIL_H
#define COOK_UTIL_H

#include <android/asset_manager_jni.h>
#include <android/sensor.h>
#include <string>

ASensorManager *getASensorManager(const char *pkgName);

std::string readAsset(AAssetManager *assetManager, const char *filename);

#endif //COOK_UTIL_H
