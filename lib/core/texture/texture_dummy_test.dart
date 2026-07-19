// ignore_for_file: avoid_print

import 'dart:ffi';
import 'dart:math' as math;

import 'package:ffi/ffi.dart';
import 'package:than_pkg_linux/than_pkg_linux.dart';

void getRandomDummyColors(
  Pointer<Uint8> buffer, {
  int width = 200,
  int height = 200,
}) {
  final random = math.Random();

  // R, G, B တစ်ခုချင်းစီအတွက် 0 ကနေ 255 ကြား random value သတ်မှတ်မယ်
  int r = random.nextInt(256);
  int g = random.nextInt(256);
  int b = random.nextInt(256);

  int totalBytes = width * height * 4;

  // print("Generated Random Color -> R: $r, G: $g, B: $b");

  // Loop ထဲမှာ ဒီ random အရောင်ကိုပဲ တစ်ပြင်လုံး ဖြည့်ပေးလိုက်မယ်
  for (int i = 0; i < totalBytes; i += 4) {
    buffer[i] = r; // Random Red
    buffer[i + 1] = g; // Random Green
    buffer[i + 2] = b; // Random Blue
    buffer[i + 3] = 255; // Alpha (Fully Opaque)
  }
}

/// ### dummy test
Future<void> testTextureDummyColor(
  int textureId, {
  int width = 200,
  int height = 200,
}) async {
  final handler = ThanPkgLinux.getInstance.textureHandler;

  // ၃။ စမ်းသပ်မည့် Width နဲ့ Height သတ်မှတ်မယ်

  int totalBytes = width * height * 4;

  // ၄။ Memory ပေါ်မှာ Buffer အလွတ်ဆောက်မယ်
  Pointer<Uint8> dummyBuffer = calloc<Uint8>(totalBytes);

  try {
    // --- ပြင်ဆင်ရမည့် နေရာ ---
    // တစ်ခါ function ခေါ်တိုင်း တစ်မျိုးထွက်အောင် Random generator ဆောက်မယ်

    final random = math.Random();

    // R, G, B တစ်ခုချင်းစီအတွက် 0 ကနေ 255 ကြား random value သတ်မှတ်မယ်
    int r = random.nextInt(256);
    int g = random.nextInt(256);
    int b = random.nextInt(256);

    print("Generated Random Color -> R: $r, G: $g, B: $b");

    // Loop ထဲမှာ ဒီ random အရောင်ကိုပဲ တစ်ပြင်လုံး ဖြည့်ပေးလိုက်မယ်
    for (int i = 0; i < totalBytes; i += 4) {
      dummyBuffer[i] = r; // Random Red
      dummyBuffer[i + 1] = g; // Random Green
      dummyBuffer[i + 2] = b; // Random Blue
      dummyBuffer[i + 3] = 255; // Alpha (Fully Opaque)
    }

    handler.updateTexturePixels(
      textureId,
      buffer: dummyBuffer,
      width: width,
      height: height,
    );

    print("Texture updated with Random Color successfully!");
  } catch (e) {
    print("FFI Call Error: $e");
  } finally {
    // Memory leak မဖြစ်အောင် buffer ပြန်ဖျက်မယ်
    Future.delayed(Duration(seconds: 1)).then((value) {
      calloc.free(dummyBuffer);
      print('free `buffer` memory');
    });
  }
}
