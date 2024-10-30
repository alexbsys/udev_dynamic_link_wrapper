
#include "udev_module_provider.h"
#include "dynamic_loader.hpp"
#include <sstream>
#include <iostream>

UdevModuleProvider::UdevModuleProvider(
    std::shared_ptr<IDynamicModulesLoader> dynamic_modules_loader,
    bool unload_on_destroy)
  :mod_loader_(dynamic_modules_loader)
  ,unload_on_destroy_(unload_on_destroy)
{
}

UdevModuleProvider::~UdevModuleProvider() {
  if (unload_on_destroy_ && udev_handle_) {
    mod_loader_->UnloadModule(udev_handle_);
    udev_handle_ = nullptr;
  }
}

bool UdevModuleProvider::IsLoaded() const {
  return udev_handle_ != nullptr;
}

bool UdevModuleProvider::Load() {
  if (udev_handle_)
    return true;

  udev_handle_ = mod_loader_->LoadModule("libudev.so");
  if (!udev_handle_) {
    udev_handle_ = mod_loader_->LoadModule("libudev.so.0");
    if (!udev_handle_) {
      udev_handle_ = mod_loader_->LoadModule("libudev.so.1");
      if (!udev_handle_)
        return false;
    }
  }

  std::stringstream problem_funcs;

  bool result = true;
  result &= LoadDllProc(udev_ref_, udev_handle_, "udev_ref", problem_funcs);
  result &= LoadDllProc(udev_unref_, udev_handle_, "udev_unref", problem_funcs);
  result &= LoadDllProc(udev_new_, udev_handle_, "udev_new", problem_funcs);
  result &= LoadDllProc(udev_set_log_fn_, udev_handle_, "udev_set_log_fn", problem_funcs);
  result &= LoadDllProc(udev_get_log_priority_, udev_handle_, "udev_get_log_priority", problem_funcs);
  result &= LoadDllProc(udev_set_log_priority_, udev_handle_, "udev_set_log_priority", problem_funcs);
  result &= LoadDllProc(udev_get_userdata_, udev_handle_, "udev_get_userdata", problem_funcs);
  result &= LoadDllProc(udev_set_userdata_, udev_handle_, "udev_set_userdata", problem_funcs);

  result &= LoadDllProc(udev_list_entry_get_next_, udev_handle_, "udev_list_entry_get_next", problem_funcs);
  result &= LoadDllProc(udev_list_entry_get_by_name_, udev_handle_, "udev_list_entry_get_by_name", problem_funcs);
  result &= LoadDllProc(udev_list_entry_get_name_, udev_handle_, "udev_list_entry_get_name", problem_funcs);
  result &= LoadDllProc(udev_list_entry_get_value_, udev_handle_, "udev_list_entry_get_value", problem_funcs);

  result &= LoadDllProc(udev_device_ref_, udev_handle_, "udev_device_ref", problem_funcs);
  result &= LoadDllProc(udev_device_unref_, udev_handle_, "udev_device_unref", problem_funcs);
  result &= LoadDllProc(udev_device_get_udev_, udev_handle_, "udev_device_get_udev", problem_funcs);
  result &= LoadDllProc(udev_device_new_from_syspath_, udev_handle_, "udev_device_new_from_syspath", problem_funcs);
  result &= LoadDllProc(udev_device_new_from_devnum_, udev_handle_, "udev_device_new_from_devnum", problem_funcs);
  result &= LoadDllProc(udev_device_new_from_subsystem_sysname_, udev_handle_, "udev_device_new_from_subsystem_sysname", problem_funcs);
  result &= LoadDllProc(udev_device_new_from_device_id_, udev_handle_, "udev_device_new_from_device_id", problem_funcs);
  result &= LoadDllProc(udev_device_new_from_environment_, udev_handle_, "udev_device_new_from_environment", problem_funcs);
  result &= LoadDllProc(udev_device_get_parent_, udev_handle_, "udev_device_get_parent", problem_funcs);
  result &= LoadDllProc(udev_device_get_parent_with_subsystem_devtype_, udev_handle_, "udev_device_get_parent_with_subsystem_devtype", problem_funcs);
  result &= LoadDllProc(udev_device_get_devpath_, udev_handle_, "udev_device_get_devpath", problem_funcs);
  result &= LoadDllProc(udev_device_get_subsystem_, udev_handle_, "udev_device_get_subsystem", problem_funcs);
  result &= LoadDllProc(udev_device_get_devtype_, udev_handle_, "udev_device_get_devtype", problem_funcs);
  result &= LoadDllProc(udev_device_get_syspath_, udev_handle_, "udev_device_get_syspath", problem_funcs);
  result &= LoadDllProc(udev_device_get_sysname_, udev_handle_, "udev_device_get_sysname", problem_funcs);
  result &= LoadDllProc(udev_device_get_sysnum_, udev_handle_, "udev_device_get_sysnum", problem_funcs);
  result &= LoadDllProc(udev_device_get_devnode_, udev_handle_, "udev_device_get_devnode", problem_funcs);
  result &= LoadDllProc(udev_device_get_is_initialized_, udev_handle_, "udev_device_get_is_initialized", problem_funcs);
  result &= LoadDllProc(udev_device_get_devlinks_list_entry_, udev_handle_, "udev_device_get_devlinks_list_entry", problem_funcs);
  result &= LoadDllProc(udev_device_get_properties_list_entry_, udev_handle_, "udev_device_get_properties_list_entry", problem_funcs);
  result &= LoadDllProc(udev_device_get_tags_list_entry_, udev_handle_, "udev_device_get_tags_list_entry", problem_funcs);
  result &= LoadDllProc(udev_device_get_current_tags_list_entry_, udev_handle_, "udev_device_get_current_tags_list_entry", problem_funcs);
  result &= LoadDllProc(udev_device_get_sysattr_list_entry_, udev_handle_, "udev_device_get_sysattr_list_entry", problem_funcs);
  result &= LoadDllProc(udev_device_get_property_value_, udev_handle_, "udev_device_get_property_value", problem_funcs);
  result &= LoadDllProc(udev_device_get_driver_, udev_handle_, "udev_device_get_driver", problem_funcs);
  result &= LoadDllProc(udev_device_get_devnum_, udev_handle_, "udev_device_get_devnum", problem_funcs);
  result &= LoadDllProc(udev_device_get_action_, udev_handle_, "udev_device_get_action", problem_funcs);
  result &= LoadDllProc(udev_device_get_seqnum_, udev_handle_, "udev_device_get_seqnum", problem_funcs);
  result &= LoadDllProc(udev_device_get_usec_since_initialized_, udev_handle_, "udev_device_get_usec_since_initialized", problem_funcs);
  result &= LoadDllProc(udev_device_get_sysattr_value_, udev_handle_, "udev_device_get_sysattr_value", problem_funcs);
  result &= LoadDllProc(udev_device_set_sysattr_value_, udev_handle_, "udev_device_set_sysattr_value", problem_funcs);
  result &= LoadDllProc(udev_device_has_tag_, udev_handle_, "udev_device_has_tag", problem_funcs);
  result &= LoadDllProc(udev_device_has_current_tag_, udev_handle_, "udev_device_has_current_tag", problem_funcs);
  result &= LoadDllProc(udev_monitor_ref_, udev_handle_, "udev_monitor_ref", problem_funcs);
  result &= LoadDllProc(udev_monitor_unref_, udev_handle_, "udev_monitor_unref", problem_funcs);
  result &= LoadDllProc(udev_monitor_get_udev_, udev_handle_, "udev_monitor_get_udev", problem_funcs);
  result &= LoadDllProc(udev_monitor_new_from_netlink_, udev_handle_, "udev_monitor_new_from_netlink", problem_funcs);
  result &= LoadDllProc(udev_monitor_enable_receiving_, udev_handle_, "udev_monitor_enable_receiving", problem_funcs);
  result &= LoadDllProc(udev_monitor_set_receive_buffer_size_, udev_handle_, "udev_monitor_set_receive_buffer_size", problem_funcs);
  result &= LoadDllProc(udev_monitor_get_fd_, udev_handle_, "udev_monitor_get_fd", problem_funcs);
  result &= LoadDllProc(udev_monitor_receive_device_, udev_handle_, "udev_monitor_receive_device", problem_funcs);
  result &= LoadDllProc(udev_monitor_filter_add_match_subsystem_devtype_, udev_handle_, "udev_monitor_filter_add_match_subsystem_devtype", problem_funcs);
  result &= LoadDllProc(udev_monitor_filter_add_match_tag_, udev_handle_, "udev_monitor_filter_add_match_tag", problem_funcs);
  result &= LoadDllProc(udev_monitor_filter_update_, udev_handle_, "udev_monitor_filter_update", problem_funcs);
  result &= LoadDllProc(udev_monitor_filter_remove_, udev_handle_, "udev_monitor_filter_remove", problem_funcs);
  result &= LoadDllProc(udev_enumerate_ref_, udev_handle_, "udev_enumerate_ref", problem_funcs);
  result &= LoadDllProc(udev_enumerate_unref_, udev_handle_, "udev_enumerate_unref", problem_funcs);
  result &= LoadDllProc(udev_enumerate_get_udev_, udev_handle_, "udev_enumerate_get_udev", problem_funcs);
  result &= LoadDllProc(udev_enumerate_new_, udev_handle_, "udev_enumerate_new", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_match_subsystem_, udev_handle_, "udev_enumerate_add_match_subsystem", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_nomatch_subsystem_, udev_handle_, "udev_enumerate_add_nomatch_subsystem", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_match_sysattr_, udev_handle_, "udev_enumerate_add_match_sysattr", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_nomatch_sysattr_, udev_handle_, "udev_enumerate_add_nomatch_sysattr", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_match_property_, udev_handle_, "udev_enumerate_add_match_property", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_match_sysname_, udev_handle_, "udev_enumerate_add_match_sysname", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_match_tag_, udev_handle_, "udev_enumerate_add_match_tag", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_match_parent_, udev_handle_, "udev_enumerate_add_match_parent", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_match_is_initialized_, udev_handle_, "udev_enumerate_add_match_is_initialized", problem_funcs);
  result &= LoadDllProc(udev_enumerate_add_syspath_, udev_handle_, "udev_enumerate_add_syspath", problem_funcs);
  result &= LoadDllProc(udev_enumerate_scan_devices_, udev_handle_, "udev_enumerate_scan_devices", problem_funcs);
  result &= LoadDllProc(udev_enumerate_scan_subsystems_, udev_handle_, "udev_enumerate_scan_subsystems", problem_funcs);
  result &= LoadDllProc(udev_enumerate_get_list_entry_, udev_handle_, "udev_enumerate_get_list_entry", problem_funcs);
  result &= LoadDllProc(udev_queue_ref_, udev_handle_, "udev_queue_ref", problem_funcs);
  result &= LoadDllProc(udev_queue_unref_, udev_handle_, "udev_queue_unref", problem_funcs);
  result &= LoadDllProc(udev_queue_get_udev_, udev_handle_, "udev_queue_get_udev", problem_funcs);
  result &= LoadDllProc(udev_queue_new_, udev_handle_, "udev_queue_new", problem_funcs);
  result &= LoadDllProc(udev_queue_get_kernel_seqnum_, udev_handle_, "udev_queue_get_kernel_seqnum", problem_funcs);
  result &= LoadDllProc(udev_queue_get_udev_seqnum_, udev_handle_, "udev_queue_get_udev_seqnum", problem_funcs);
  result &= LoadDllProc(udev_queue_get_udev_is_active_, udev_handle_, "udev_queue_get_udev_is_active", problem_funcs);
  result &= LoadDllProc(udev_queue_get_queue_is_empty_, udev_handle_, "udev_queue_get_queue_is_empty", problem_funcs);
  result &= LoadDllProc(udev_queue_get_seqnum_is_finished_, udev_handle_, "udev_queue_get_seqnum_is_finished", problem_funcs);
  result &= LoadDllProc(udev_queue_get_seqnum_sequence_is_finished_, udev_handle_, "udev_queue_get_seqnum_sequence_is_finished", problem_funcs);
  result &= LoadDllProc(udev_queue_get_fd_, udev_handle_, "udev_queue_get_fd", problem_funcs);
  result &= LoadDllProc(udev_queue_flush_, udev_handle_, "udev_queue_flush", problem_funcs);
  result &= LoadDllProc(udev_queue_get_queued_list_entry_, udev_handle_, "udev_queue_get_queued_list_entry", problem_funcs);
  result &= LoadDllProc(udev_hwdb_new_, udev_handle_, "udev_hwdb_new", problem_funcs);
  result &= LoadDllProc(udev_hwdb_ref_, udev_handle_, "udev_hwdb_ref", problem_funcs);
  result &= LoadDllProc(udev_hwdb_unref_, udev_handle_, "udev_hwdb_unref", problem_funcs);
  result &= LoadDllProc(udev_hwdb_get_properties_list_entry_, udev_handle_, "udev_hwdb_get_properties_list_entry", problem_funcs);
  result &= LoadDllProc(udev_util_encode_string_, udev_handle_, "udev_util_encode_string", problem_funcs);

  if (!result) {
    std::cerr << "LIBUDEV load problem: some functions were not loaded: " << problem_funcs.str() << std::endl;
  }

  return result;
}

struct IUdevModuleProvider::udev * UdevModuleProvider::udev_ref(struct udev *udev) {
  Load();
  return udev_ref_(udev);
}

struct IUdevModuleProvider::udev * UdevModuleProvider::udev_unref(struct udev *udev) {
  Load();
  return udev_unref_(udev);
}

struct IUdevModuleProvider::udev * UdevModuleProvider::udev_new(void) {
  Load();
  return udev_new_();
}

void UdevModuleProvider::udev_set_log_fn(struct udev *udev,
                            void (*log_fn)(struct udev *udev,
                                           int priority, const char *file, int line, const char *fn,
                                           const char *format, va_list args)) {
  Load();
  return udev_set_log_fn_(udev, log_fn);
}

int UdevModuleProvider::udev_get_log_priority(struct udev *udev) {
  Load();
  return udev_get_log_priority_(udev);
}

void UdevModuleProvider::udev_set_log_priority(struct udev *udev, int priority) {
  Load();
  return udev_set_log_priority_(udev, priority);
}

void * UdevModuleProvider::udev_get_userdata(struct udev *udev) {
  Load();
  return udev_get_userdata_(udev);
}

void UdevModuleProvider::udev_set_userdata(struct udev *udev, void *userdata){
  Load();
  return udev_set_userdata_(udev, userdata);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_list_entry_get_next(struct udev_list_entry *list_entry){
  Load();
  return udev_list_entry_get_next_(list_entry);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_list_entry_get_by_name(struct udev_list_entry *list_entry, const char *name) {
  Load();
  return udev_list_entry_get_by_name_(list_entry, name);
}

const char * UdevModuleProvider::udev_list_entry_get_name(struct udev_list_entry *list_entry) {
  Load();
  return udev_list_entry_get_name_(list_entry);
}
const char * UdevModuleProvider::udev_list_entry_get_value(struct udev_list_entry *list_entry) {
  Load();
  return udev_list_entry_get_value_(list_entry);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_ref(struct udev_device *udev_device) {
  Load();
  return udev_device_ref_(udev_device);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_unref(struct udev_device *udev_device){
  Load();
  return udev_device_unref_(udev_device);
}

struct IUdevModuleProvider::udev * UdevModuleProvider::udev_device_get_udev(struct udev_device *udev_device) {
  Load();
  return udev_device_get_udev_(udev_device);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_new_from_syspath(struct udev *udev, const char *syspath) {
  Load();
  return udev_device_new_from_syspath_(udev,syspath);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_new_from_devnum(struct udev *udev, char type, dev_t devnum) {
  Load();
  return udev_device_new_from_devnum_(udev, type, devnum);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_new_from_subsystem_sysname(struct udev *udev, const char *subsystem, const char *sysname) {
  Load();
  return udev_device_new_from_subsystem_sysname_(udev, subsystem, sysname);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_new_from_device_id(struct udev *udev, const char *id) {
  Load();
  return udev_device_new_from_device_id_(udev, id);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_new_from_environment(struct udev *udev) {
  Load();
  return udev_device_new_from_environment_(udev);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_get_parent(struct udev_device *udev_device){
  Load();
  return udev_device_get_parent_(udev_device);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_device_get_parent_with_subsystem_devtype(struct udev_device *udev_device,
                                                                  const char *subsystem, const char *devtype){
  Load();
  return udev_device_get_parent_with_subsystem_devtype_(udev_device, subsystem, devtype);
}

const char * UdevModuleProvider::udev_device_get_devpath(struct udev_device *udev_device){
  Load();
  return udev_device_get_devpath_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_subsystem(struct udev_device *udev_device){
  Load();
  return udev_device_get_subsystem_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_devtype(struct udev_device *udev_device){
  Load();
  return udev_device_get_devtype_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_syspath(struct udev_device *udev_device){
  Load();
  return udev_device_get_syspath_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_sysname(struct udev_device *udev_device){
  Load();
  return udev_device_get_sysname_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_sysnum(struct udev_device *udev_device){
  Load();
  return udev_device_get_sysnum_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_devnode(struct udev_device *udev_device){
  Load();
  return udev_device_get_devnode_(udev_device);
}

int  UdevModuleProvider::udev_device_get_is_initialized(struct udev_device *udev_device){
  Load();
  return udev_device_get_is_initialized_(udev_device);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_device_get_devlinks_list_entry(struct udev_device *udev_device){
  Load();
  return udev_device_get_devlinks_list_entry_(udev_device);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_device_get_properties_list_entry(struct udev_device *udev_device){
  Load();
  return udev_device_get_properties_list_entry_(udev_device);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_device_get_tags_list_entry(struct udev_device *udev_device){
  Load();
  return udev_device_get_tags_list_entry_(udev_device);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_device_get_current_tags_list_entry(struct udev_device *udev_device){
  Load();
  return udev_device_get_current_tags_list_entry_(udev_device);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_device_get_sysattr_list_entry(struct udev_device *udev_device){
  Load();
  return udev_device_get_sysattr_list_entry_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_property_value(struct udev_device *udev_device, const char *key){
  Load();
  return udev_device_get_property_value_(udev_device, key);
}

const char * UdevModuleProvider::udev_device_get_driver(struct udev_device *udev_device){
  Load();
  return udev_device_get_driver_(udev_device);
}

unsigned long int  UdevModuleProvider::udev_device_get_devnum(struct udev_device *udev_device){
  Load();
  return udev_device_get_devnum_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_action(struct udev_device *udev_device){
  Load();
  return udev_device_get_action_(udev_device);
}

unsigned long long int  UdevModuleProvider::udev_device_get_seqnum(struct udev_device *udev_device){
  Load();
  return udev_device_get_seqnum_(udev_device);
}

unsigned long long int  UdevModuleProvider::udev_device_get_usec_since_initialized(struct udev_device *udev_device){
  Load();
  return udev_device_get_usec_since_initialized_(udev_device);
}

const char * UdevModuleProvider::udev_device_get_sysattr_value(struct udev_device *udev_device, const char *sysattr){
  Load();
  return udev_device_get_sysattr_value_(udev_device, sysattr);
}

int  UdevModuleProvider::udev_device_set_sysattr_value(struct udev_device *udev_device, const char *sysattr, const char *value){
  Load();
  return udev_device_set_sysattr_value_(udev_device, sysattr, value);
}

int  UdevModuleProvider::udev_device_has_tag(struct udev_device *udev_device, const char *tag){
  Load();
  return udev_device_has_tag_(udev_device, tag);
}

int  UdevModuleProvider::udev_device_has_current_tag(struct udev_device *udev_device, const char *tag){
  Load();
  return udev_device_has_current_tag_(udev_device, tag);
}

struct IUdevModuleProvider::udev_monitor * UdevModuleProvider::udev_monitor_ref(struct udev_monitor *udev_monitor){
  Load();
  return udev_monitor_ref_(udev_monitor);
}

struct IUdevModuleProvider::udev_monitor * UdevModuleProvider::udev_monitor_unref(struct udev_monitor *udev_monitor){
  Load();
  return udev_monitor_unref_(udev_monitor);
}

struct IUdevModuleProvider::udev * UdevModuleProvider::udev_monitor_get_udev(struct udev_monitor *udev_monitor){
  Load();
  return udev_monitor_get_udev_(udev_monitor);
}

struct IUdevModuleProvider::udev_monitor * UdevModuleProvider::udev_monitor_new_from_netlink(struct udev *udev, const char *name){
  Load();
  return udev_monitor_new_from_netlink_(udev, name);
}

int  UdevModuleProvider::udev_monitor_enable_receiving(struct udev_monitor *udev_monitor){
  Load();
  return udev_monitor_enable_receiving_(udev_monitor);
}

int  UdevModuleProvider::udev_monitor_set_receive_buffer_size(struct udev_monitor *udev_monitor, int size){
  Load();
  return udev_monitor_set_receive_buffer_size_(udev_monitor, size);
}

int  UdevModuleProvider::udev_monitor_get_fd(struct udev_monitor *udev_monitor){
  Load();
  return udev_monitor_get_fd_(udev_monitor);
}

struct IUdevModuleProvider::udev_device * UdevModuleProvider::udev_monitor_receive_device(struct udev_monitor *udev_monitor){
  Load();
  return udev_monitor_receive_device_(udev_monitor);
}

int  UdevModuleProvider::udev_monitor_filter_add_match_subsystem_devtype(struct udev_monitor *udev_monitor,
                                                                         const char *subsystem, const char *devtype){
  Load();
  return udev_monitor_filter_add_match_subsystem_devtype_(udev_monitor, subsystem, devtype);
}

int  UdevModuleProvider::udev_monitor_filter_add_match_tag(struct udev_monitor *udev_monitor, const char *tag){
  Load();
  return udev_monitor_filter_add_match_tag_(udev_monitor, tag);
}

int  UdevModuleProvider::udev_monitor_filter_update(struct udev_monitor *udev_monitor){
  Load();
  return udev_monitor_filter_update_(udev_monitor);
}

int  UdevModuleProvider::udev_monitor_filter_remove(struct udev_monitor *udev_monitor){
  Load();
  return udev_monitor_filter_remove_(udev_monitor);
}

struct IUdevModuleProvider::udev_enumerate * UdevModuleProvider::udev_enumerate_ref(struct udev_enumerate *udev_enumerate){
  Load();
  return udev_enumerate_ref_(udev_enumerate);
}

struct IUdevModuleProvider::udev_enumerate * UdevModuleProvider::udev_enumerate_unref(struct udev_enumerate *udev_enumerate){
  Load();
  return udev_enumerate_unref_(udev_enumerate);
}

struct IUdevModuleProvider::udev * UdevModuleProvider::udev_enumerate_get_udev(struct udev_enumerate *udev_enumerate){
  Load();
  return udev_enumerate_get_udev_(udev_enumerate);
}

struct IUdevModuleProvider::udev_enumerate * UdevModuleProvider::udev_enumerate_new(struct udev *udev){
  Load();
  return udev_enumerate_new_(udev);
}

int  UdevModuleProvider::udev_enumerate_add_match_subsystem(struct udev_enumerate *udev_enumerate, const char *subsystem){
  Load();
  return udev_enumerate_add_match_subsystem_(udev_enumerate, subsystem);
}

int  UdevModuleProvider::udev_enumerate_add_nomatch_subsystem(struct udev_enumerate *udev_enumerate, const char *subsystem){
  Load();
  return udev_enumerate_add_nomatch_subsystem_(udev_enumerate, subsystem);
}

int  UdevModuleProvider::udev_enumerate_add_match_sysattr(struct udev_enumerate *udev_enumerate, const char *sysattr, const char *value){
  Load();
  return udev_enumerate_add_match_sysattr_(udev_enumerate, sysattr, value);
}

int  UdevModuleProvider::udev_enumerate_add_nomatch_sysattr(struct udev_enumerate *udev_enumerate, const char *sysattr, const char *value){
  Load();
  return udev_enumerate_add_nomatch_sysattr_(udev_enumerate, sysattr, value);
}

int  UdevModuleProvider::udev_enumerate_add_match_property(struct udev_enumerate *udev_enumerate, const char *property, const char *value){
  Load();
  return udev_enumerate_add_match_property_(udev_enumerate, property, value);

}
int  UdevModuleProvider::udev_enumerate_add_match_sysname(struct udev_enumerate *udev_enumerate, const char *sysname){
  Load();
  return udev_enumerate_add_match_sysname_(udev_enumerate, sysname);
}

int UdevModuleProvider::udev_enumerate_add_match_tag(struct udev_enumerate *udev_enumerate, const char *tag){
  Load();
  return udev_enumerate_add_match_tag_(udev_enumerate, tag);
}

int  UdevModuleProvider::udev_enumerate_add_match_parent(struct udev_enumerate *udev_enumerate, struct udev_device *parent){
  Load();
  return udev_enumerate_add_match_parent_(udev_enumerate, parent);
}

int  UdevModuleProvider::udev_enumerate_add_match_is_initialized(struct udev_enumerate *udev_enumerate){
  Load();
  return udev_enumerate_add_match_is_initialized_(udev_enumerate);
}

int  UdevModuleProvider::udev_enumerate_add_syspath(struct udev_enumerate *udev_enumerate, const char *syspath){
  Load();
  return udev_enumerate_add_syspath_(udev_enumerate, syspath);
}

int  UdevModuleProvider::udev_enumerate_scan_devices(struct udev_enumerate *udev_enumerate){
  Load();
  return udev_enumerate_scan_devices_(udev_enumerate);
}

int  UdevModuleProvider::udev_enumerate_scan_subsystems(struct udev_enumerate *udev_enumerate){
  Load();
  return udev_enumerate_scan_subsystems_(udev_enumerate);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_enumerate_get_list_entry(struct udev_enumerate *udev_enumerate){
  Load();
  return udev_enumerate_get_list_entry_(udev_enumerate);
}

struct IUdevModuleProvider::udev_queue * UdevModuleProvider::udev_queue_ref(struct udev_queue *udev_queue){
  Load();
  return udev_queue_ref_(udev_queue);
}

struct IUdevModuleProvider::udev_queue * UdevModuleProvider::udev_queue_unref(struct udev_queue *udev_queue){
  Load();
  return udev_queue_unref_(udev_queue);
}

struct IUdevModuleProvider::udev * UdevModuleProvider::udev_queue_get_udev(struct udev_queue *udev_queue){
  Load();
  return udev_queue_get_udev_(udev_queue);
}

struct IUdevModuleProvider::udev_queue * UdevModuleProvider::udev_queue_new(struct udev *udev){
  Load();
  return udev_queue_new_(udev);
}

unsigned long long int  UdevModuleProvider::udev_queue_get_kernel_seqnum(struct udev_queue *udev_queue){
  Load();
  return udev_queue_get_kernel_seqnum_(udev_queue);
}

unsigned long long int  UdevModuleProvider::udev_queue_get_udev_seqnum(struct udev_queue *udev_queue){
  Load();
  return udev_queue_get_udev_seqnum_(udev_queue);
}

int  UdevModuleProvider::udev_queue_get_udev_is_active(struct udev_queue *udev_queue){
  Load();
  return  udev_queue_get_udev_is_active_(udev_queue);
}

int  UdevModuleProvider::udev_queue_get_queue_is_empty(struct udev_queue *udev_queue){
  Load();
  return udev_queue_get_queue_is_empty_(udev_queue);
}

int  UdevModuleProvider::udev_queue_get_seqnum_is_finished(struct udev_queue *udev_queue, unsigned long long int seqnum){
  Load();
  return udev_queue_get_seqnum_is_finished_(udev_queue, seqnum);
}
int  UdevModuleProvider::udev_queue_get_seqnum_sequence_is_finished(struct udev_queue *udev_queue,
                                                                    unsigned long long int start, unsigned long long int end){
  Load();
  return udev_queue_get_seqnum_sequence_is_finished_(udev_queue, start, end);
}
int  UdevModuleProvider::udev_queue_get_fd(struct udev_queue *udev_queue){
  Load();
  return udev_queue_get_fd_(udev_queue);
}

int  UdevModuleProvider::udev_queue_flush(struct udev_queue *udev_queue){
  Load();
  return udev_queue_flush_(udev_queue);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_queue_get_queued_list_entry(struct udev_queue *udev_queue){
  Load();
  return udev_queue_get_queued_list_entry_(udev_queue);
}

struct IUdevModuleProvider::udev_hwdb * UdevModuleProvider::udev_hwdb_new(struct udev *udev){
  Load();
  return udev_hwdb_new_(udev);
}

struct IUdevModuleProvider::udev_hwdb * UdevModuleProvider::udev_hwdb_ref(struct udev_hwdb *hwdb){
  Load();
  return udev_hwdb_ref_(hwdb);
}

struct IUdevModuleProvider::udev_hwdb * UdevModuleProvider::udev_hwdb_unref(struct udev_hwdb *hwdb){
  Load();
  return udev_hwdb_unref_(hwdb);
}

struct IUdevModuleProvider::udev_list_entry * UdevModuleProvider::udev_hwdb_get_properties_list_entry(struct udev_hwdb *hwdb, const char *modalias, unsigned flags){
  Load();
  return udev_hwdb_get_properties_list_entry_(hwdb, modalias, flags);
}

int  UdevModuleProvider::udev_util_encode_string(const char *str, char *str_enc, size_t len){
  Load();
  return udev_util_encode_string_(str, str_enc, len);
}
