// ignore_for_file: avoid_print

import 'dart:async';
import 'dart:ffi';

import 'package:ffi/ffi.dart';
import 'package:flutter/material.dart';
import 'package:than_pkg_linux/than_pkg_linux.dart';

class TextureIdExample extends StatefulWidget {
  const TextureIdExample({super.key});

  @override
  State<TextureIdExample> createState() => _TextureIdExampleState();
}

class _TextureIdExampleState extends State<TextureIdExample> {
  @override
  void initState() {
    super.initState();
    genereateColors();
  }

  @override
  void dispose() {
    if (textureId != null) {
      ThanPkgLinux.getInstance.textureHandler.releaseTexture(textureId!);
    }
    if (buffer != nullptr) {
      calloc.free(buffer);
    }
    loopTimer?.cancel();
    super.dispose();
  }

  int? textureId;
  Pointer<Uint8> buffer = nullptr;
  Timer? loopTimer;

  void genereateColors() {
    if (buffer == nullptr) {
      buffer = calloc.call<Uint8>();
    }

    textureId ??= ThanPkgLinux.getInstance.textureHandler.createTextureId();

    // // test colors
    testTextureDummyColor(textureId!);
    setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('TextureIdExample')),
      body: Center(
        child: textureId == null
            ? Text('Texture is null!')
            : Texture(textureId: textureId!),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () async {
          // if (textureId == null) {
          //   print('texture id is null!');
          //   return;
          // }
          genereateColors();
        },
      ),
    );
  }
}
