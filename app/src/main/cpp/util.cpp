// D&T: 2022-10-15 11:12
// DES: 
//

#include "util.h"

#include <cassert>
#include <dlfcn.h>

ASensorManager *getASensorManager(const char *pkgName) {
  void *androidHandle = dlopen("libandroid.so", RTLD_NOW);
  int apiLevel = android_get_device_api_level();
  if (apiLevel < __ANDROID_API_O__) {
    typedef ASensorManager *(*PF_GETINSTANCE)();
    auto getInstanceFunc = (PF_GETINSTANCE) dlsym(androidHandle, "ASensorManager_getInstance");
    assert(getInstanceFunc);
    return getInstanceFunc();
  } else {
    typedef ASensorManager *(*PF_GETINSTANCEFORPACKAGE)(const char *name);
    auto getInstanceForPackageFunc = (PF_GETINSTANCEFORPACKAGE)
            dlsym(androidHandle, "ASensorManager_getInstanceForPackage");
    if (getInstanceForPackageFunc) {
      return getInstanceForPackageFunc(pkgName);
    }
  }
  return nullptr;
}

std::string readAsset(AAssetManager *assetManager, const char *filename) {
  AAsset *asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
  assert(asset != nullptr);
  const void *buf = AAsset_getBuffer(asset);
  assert(buf != nullptr);
  off_t len = AAsset_getLength(asset);
  std::string source = std::string((const char *) buf, (size_t) len);
  AAsset_close(asset);
  return source;
}