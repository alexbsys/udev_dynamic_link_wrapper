#ifndef DYNAMIC_MODULES_LOADER_H
#define DYNAMIC_MODULES_LOADER_H

#include <string>
#include <memory>
#include "i_dynamic_modules_loader.h"

class DynamicModulesLoader : public virtual IDynamicModulesLoader {
public:
  DynamicModulesLoader();
  virtual ~DynamicModulesLoader() override;

  void* LoadModule(const std::string& module_path) override;
  void* GetProcAddress(void* module_handle, const std::string& function_name) override;
  void UnloadModule(void* module_handle) override;
};

std::shared_ptr<IDynamicModulesLoader> CreateDynamicModulesLoader();

#endif // DYNAMIC_MODULES_LOADER_H
