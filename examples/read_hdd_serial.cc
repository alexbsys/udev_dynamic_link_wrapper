
#include "dynamic_modules_loader.h"
#include "udev_module_provider.h"

#ifdef _WIN32
#include <windows.h>
#else //_WIN32
#include <sys/stat.h>
#endif /*_WIN32*/

#include <memory>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

std::string get_hdd_serial_number(std::shared_ptr<IUdevModuleProvider> udev_mod, const std::string& disk_dev_path) {
  std::string serial_number;
  struct IUdevModuleProvider::udev *ud      = NULL;
  struct stat statbuf;
  struct IUdevModuleProvider::udev_device *device  = NULL;
  struct IUdevModuleProvider::udev_list_entry *entry   = NULL;

  ud = udev_mod->udev_new();
  if (NULL == ud) 
    return serial_number;

  if (0 != stat(disk_dev_path.c_str(), &statbuf))
    return serial_number;

  device = udev_mod->udev_device_new_from_devnum(ud, 'b', statbuf.st_rdev);
  if (NULL == device) 
    return serial_number;
      
  entry = udev_mod->udev_device_get_properties_list_entry(device);
  while (NULL != entry) {
    if (0 == strcmp(udev_mod->udev_list_entry_get_name(entry),"ID_SERIAL")) 
      break;

    entry = udev_mod->udev_list_entry_get_next(entry);
  }

  serial_number = udev_mod->udev_list_entry_get_value(entry);

  udev_mod->udev_device_unref(device);
  udev_mod->udev_unref(ud);

  return serial_number;
}

int main(int argc, char* argv[]) {
  std::shared_ptr<IDynamicModulesLoader> dynamic_modules_loader = CreateDynamicModulesLoader();
  std::shared_ptr<IUdevModuleProvider> udev_mod(new UdevModuleProvider(dynamic_modules_loader, false));
  if (!udev_mod->Load()) {
    std::cerr << "LIBUDEV was not loaded" << std::endl;
    return 254;
  }

  auto hdd_serial = get_hdd_serial_number(udev_mod,"/dev/sda");
  std::cout << "HDD serial: " << hdd_serial << std::endl;
  return 0;
}
