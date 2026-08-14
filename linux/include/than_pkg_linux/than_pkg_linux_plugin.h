#ifndef FLUTTER_PLUGIN_THAN_PKG_LINUX_PLUGIN_H_
#define FLUTTER_PLUGIN_THAN_PKG_LINUX_PLUGIN_H_

#include <flutter_linux/flutter_linux.h>

#include <stdint.h>

G_BEGIN_DECLS

#ifdef FLUTTER_PLUGIN_IMPL
#define FLUTTER_PLUGIN_EXPORT __attribute__((visibility("default")))
#else
#define FLUTTER_PLUGIN_EXPORT
#endif

typedef struct _ThanPkgLinuxPlugin ThanPkgLinuxPlugin;

typedef struct {
  GObjectClass parent_class;
} ThanPkgLinuxPluginClass;

FLUTTER_PLUGIN_EXPORT GType than_pkg_linux_plugin_get_type();

FLUTTER_PLUGIN_EXPORT void
than_pkg_linux_plugin_register_with_registrar(FlPluginRegistrar *registrar);

G_END_DECLS

#endif