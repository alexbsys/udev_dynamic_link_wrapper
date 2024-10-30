#ifndef UDEV_MODULE_PROVIDER_H
#define UDEV_MODULE_PROVIDER_H

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <memory>

#include "i_dynamic_modules_loader.h"


#ifndef udev_list_entry_foreach
#define udev_list_entry_foreach(list_entry, first_entry) \
          for (list_entry = first_entry; \
               list_entry; \
               list_entry = udev_list_entry_get_next(list_entry))
#endif //udev_list_entry_foreach

struct IUdevModuleProvider {
  struct udev;
  struct udev_list_entry;
  struct udev_device;
  struct udev_monitor;

  struct udev_enumerate;
  struct udev_queue;
  struct udev_hwdb;

  virtual ~IUdevModuleProvider() = default;

  virtual bool Load() = 0;
  virtual bool IsLoaded() const = 0;

  virtual struct udev *udev_ref(struct udev *udev) = 0;
  virtual struct udev *udev_unref(struct udev *udev) = 0;
  virtual struct udev *udev_new(void) = 0;
  virtual void udev_set_log_fn(struct udev *udev,
                              void (*log_fn)(struct udev *udev,
                                             int priority, const char *file, int line, const char *fn,
                                             const char *format, va_list args)) = 0;
  virtual int udev_get_log_priority(struct udev *udev) = 0;
  virtual void udev_set_log_priority(struct udev *udev, int priority) = 0;
  virtual void *udev_get_userdata(struct udev *udev) = 0;
  virtual void udev_set_userdata(struct udev *udev, void *userdata) = 0;

  virtual struct udev_list_entry *udev_list_entry_get_next(struct udev_list_entry *list_entry) = 0;
  virtual struct udev_list_entry *udev_list_entry_get_by_name(struct udev_list_entry *list_entry, const char *name) = 0;
  virtual const char *udev_list_entry_get_name(struct udev_list_entry *list_entry) = 0;
  virtual const char *udev_list_entry_get_value(struct udev_list_entry *list_entry) = 0;

  virtual struct udev_device *udev_device_ref(struct udev_device *udev_device) = 0;
  virtual struct udev_device *udev_device_unref(struct udev_device *udev_device) = 0;
  virtual struct udev *udev_device_get_udev(struct udev_device *udev_device) = 0;
  virtual struct udev_device *udev_device_new_from_syspath(struct udev *udev, const char *syspath) = 0;
  virtual struct udev_device *udev_device_new_from_devnum(struct udev *udev, char type, dev_t devnum) = 0;
  virtual struct udev_device *udev_device_new_from_subsystem_sysname(struct udev *udev, const char *subsystem, const char *sysname) = 0;
  virtual struct udev_device *udev_device_new_from_device_id(struct udev *udev, const char *id) = 0;
  virtual struct udev_device *udev_device_new_from_environment(struct udev *udev) = 0;
  virtual struct udev_device *udev_device_get_parent(struct udev_device *udev_device) = 0;
  virtual struct udev_device *udev_device_get_parent_with_subsystem_devtype(struct udev_device *udev_device,
                                                                    const char *subsystem, const char *devtype) = 0;
  virtual const char *udev_device_get_devpath(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_subsystem(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_devtype(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_syspath(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_sysname(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_sysnum(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_devnode(struct udev_device *udev_device) = 0;
  virtual int udev_device_get_is_initialized(struct udev_device *udev_device) = 0;
  virtual struct udev_list_entry *udev_device_get_devlinks_list_entry(struct udev_device *udev_device) = 0;
  virtual struct udev_list_entry *udev_device_get_properties_list_entry(struct udev_device *udev_device) = 0;
  virtual struct udev_list_entry *udev_device_get_tags_list_entry(struct udev_device *udev_device) = 0;
  virtual struct udev_list_entry *udev_device_get_current_tags_list_entry(struct udev_device *udev_device) = 0;
  virtual struct udev_list_entry *udev_device_get_sysattr_list_entry(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_property_value(struct udev_device *udev_device, const char *key) = 0;
  virtual const char *udev_device_get_driver(struct udev_device *udev_device) = 0;
  virtual unsigned long int udev_device_get_devnum(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_action(struct udev_device *udev_device) = 0;
  virtual unsigned long long int udev_device_get_seqnum(struct udev_device *udev_device) = 0;
  virtual unsigned long long int udev_device_get_usec_since_initialized(struct udev_device *udev_device) = 0;
  virtual const char *udev_device_get_sysattr_value(struct udev_device *udev_device, const char *sysattr) = 0;
  virtual int udev_device_set_sysattr_value(struct udev_device *udev_device, const char *sysattr, const char *value) = 0;
  virtual int udev_device_has_tag(struct udev_device *udev_device, const char *tag) = 0;
  virtual int udev_device_has_current_tag(struct udev_device *udev_device, const char *tag) = 0;

  virtual struct udev_monitor *udev_monitor_ref(struct udev_monitor *udev_monitor) = 0;
  virtual struct udev_monitor *udev_monitor_unref(struct udev_monitor *udev_monitor) = 0;
  virtual struct udev *udev_monitor_get_udev(struct udev_monitor *udev_monitor) = 0;
  virtual struct udev_monitor *udev_monitor_new_from_netlink(struct udev *udev, const char *name) = 0;
  virtual int udev_monitor_enable_receiving(struct udev_monitor *udev_monitor) = 0;
  virtual int udev_monitor_set_receive_buffer_size(struct udev_monitor *udev_monitor, int size) = 0;
  virtual int udev_monitor_get_fd(struct udev_monitor *udev_monitor) = 0;
  virtual struct udev_device *udev_monitor_receive_device(struct udev_monitor *udev_monitor) = 0;
  virtual int udev_monitor_filter_add_match_subsystem_devtype(struct udev_monitor *udev_monitor,
                                                      const char *subsystem, const char *devtype) = 0;
  virtual int udev_monitor_filter_add_match_tag(struct udev_monitor *udev_monitor, const char *tag) = 0;
  virtual int udev_monitor_filter_update(struct udev_monitor *udev_monitor) = 0;
  virtual int udev_monitor_filter_remove(struct udev_monitor *udev_monitor) = 0;

  virtual struct udev_enumerate *udev_enumerate_ref(struct udev_enumerate *udev_enumerate) = 0;
  virtual struct udev_enumerate *udev_enumerate_unref(struct udev_enumerate *udev_enumerate) = 0;
  virtual struct udev *udev_enumerate_get_udev(struct udev_enumerate *udev_enumerate) = 0;
  virtual struct udev_enumerate *udev_enumerate_new(struct udev *udev) = 0;
  virtual int udev_enumerate_add_match_subsystem(struct udev_enumerate *udev_enumerate, const char *subsystem) = 0;
  virtual int udev_enumerate_add_nomatch_subsystem(struct udev_enumerate *udev_enumerate, const char *subsystem) = 0;
  virtual int udev_enumerate_add_match_sysattr(struct udev_enumerate *udev_enumerate, const char *sysattr, const char *value) = 0;
  virtual int udev_enumerate_add_nomatch_sysattr(struct udev_enumerate *udev_enumerate, const char *sysattr, const char *value) = 0;
  virtual int udev_enumerate_add_match_property(struct udev_enumerate *udev_enumerate, const char *property, const char *value) = 0;
  virtual int udev_enumerate_add_match_sysname(struct udev_enumerate *udev_enumerate, const char *sysname) = 0;
  virtual int udev_enumerate_add_match_tag(struct udev_enumerate *udev_enumerate, const char *tag) = 0;
  virtual int udev_enumerate_add_match_parent(struct udev_enumerate *udev_enumerate, struct udev_device *parent) = 0;
  virtual int udev_enumerate_add_match_is_initialized(struct udev_enumerate *udev_enumerate) = 0;
  virtual int udev_enumerate_add_syspath(struct udev_enumerate *udev_enumerate, const char *syspath) = 0;
  virtual int udev_enumerate_scan_devices(struct udev_enumerate *udev_enumerate) = 0;
  virtual int udev_enumerate_scan_subsystems(struct udev_enumerate *udev_enumerate) = 0;
  virtual struct udev_list_entry *udev_enumerate_get_list_entry(struct udev_enumerate *udev_enumerate) = 0;

  virtual struct udev_queue *udev_queue_ref(struct udev_queue *udev_queue) = 0;
  virtual struct udev_queue *udev_queue_unref(struct udev_queue *udev_queue) = 0;
  virtual struct udev *udev_queue_get_udev(struct udev_queue *udev_queue) = 0;
  virtual struct udev_queue *udev_queue_new(struct udev *udev) = 0;
  virtual unsigned long long int udev_queue_get_kernel_seqnum(struct udev_queue *udev_queue) = 0;
  virtual unsigned long long int udev_queue_get_udev_seqnum(struct udev_queue *udev_queue) = 0;
  virtual int udev_queue_get_udev_is_active(struct udev_queue *udev_queue) = 0;
  virtual int udev_queue_get_queue_is_empty(struct udev_queue *udev_queue) = 0;
  virtual int udev_queue_get_seqnum_is_finished(struct udev_queue *udev_queue, unsigned long long int seqnum) = 0;
  virtual int udev_queue_get_seqnum_sequence_is_finished(struct udev_queue *udev_queue,
                                                 unsigned long long int start, unsigned long long int end) = 0;
  virtual int udev_queue_get_fd(struct udev_queue *udev_queue) = 0;
  virtual int udev_queue_flush(struct udev_queue *udev_queue) = 0;
  virtual struct udev_list_entry *udev_queue_get_queued_list_entry(struct udev_queue *udev_queue) = 0;
  virtual struct udev_hwdb *udev_hwdb_new(struct udev *udev) = 0;
  virtual struct udev_hwdb *udev_hwdb_ref(struct udev_hwdb *hwdb) = 0;
  virtual struct udev_hwdb *udev_hwdb_unref(struct udev_hwdb *hwdb) = 0;
  virtual struct udev_list_entry *udev_hwdb_get_properties_list_entry(struct udev_hwdb *hwdb, const char *modalias, unsigned flags) = 0;
  virtual int udev_util_encode_string(const char *str, char *str_enc, size_t len) = 0;

};

class UdevModuleProvider : public virtual IUdevModuleProvider
{
public:
  UdevModuleProvider(std::shared_ptr<IDynamicModulesLoader> dynamic_modules_loader, bool unload_on_destroy = true);
  virtual ~UdevModuleProvider();

  bool Load() override;
  bool IsLoaded() const override;

  struct udev *udev_ref(struct udev *udev) override;
  struct udev *udev_unref(struct udev *udev) override;
  struct udev *udev_new(void) override;
  void udev_set_log_fn(struct udev *udev,
                              void (*log_fn)(struct udev *udev,
                                             int priority, const char *file, int line, const char *fn,
                                             const char *format, va_list args)) override;
  int udev_get_log_priority(struct udev *udev) override;
  void udev_set_log_priority(struct udev *udev, int priority) override;
  void *udev_get_userdata(struct udev *udev) override;
  void udev_set_userdata(struct udev *udev, void *userdata) override;

  struct udev_list_entry *udev_list_entry_get_next(struct udev_list_entry *list_entry) override;
  struct udev_list_entry *udev_list_entry_get_by_name(struct udev_list_entry *list_entry, const char *name) override;
  const char *udev_list_entry_get_name(struct udev_list_entry *list_entry) override;
  const char *udev_list_entry_get_value(struct udev_list_entry *list_entry) override;

  struct udev_device *udev_device_ref(struct udev_device *udev_device) override;
  struct udev_device *udev_device_unref(struct udev_device *udev_device) override;
  struct udev *udev_device_get_udev(struct udev_device *udev_device) override;
  struct udev_device *udev_device_new_from_syspath(struct udev *udev, const char *syspath) override;
  struct udev_device *udev_device_new_from_devnum(struct udev *udev, char type, dev_t devnum) override;
  struct udev_device *udev_device_new_from_subsystem_sysname(struct udev *udev, const char *subsystem, const char *sysname) override;
  struct udev_device *udev_device_new_from_device_id(struct udev *udev, const char *id) override;
  struct udev_device *udev_device_new_from_environment(struct udev *udev) override;
  struct udev_device *udev_device_get_parent(struct udev_device *udev_device) override;
  struct udev_device *udev_device_get_parent_with_subsystem_devtype(struct udev_device *udev_device,
                                                                    const char *subsystem, const char *devtype) override;
  const char *udev_device_get_devpath(struct udev_device *udev_device) override;
  const char *udev_device_get_subsystem(struct udev_device *udev_device) override;
  const char *udev_device_get_devtype(struct udev_device *udev_device) override;
  const char *udev_device_get_syspath(struct udev_device *udev_device) override;
  const char *udev_device_get_sysname(struct udev_device *udev_device) override;
  const char *udev_device_get_sysnum(struct udev_device *udev_device) override;
  const char *udev_device_get_devnode(struct udev_device *udev_device) override;
  int udev_device_get_is_initialized(struct udev_device *udev_device) override;
  struct udev_list_entry *udev_device_get_devlinks_list_entry(struct udev_device *udev_device) override;
  struct udev_list_entry *udev_device_get_properties_list_entry(struct udev_device *udev_device) override;
  struct udev_list_entry *udev_device_get_tags_list_entry(struct udev_device *udev_device) override;
  struct udev_list_entry *udev_device_get_current_tags_list_entry(struct udev_device *udev_device) override;
  struct udev_list_entry *udev_device_get_sysattr_list_entry(struct udev_device *udev_device) override;
  const char *udev_device_get_property_value(struct udev_device *udev_device, const char *key) override;
  const char *udev_device_get_driver(struct udev_device *udev_device) override;
  unsigned long int udev_device_get_devnum(struct udev_device *udev_device) override;
  const char *udev_device_get_action(struct udev_device *udev_device) override;
  unsigned long long int udev_device_get_seqnum(struct udev_device *udev_device) override;
  unsigned long long int udev_device_get_usec_since_initialized(struct udev_device *udev_device) override;
  const char *udev_device_get_sysattr_value(struct udev_device *udev_device, const char *sysattr) override;
  int udev_device_set_sysattr_value(struct udev_device *udev_device, const char *sysattr, const char *value) override;
  int udev_device_has_tag(struct udev_device *udev_device, const char *tag) override;
  int udev_device_has_current_tag(struct udev_device *udev_device, const char *tag) override;

  struct udev_monitor *udev_monitor_ref(struct udev_monitor *udev_monitor) override;
  struct udev_monitor *udev_monitor_unref(struct udev_monitor *udev_monitor) override;
  struct udev *udev_monitor_get_udev(struct udev_monitor *udev_monitor) override;
  struct udev_monitor *udev_monitor_new_from_netlink(struct udev *udev, const char *name) override;
  int udev_monitor_enable_receiving(struct udev_monitor *udev_monitor) override;
  int udev_monitor_set_receive_buffer_size(struct udev_monitor *udev_monitor, int size) override;
  int udev_monitor_get_fd(struct udev_monitor *udev_monitor) override;
  struct udev_device *udev_monitor_receive_device(struct udev_monitor *udev_monitor) override;
  int udev_monitor_filter_add_match_subsystem_devtype(struct udev_monitor *udev_monitor,
                                                      const char *subsystem, const char *devtype) override;
  int udev_monitor_filter_add_match_tag(struct udev_monitor *udev_monitor, const char *tag) override;
  int udev_monitor_filter_update(struct udev_monitor *udev_monitor) override;
  int udev_monitor_filter_remove(struct udev_monitor *udev_monitor) override;

  struct udev_enumerate *udev_enumerate_ref(struct udev_enumerate *udev_enumerate);
  struct udev_enumerate *udev_enumerate_unref(struct udev_enumerate *udev_enumerate);
  struct udev *udev_enumerate_get_udev(struct udev_enumerate *udev_enumerate);
  struct udev_enumerate *udev_enumerate_new(struct udev *udev) override;
  int udev_enumerate_add_match_subsystem(struct udev_enumerate *udev_enumerate, const char *subsystem) override;
  int udev_enumerate_add_nomatch_subsystem(struct udev_enumerate *udev_enumerate, const char *subsystem) override;
  int udev_enumerate_add_match_sysattr(struct udev_enumerate *udev_enumerate, const char *sysattr, const char *value) override;
  int udev_enumerate_add_nomatch_sysattr(struct udev_enumerate *udev_enumerate, const char *sysattr, const char *value) override;
  int udev_enumerate_add_match_property(struct udev_enumerate *udev_enumerate, const char *property, const char *value) override;
  int udev_enumerate_add_match_sysname(struct udev_enumerate *udev_enumerate, const char *sysname) override;
  int udev_enumerate_add_match_tag(struct udev_enumerate *udev_enumerate, const char *tag) override;
  int udev_enumerate_add_match_parent(struct udev_enumerate *udev_enumerate, struct udev_device *parent) override;
  int udev_enumerate_add_match_is_initialized(struct udev_enumerate *udev_enumerate) override;
  int udev_enumerate_add_syspath(struct udev_enumerate *udev_enumerate, const char *syspath) override;
  int udev_enumerate_scan_devices(struct udev_enumerate *udev_enumerate) override;
  int udev_enumerate_scan_subsystems(struct udev_enumerate *udev_enumerate) override;
  struct udev_list_entry *udev_enumerate_get_list_entry(struct udev_enumerate *udev_enumerate) override;

  struct udev_queue *udev_queue_ref(struct udev_queue *udev_queue) override;
  struct udev_queue *udev_queue_unref(struct udev_queue *udev_queue) override;
  struct udev *udev_queue_get_udev(struct udev_queue *udev_queue) override;
  struct udev_queue *udev_queue_new(struct udev *udev) override;
  unsigned long long int udev_queue_get_kernel_seqnum(struct udev_queue *udev_queue) override;
  unsigned long long int udev_queue_get_udev_seqnum(struct udev_queue *udev_queue) override;
  int udev_queue_get_udev_is_active(struct udev_queue *udev_queue) override;
  int udev_queue_get_queue_is_empty(struct udev_queue *udev_queue) override;
  int udev_queue_get_seqnum_is_finished(struct udev_queue *udev_queue, unsigned long long int seqnum) override;
  int udev_queue_get_seqnum_sequence_is_finished(struct udev_queue *udev_queue,
                                                 unsigned long long int start, unsigned long long int end) override;
  int udev_queue_get_fd(struct udev_queue *udev_queue) override;
  int udev_queue_flush(struct udev_queue *udev_queue) override;
  struct udev_list_entry *udev_queue_get_queued_list_entry(struct udev_queue *udev_queue) override;
  struct udev_hwdb *udev_hwdb_new(struct udev *udev) override;
  struct udev_hwdb *udev_hwdb_ref(struct udev_hwdb *hwdb) override;
  struct udev_hwdb *udev_hwdb_unref(struct udev_hwdb *hwdb) override;
  struct udev_list_entry *udev_hwdb_get_properties_list_entry(struct udev_hwdb *hwdb, const char *modalias, unsigned flags) override;
  int udev_util_encode_string(const char *str, char *str_enc, size_t len) override;


private:
  struct udev*(*udev_ref_)(struct udev *udev) = nullptr;
  struct udev*(*udev_unref_)(struct udev *udev) = nullptr;
  struct udev*(*udev_new_)(void) = nullptr;
  void (*udev_set_log_fn_)(struct udev *udev,
                              void (*log_fn)(struct udev *udev,
                                             int priority, const char *file, int line, const char *fn,
                                             const char *format, va_list args)) = nullptr;
  int (*udev_get_log_priority_)(struct udev *udev) = nullptr;
  void (*udev_set_log_priority_)(struct udev *udev, int priority) = nullptr;
  void*(*udev_get_userdata_)(struct udev *udev) = nullptr;
  void (*udev_set_userdata_)(struct udev *udev, void *userdata) = nullptr;

  struct udev_list_entry *(*udev_list_entry_get_next_)(struct udev_list_entry *list_entry) = nullptr;
  struct udev_list_entry *(*udev_list_entry_get_by_name_)(struct udev_list_entry *list_entry, const char *name) = nullptr;
  const char *(*udev_list_entry_get_name_)(struct udev_list_entry *list_entry) = nullptr;
  const char *(*udev_list_entry_get_value_)(struct udev_list_entry *list_entry) = nullptr;

  #define udev_list_entry_foreach(list_entry, first_entry) \
          for (list_entry = first_entry; \
               list_entry; \
               list_entry = udev_list_entry_get_next(list_entry))

  struct udev_device *(*udev_device_ref_)(struct udev_device *udev_device) = nullptr;
  struct udev_device *(*udev_device_unref_)(struct udev_device *udev_device) = nullptr;
  struct udev *(*udev_device_get_udev_)(struct udev_device *udev_device) = nullptr;
  struct udev_device *(*udev_device_new_from_syspath_)(struct udev *udev, const char *syspath) = nullptr;
  struct udev_device *(*udev_device_new_from_devnum_)(struct udev *udev, char type, dev_t devnum) = nullptr;
  struct udev_device *(*udev_device_new_from_subsystem_sysname_)(struct udev *udev, const char *subsystem, const char *sysname) = nullptr;
  struct udev_device *(*udev_device_new_from_device_id_)(struct udev *udev, const char *id) = nullptr;
  struct udev_device *(*udev_device_new_from_environment_)(struct udev *udev) = nullptr;
  struct udev_device *(*udev_device_get_parent_)(struct udev_device *udev_device) = nullptr;
  struct udev_device *(*udev_device_get_parent_with_subsystem_devtype_)(struct udev_device *udev_device,
                                                                    const char *subsystem, const char *devtype) = nullptr;
  const char *(*udev_device_get_devpath_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_subsystem_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_devtype_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_syspath_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_sysname_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_sysnum_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_devnode_)(struct udev_device *udev_device) = nullptr;
  int (*udev_device_get_is_initialized_)(struct udev_device *udev_device) = nullptr;
  struct udev_list_entry *(*udev_device_get_devlinks_list_entry_)(struct udev_device *udev_device) = nullptr;
  struct udev_list_entry *(*udev_device_get_properties_list_entry_)(struct udev_device *udev_device) = nullptr;
  struct udev_list_entry *(*udev_device_get_tags_list_entry_)(struct udev_device *udev_device) = nullptr;
  struct udev_list_entry *(*udev_device_get_current_tags_list_entry_)(struct udev_device *udev_device) = nullptr;
  struct udev_list_entry *(*udev_device_get_sysattr_list_entry_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_property_value_)(struct udev_device *udev_device, const char *key) = nullptr;
  const char *(*udev_device_get_driver_)(struct udev_device *udev_device) = nullptr;
  unsigned long int (*udev_device_get_devnum_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_action_)(struct udev_device *udev_device) = nullptr;
  unsigned long long int (*udev_device_get_seqnum_)(struct udev_device *udev_device) = nullptr;
  unsigned long long int (*udev_device_get_usec_since_initialized_)(struct udev_device *udev_device) = nullptr;
  const char *(*udev_device_get_sysattr_value_)(struct udev_device *udev_device, const char *sysattr) = nullptr;
  int (*udev_device_set_sysattr_value_)(struct udev_device *udev_device, const char *sysattr, const char *value) = nullptr;
  int (*udev_device_has_tag_)(struct udev_device *udev_device, const char *tag) = nullptr;
  int (*udev_device_has_current_tag_)(struct udev_device *udev_device, const char *tag) = nullptr;

  struct udev_monitor *(*udev_monitor_ref_)(struct udev_monitor *udev_monitor) = nullptr;
  struct udev_monitor *(*udev_monitor_unref_)(struct udev_monitor *udev_monitor) = nullptr;
  struct udev *(*udev_monitor_get_udev_)(struct udev_monitor *udev_monitor) = nullptr;
  struct udev_monitor *(*udev_monitor_new_from_netlink_)(struct udev *udev, const char *name) = nullptr;
  int (*udev_monitor_enable_receiving_)(struct udev_monitor *udev_monitor) = nullptr;
  int (*udev_monitor_set_receive_buffer_size_)(struct udev_monitor *udev_monitor, int size) = nullptr;
  int (*udev_monitor_get_fd_)(struct udev_monitor *udev_monitor) = nullptr;
  struct udev_device *(*udev_monitor_receive_device_)(struct udev_monitor *udev_monitor) = nullptr;
  int (*udev_monitor_filter_add_match_subsystem_devtype_)(struct udev_monitor *udev_monitor,
                                                      const char *subsystem, const char *devtype) = nullptr;
  int (*udev_monitor_filter_add_match_tag_)(struct udev_monitor *udev_monitor, const char *tag) = nullptr;
  int (*udev_monitor_filter_update_)(struct udev_monitor *udev_monitor) = nullptr;
  int (*udev_monitor_filter_remove_)(struct udev_monitor *udev_monitor) = nullptr;

  struct udev_enumerate *(*udev_enumerate_ref_)(struct udev_enumerate *udev_enumerate) = nullptr;
  struct udev_enumerate *(*udev_enumerate_unref_)(struct udev_enumerate *udev_enumerate) = nullptr;
  struct udev *(*udev_enumerate_get_udev_)(struct udev_enumerate *udev_enumerate) = nullptr;
  struct udev_enumerate *(*udev_enumerate_new_)(struct udev *udev) = nullptr;
  int (*udev_enumerate_add_match_subsystem_)(struct udev_enumerate *udev_enumerate, const char *subsystem) = nullptr;
  int (*udev_enumerate_add_nomatch_subsystem_)(struct udev_enumerate *udev_enumerate, const char *subsystem) = nullptr;
  int (*udev_enumerate_add_match_sysattr_)(struct udev_enumerate *udev_enumerate, const char *sysattr, const char *value) = nullptr;
  int (*udev_enumerate_add_nomatch_sysattr_)(struct udev_enumerate *udev_enumerate, const char *sysattr, const char *value) = nullptr;
  int (*udev_enumerate_add_match_property_)(struct udev_enumerate *udev_enumerate, const char *property, const char *value) = nullptr;
  int (*udev_enumerate_add_match_sysname_)(struct udev_enumerate *udev_enumerate, const char *sysname) = nullptr;
  int (*udev_enumerate_add_match_tag_)(struct udev_enumerate *udev_enumerate, const char *tag) = nullptr;
  int (*udev_enumerate_add_match_parent_)(struct udev_enumerate *udev_enumerate, struct udev_device *parent) = nullptr;
  int (*udev_enumerate_add_match_is_initialized_)(struct udev_enumerate *udev_enumerate) = nullptr;
  int (*udev_enumerate_add_syspath_)(struct udev_enumerate *udev_enumerate, const char *syspath) = nullptr;

  int (*udev_enumerate_scan_devices_)(struct udev_enumerate *udev_enumerate) = nullptr;
  int (*udev_enumerate_scan_subsystems_)(struct udev_enumerate *udev_enumerate) = nullptr;

  struct udev_list_entry *(*udev_enumerate_get_list_entry_)(struct udev_enumerate *udev_enumerate) = nullptr;

  struct udev_queue *(*udev_queue_ref_)(struct udev_queue *udev_queue) = nullptr;
  struct udev_queue *(*udev_queue_unref_)(struct udev_queue *udev_queue) = nullptr;
  struct udev *(*udev_queue_get_udev_)(struct udev_queue *udev_queue) = nullptr;
  struct udev_queue *(*udev_queue_new_)(struct udev *udev) = nullptr;
  unsigned long long int (*udev_queue_get_kernel_seqnum_)(struct udev_queue *udev_queue) = nullptr;
  unsigned long long int (*udev_queue_get_udev_seqnum_)(struct udev_queue *udev_queue) = nullptr;
  int (*udev_queue_get_udev_is_active_)(struct udev_queue *udev_queue) = nullptr;
  int (*udev_queue_get_queue_is_empty_)(struct udev_queue *udev_queue) = nullptr;
  int (*udev_queue_get_seqnum_is_finished_)(struct udev_queue *udev_queue, unsigned long long int seqnum) = nullptr;
  int (*udev_queue_get_seqnum_sequence_is_finished_)(struct udev_queue *udev_queue,
                                                 unsigned long long int start, unsigned long long int end) = nullptr;
  int (*udev_queue_get_fd_)(struct udev_queue *udev_queue) = nullptr;
  int (*udev_queue_flush_)(struct udev_queue *udev_queue) = nullptr;
  struct udev_list_entry *(*udev_queue_get_queued_list_entry_)(struct udev_queue *udev_queue) = nullptr;

  struct udev_hwdb *(*udev_hwdb_new_)(struct udev *udev) = nullptr;
  struct udev_hwdb *(*udev_hwdb_ref_)(struct udev_hwdb *hwdb) = nullptr;
  struct udev_hwdb *(*udev_hwdb_unref_)(struct udev_hwdb *hwdb) = nullptr;
  struct udev_list_entry *(*udev_hwdb_get_properties_list_entry_)(struct udev_hwdb *hwdb, const char *modalias, unsigned flags) = nullptr;

  int (*udev_util_encode_string_)(const char *str, char *str_enc, size_t len) = nullptr;

  void* udev_handle_ = nullptr;
  std::shared_ptr<IDynamicModulesLoader> mod_loader_;
  bool unload_on_destroy_;
};

#endif // UDEV_MODULE_PROVIDER_H
