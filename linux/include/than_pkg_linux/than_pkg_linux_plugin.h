#ifndef FLUTTER_PLUGIN_THAN_PKG_LINUX_PLUGIN_H_
#define FLUTTER_PLUGIN_THAN_PKG_LINUX_PLUGIN_H_

#include <flutter_linux/flutter_linux.h>

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

FLUTTER_PLUGIN_EXPORT void than_pkg_linux_plugin_register_with_registrar(
    FlPluginRegistrar* registrar);

// --- Texture FFI Functions များ ---
// ၁။ Texture အသစ်ဆောက်ပြီး Texture ID (int64_t) ပြန်ပေးမယ့် function
FLUTTER_PLUGIN_EXPORT int64_t than_pkg_linux_plugin_ffi_create_texture();

// Texture ကို အပြီးဖျက်မယ့် function ကြေညာခြင်း
FLUTTER_PLUGIN_EXPORT void than_pkg_linux_plugin_ffi_dispose_texture(
    int64_t texture_id);

// ၂။ ရလာတဲ့ ID ထဲကို Pixel bufferPointer သွားချိတ်မယ့် function
FLUTTER_PLUGIN_EXPORT void than_pkg_linux_plugin_ffi_update_texture_pixels(
    int64_t texture_id, unsigned char* buffer, uint32_t width, uint32_t height);

G_END_DECLS

#endif  // FLUTTER_PLUGIN_THAN_PKG_LINUX_PLUGIN_H_
