# than_pkg_linux

A powerful Flutter plugin for Linux desktop development, providing advanced window management features and low-level pixel buffer texture handling.

## Features

*   **Window Management (`MChannel`):** Easily control window state, size, visibility, and positioning (center, minimize, full screen, etc.) directly from Dart.
*   **Low-Level Texture Handling (`TextureHandler`):** Render and update raw pixel buffers efficiently using Flutter's `Texture` widget on Linux.

---

### Example
```dart
ThanPkgLinux.getInstance.[whatever your want!]
```

+ [x] [`MChannel`](#m-channel)
+ [x] [`TextureHandler`](#texturehandler)
[Example](https://github.com/ThanCoder/than_pkg_linux/blob/main/example/lib/texture_id_example.dart)
  

### M Channel
```dart
final pkg = ThanPkgLinux.getInstance.channel;

pkg.centerWindow()
pkg.closeWindow()
pkg.getVersion()
pkg.getWindowSize()
pkg.getWindowTitle()
pkg.isFullScreen()
pkg.minimizeWindow()
pkg.setFullscreen(enable)
pkg.setKeepAbove(keepAbove)
pkg.setWindowBordered(bordered)
pkg.setWindowSize(width: width, height: height)
pkg.setWindowTitle(title)
pkg.toggleFullScreen()
```

### TextureHandler
[Example](https://github.com/ThanCoder/than_pkg_linux/blob/main/example/lib/texture_id_example.dart)

```dart
final pkg = ThanPkgLinux.getInstance.textureHandler;

pkg.createTextureId()
pkg.releaseTexture(textureId)
pkg.updateTexturePixels(textureId, buffer: buffer, width: width, height: height)

//test colors
testTextureDummyColor(textureId!);
```