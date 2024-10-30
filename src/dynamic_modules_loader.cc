
#include "dynamic_modules_loader.h"

#ifdef _WIN32
#	include <windows.h>
#else //_WIN32
#	include <dlfcn.h>
#	include <limits.h>
#endif //_WIN32

std::shared_ptr<IDynamicModulesLoader> CreateDynamicModulesLoader() {
  return std::make_shared<DynamicModulesLoader>();
}

DynamicModulesLoader::DynamicModulesLoader() {
}

DynamicModulesLoader::~DynamicModulesLoader() {
}

void* DynamicModulesLoader::LoadModule(const std::string& module_path) {
  void* module_handle = nullptr;

#ifdef _WIN32
  module_handle = LoadLibraryA(module_path.c_str());
#else //_WIN32
  module_handle = dlopen(module_path.c_str(), RTLD_LAZY);
#endif //_WIN32

  return module_handle;
}

void* DynamicModulesLoader::GetProcAddress(void* module_handle, const std::string& function_name) {
  void* fn_addr = nullptr;
#ifdef _WIN32
  fn_addr = reinterpret_cast<void*>(
      ::GetProcAddress(reinterpret_cast<HMODULE>(module_handle), function_name.c_str()));
#else //_WIN32
  fn_addr = dlsym(module_handle, function_name.c_str());

#endif //_WIN32
  return fn_addr;
}

void DynamicModulesLoader::UnloadModule(void* module_handle) {
#ifdef _WIN32
    FreeLibrary(reinterpret_cast<HMODULE>(module_handle));
#else //_WIN32
    dlclose(module_handle);
#endif //_WIN32
}
