# than_pkg_linux


### Example
```dart
ThanPkgLinux.getInstance.[whatever your want!]
```

+ [x] [`MChannel`](#m-channel)
+ [x] [`TextureHandler`](#texturehandler)
  

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
```dart
final pkg = ThanPkgLinux.getInstance.textureHandler;

pkg.createTextureId()
pkg.releaseTexture(textureId)
pkg.updateTexturePixels(textureId, buffer: buffer, width: width, height: height)
```