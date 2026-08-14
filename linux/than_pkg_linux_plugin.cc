#include "include/than_pkg_linux/than_pkg_linux_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>

#include <cstdio>
#include <cstring>

#include "method_channel.h"
#include "than_globals.h"
#include "texture_handler.h"
#include "than_pkg_linux_plugin_private.h"


#include <flutter_linux/flutter_linux.h>

FlTextureRegistrar *g_texture_registrar = nullptr;
GtkWidget *g_toplevel_window = nullptr;

#define THAN_PKG_LINUX_PLUGIN(obj)                                             \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), than_pkg_linux_plugin_get_type(),         \
                              ThanPkgLinuxPlugin))

struct _ThanPkgLinuxPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(ThanPkgLinuxPlugin, than_pkg_linux_plugin, g_object_get_type())

static void than_pkg_linux_plugin_dispose(GObject *object) {
  G_OBJECT_CLASS(than_pkg_linux_plugin_parent_class)->dispose(object);
}

static void than_pkg_linux_plugin_class_init(ThanPkgLinuxPluginClass *klass) {
  G_OBJECT_CLASS(klass)->dispose = than_pkg_linux_plugin_dispose;
}

static void than_pkg_linux_plugin_init(ThanPkgLinuxPlugin *self) {}

// plugin register လုပ်တဲ့ နေရာ
void than_pkg_linux_plugin_register_with_registrar(
    FlPluginRegistrar *registrar) {

  g_texture_registrar = fl_plugin_registrar_get_texture_registrar(registrar);

  FlView *view = fl_plugin_registrar_get_view(registrar);

  if (view != nullptr) {
    g_toplevel_window = gtk_widget_get_toplevel(GTK_WIDGET(view));
  }

  register_method_channel(registrar);
}
