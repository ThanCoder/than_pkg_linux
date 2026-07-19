// ignore_for_file: camel_case_types, non_constant_identifier_names

import 'dart:ffi';

/* 
FLUTTER_PLUGIN_EXPORT int64_t than_pkg_linux_plugin_ffi_create_texture();

// Texture ကို အပြီးဖျက်မယ့် function ကြေညာခြင်း
FLUTTER_PLUGIN_EXPORT void than_pkg_linux_plugin_ffi_dispose_texture(
    int64_t texture_id);

// ၂။ ရလာတဲ့ ID ထဲကို Pixel bufferPointer သွားချိတ်မယ့် function
FLUTTER_PLUGIN_EXPORT void than_pkg_linux_plugin_ffi_update_texture_pixels(
    int64_t texture_id, uint8_t* buffer, uint32_t width, uint32_t height);
*/

final dylib = DynamicLibrary.process();

// c အတွက်အရင်ရေး
typedef _c_create_texture = Int64 Function();
typedef _c_dispose_texture = Void Function(Int64 texture_id);
typedef _c_update_texture_pixels =
    Void Function(
      Int64 texture_id,
      Pointer<Uint8> buffer,
      Int32 width,
      Int32 height,
    );
// dart အတွက်
typedef _dart_create_texture = int Function();
typedef _dart_dipose_texture = void Function(int texture_id);
typedef _dart_update_texture_pixels =
    void Function(int texture_id, Pointer<Uint8> buffer, int width, int height);

final _dart_create_texture _create_texture = dylib
    .lookup<NativeFunction<_c_create_texture>>(
      'than_pkg_linux_plugin_ffi_create_texture',
    )
    .asFunction();
final _dart_dipose_texture _dispose_texture = dylib
    .lookup<NativeFunction<_c_dispose_texture>>(
      'than_pkg_linux_plugin_ffi_dispose_texture',
    )
    .asFunction();

final _dart_update_texture_pixels _update_texture = dylib
    .lookup<NativeFunction<_c_update_texture_pixels>>(
      'than_pkg_linux_plugin_ffi_update_texture_pixels',
    )
    .asFunction();

class TextureHandler {
  /// ### Create Texture Id
  int createTextureId() {
    return _create_texture();
  }

  /// ### Release Texture Id
  void releaseTexture(int textureId) {
    _dispose_texture(textureId);
  }

  /// ### Update Texture Pixels
  void updateTexturePixels(
    int textureId, {
    required Pointer<Uint8> buffer,
    required int width,
    required int height,
  }) {
    _update_texture(textureId, buffer, width, height);
  }
}
