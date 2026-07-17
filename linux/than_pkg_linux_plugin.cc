#include "include/than_pkg_linux/than_pkg_linux_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>
#include <map>
#include <mutex>

#include "than_pkg_linux_plugin_private.h"

FlTextureRegistrar* g_texture_registrar = nullptr;
GtkWidget* g_toplevel_window = nullptr;

#define THAN_PKG_LINUX_PLUGIN(obj)                                     \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), than_pkg_linux_plugin_get_type(), \
                              ThanPkgLinuxPlugin))

struct _ThanPkgLinuxPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(ThanPkgLinuxPlugin, than_pkg_linux_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void than_pkg_linux_plugin_handle_method_call(
    ThanPkgLinuxPlugin* self, FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, "getPlatformVersion") == 0) {
    response = get_platform_version();
  } else if (strcmp(method, "getWindowSize") == 0) {
    response = get_window_size();
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

static void than_pkg_linux_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(than_pkg_linux_plugin_parent_class)->dispose(object);
}

static void than_pkg_linux_plugin_class_init(ThanPkgLinuxPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = than_pkg_linux_plugin_dispose;
}

static void than_pkg_linux_plugin_init(ThanPkgLinuxPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  ThanPkgLinuxPlugin* plugin = THAN_PKG_LINUX_PLUGIN(user_data);
  than_pkg_linux_plugin_handle_method_call(plugin, method_call);
}

void than_pkg_linux_plugin_register_with_registrar(
    FlPluginRegistrar* registrar) {
  // ကောက်သိမ်းလိုက်ခြင်း
  g_texture_registrar = fl_plugin_registrar_get_texture_registrar(registrar);

  // Window pointer ကို ရယူခြင်း
  FlView* view = fl_plugin_registrar_get_view(registrar);
  if (view != nullptr) {
    g_toplevel_window = gtk_widget_get_toplevel(GTK_WIDGET(view));
  }

  ThanPkgLinuxPlugin* plugin = THAN_PKG_LINUX_PLUGIN(
      g_object_new(than_pkg_linux_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "than_pkg_linux", FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(
      channel, method_call_cb, g_object_ref(plugin), g_object_unref);

  g_object_unref(plugin);
}

/*********************Method Channel Func**************************** */
FlMethodResponse* get_platform_version() {
  struct utsname uname_data = {};
  uname(&uname_data);
  g_autofree gchar* version = g_strdup_printf("Linux %s", uname_data.version);
  g_autoptr(FlValue) result = fl_value_new_string(version);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// func
FlMethodResponse* get_window_size() {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  gint width = 0;
  gint height = 0;
  // Window ရဲ့ လက်ရှိ size ကို ယူခြင်း
  gtk_window_get_size(GTK_WINDOW(g_toplevel_window), &width, &height);

  g_autoptr(FlValue) result = fl_value_new_map();
  fl_value_set_string_take(result, "width", fl_value_new_int(width));
  fl_value_set_string_take(result, "height", fl_value_new_int(height));

  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}
/*********************Method Channel Func**************************** */

/*********************Texture Func**************************** */

// texture register

// --- ၁။ GObject အတွက် လိုအပ်သော Struct နှင့် Typedef များ ---
struct _MyCustomTexture {
  FlPixelBufferTexture parent_instance;
  uint8_t* pixel_buffer;
  uint32_t width;
  uint32_t height;
};

typedef struct _MyCustomTexture MyCustomTexture;
typedef struct {
  FlPixelBufferTextureClass parent_class;
} MyCustomTextureClass;

#define MY_TYPE_CUSTOM_TEXTURE (my_custom_texture_get_type())
#define MY_CUSTOM_TEXTURE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_CUSTOM_TEXTURE, MyCustomTexture))

// Global management အတွက် Modern C++ standard container များ
static std::map<int64_t, MyCustomTexture*> g_active_textures;
static std::mutex g_texture_mutex;

// *************************************************************
// ပြင်လိုက်တဲ့နေရာ - အဟောင်းကို ဖျက်ပြီး ဒါနဲ့ အစားထိုးပါတယ်
// Main ဖိုင်ထဲက registrar ကို လှမ်းမျှသုံးဖို့ ဖြစ်ပါတယ်
extern FlTextureRegistrar* g_texture_registrar;
// *************************************************************

// --- ၂။ GObject Runtime System တွင် Type  ---
G_DEFINE_TYPE(MyCustomTexture, my_custom_texture,
              fl_pixel_buffer_texture_get_type())

static void my_custom_texture_init(MyCustomTexture* self) {
  self->pixel_buffer = nullptr;
  self->width = 0;
  self->height = 0;
}

static gboolean my_custom_texture_copy_pixels(FlPixelBufferTexture* texture,
                                              const uint8_t** buffer,
                                              uint32_t* width, uint32_t* height,
                                              GError** error) {
  auto* self = reinterpret_cast<MyCustomTexture*>(texture);
  if (!self || !self->pixel_buffer) {
    return FALSE;
  }

  *buffer = self->pixel_buffer;
  *width = self->width;
  *height = self->height;
  return TRUE;
}

static void my_custom_texture_class_init(MyCustomTextureClass* klass) {
  FL_PIXEL_BUFFER_TEXTURE_CLASS(klass)->copy_pixels =
      my_custom_texture_copy_pixels;
}

// --- ၃။ Dart FFI ကနေ တိုက်ရိုက်ခေါ်မယ့် C++ Functions များ ---

int64_t than_pkg_linux_plugin_ffi_create_texture() {
  if (!g_texture_registrar) {
    return -1;
  }

  auto* tex = reinterpret_cast<MyCustomTexture*>(
      g_object_new(my_custom_texture_get_type(), nullptr));

  fl_texture_registrar_register_texture(g_texture_registrar, FL_TEXTURE(tex));

  int64_t texture_id = reinterpret_cast<int64_t>(tex);

  {
    std::lock_guard<std::mutex> lock(g_texture_mutex);
    g_active_textures[texture_id] = tex;
  }

  return texture_id;
}

void than_pkg_linux_plugin_ffi_dispose_texture(int64_t texture_id) {
  std::lock_guard<std::mutex> lock(g_texture_mutex);

  auto it = g_active_textures.find(texture_id);
  if (it != g_active_textures.end()) {
    MyCustomTexture* tex = it->second;

    if (g_texture_registrar && tex) {
      // ၁။ Flutter Engine မှာ ဒီ Texture ကို ဆက်မသုံးတော့ကြောင်း သွားဖြုတ်တယ်
      fl_texture_registrar_unregister_texture(g_texture_registrar,
                                              FL_TEXTURE(tex));
    }

    // ၂။ ငါတို့ C++ Map ထဲကနေ ဖယ်ထုတ်တယ်
    g_active_textures.erase(it);

    // ၃။ GObject ရဲ့ Reference Count ကို ချပေးလိုက်တာဖြစ်လို့ RAM ပေါ်ကနေ လုံးဝ
    // ပျောက်ကွယ်သွားပါလိမ့်မယ်
    g_object_unref(tex);
  }
}

void than_pkg_linux_plugin_ffi_update_texture_pixels(int64_t texture_id,
                                                     uint8_t* buffer,
                                                     uint32_t width,
                                                     uint32_t height) {
  std::lock_guard<std::mutex> lock(g_texture_mutex);

  auto it = g_active_textures.find(texture_id);
  if (it != g_active_textures.end()) {
    MyCustomTexture* tex = it->second;
    tex->pixel_buffer = buffer;
    tex->width = width;
    tex->height = height;

    if (g_texture_registrar) {
      fl_texture_registrar_mark_texture_frame_available(g_texture_registrar,
                                                        FL_TEXTURE(tex));
    }
  }
}

/*********************Texture Func**************************** */
