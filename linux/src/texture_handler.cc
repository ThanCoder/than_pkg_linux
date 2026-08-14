#include "texture_handler.h"
#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>

#include "than_globals.h"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <map>
#include <mutex>

// ============================================================
// Texture
// ============================================================
// --- ၁။ GObject အတွက် လိုအပ်သော Struct နှင့် Typedef များ ---
struct _MyCustomTexture {
  FlPixelBufferTexture parent_instance;
  uint8_t *pixel_buffer;
  uint32_t width;
  uint32_t height;
};

typedef struct _MyCustomTexture MyCustomTexture;
typedef struct {
  FlPixelBufferTextureClass parent_class;
} MyCustomTextureClass;

#define MY_TYPE_CUSTOM_TEXTURE (my_custom_texture_get_type())
#define MY_CUSTOM_TEXTURE(obj)                                                 \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_CUSTOM_TEXTURE, MyCustomTexture))

// Global management အတွက် Modern C++ standard container များ
static std::map<int64_t, MyCustomTexture *> g_active_textures;
static std::mutex g_texture_mutex;

// *************************************************************
// ပြင်လိုက်တဲ့နေရာ - အဟောင်းကို ဖျက်ပြီး ဒါနဲ့ အစားထိုးပါတယ်
// Main ဖိုင်ထဲက registrar ကို လှမ်းမျှသုံးဖို့ ဖြစ်ပါတယ်
extern FlTextureRegistrar *g_texture_registrar;
// *************************************************************

// --- ၂။ GObject Runtime System တွင် Type  ---
G_DEFINE_TYPE(MyCustomTexture, my_custom_texture,
              fl_pixel_buffer_texture_get_type())

static void my_custom_texture_init(MyCustomTexture *self) {
  self->pixel_buffer = nullptr;
  self->width = 0;
  self->height = 0;
}

static gboolean my_custom_texture_copy_pixels(FlPixelBufferTexture *texture,
                                              const uint8_t **buffer,
                                              uint32_t *width, uint32_t *height,
                                              GError **error) {
  auto *self = reinterpret_cast<MyCustomTexture *>(texture);
  if (!self || !self->pixel_buffer) {
    return FALSE;
  }

  *buffer = self->pixel_buffer;
  *width = self->width;
  *height = self->height;
  return TRUE;
}

static void my_custom_texture_class_init(MyCustomTextureClass *klass) {
  FL_PIXEL_BUFFER_TEXTURE_CLASS(klass)->copy_pixels =
      my_custom_texture_copy_pixels;
}

// --- ၃။ Dart FFI ကနေ တိုက်ရိုက်ခေါ်မယ့် C++ Functions များ ---

int64_t than_pkg_linux_plugin_ffi_create_texture() {
  if (!g_texture_registrar) {
    return -1;
  }

  auto *tex = reinterpret_cast<MyCustomTexture *>(
      g_object_new(my_custom_texture_get_type(), nullptr));

  fl_texture_registrar_register_texture(g_texture_registrar, FL_TEXTURE(tex));

  int64_t texture_id = reinterpret_cast<int64_t>(tex);

  {
    std::lock_guard<std::mutex> lock(g_texture_mutex);
    g_active_textures[texture_id] = tex;
  }
  printf("[than_pkg_linux_plugin_ffi_create_texture]: created");

  return texture_id;
}

void than_pkg_linux_plugin_ffi_dispose_texture(int64_t texture_id) {
  std::lock_guard<std::mutex> lock(g_texture_mutex);

  auto it = g_active_textures.find(texture_id);
  if (it != g_active_textures.end()) {
    MyCustomTexture *tex = it->second;

    if (g_texture_registrar && tex) {
      // ၁။ Flutter Engine မှာ ဒီ Texture ကို ဆက်မသုံးတော့ကြောင်း သွားဖြုတ်တယ်
      fl_texture_registrar_unregister_texture(g_texture_registrar,
                                              FL_TEXTURE(tex));
      printf("[fl_texture_registrar_unregister_texture]: released");
    }

    // ၂။ ငါတို့ C++ Map ထဲကနေ ဖယ်ထုတ်တယ်
    g_active_textures.erase(it);

    // ၃။ GObject ရဲ့ Reference Count ကို ချပေးလိုက်တာဖြစ်လို့ RAM ပေါ်ကနေ လုံးဝ
    // ပျောက်ကွယ်သွားပါလိမ့်မယ်
    g_object_unref(tex);
  }
}

void than_pkg_linux_plugin_ffi_update_texture_pixels(int64_t texture_id,
                                                     uint8_t *buffer,
                                                     uint32_t width,
                                                     uint32_t height) {
  std::lock_guard<std::mutex> lock(g_texture_mutex);

  auto it = g_active_textures.find(texture_id);
  if (it != g_active_textures.end()) {
    MyCustomTexture *tex = it->second;
    tex->pixel_buffer = buffer;
    tex->width = width;
    tex->height = height;

    if (g_texture_registrar) {
      fl_texture_registrar_mark_texture_frame_available(g_texture_registrar,
                                                        FL_TEXTURE(tex));
    }
  }
}