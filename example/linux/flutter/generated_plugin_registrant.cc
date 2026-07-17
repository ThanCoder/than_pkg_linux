//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <than_pkg_linux/than_pkg_linux_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) than_pkg_linux_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "ThanPkgLinuxPlugin");
  than_pkg_linux_plugin_register_with_registrar(than_pkg_linux_registrar);
}
