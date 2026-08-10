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
+ [x] [`Info`](#info-example)
+ [x] [`PathProvider`](#pathprovider-example)
+ [x] [`Launcher`](#launcher-example)

---

### Launcher Example
```dart
final pkg = ThanPkgLinux.getInstance.launcher;

await pkg.launchUrl('https://pub.dev/'); // bool
await pkg.launchPath('[path]',);
await pkg.launchApp('vlc')// bool
```

### Info Example
```dart
final pkg = ThanPkgLinux.getInstance.info;

pkg.getAppInfo()// AppInfo(packageName: com.example.than_pkg_linux, version: 1.0.0, buildNumber: 1)
pkg.getOsRelease() //Linux
pkg.getVersion() //Linux #1 SMP PREEMPT_DYNAMIC Debian 6.12.101-1 (2026-08-05)
pkg.getInstalledApps() // `[InstalledApp(id: $id, name: $name, executable: $executable)]`
```

### PathProvider Example
```dart
final pkg = ThanPkgLinux.getInstance.pathHandler;

pkg.getTemporaryDirectory()// /home/[host]/.cache
pkg.getDesktopDirectory() ///home/[host]/Desktop
pkg.getDownloadsDirectory() // /home/[host]/Downloads
pkg.getPicturesDirectory() // /home/[host]/Pictures
pkg.getApplicationDocumentsDirectory() ///home/[host]/Documents
pkg.getApplicationSupportDirectory() // /home/[host]/.config

pkg.getExecutablePath() 
// `/home/[host]/projects/[project path]/build/linux/x64/debug/bundle/than_pkg_linux_example`

pkg.getWorkingDirectory() 
// `/home/[host]/projects/[project path]/example` 

pkg.getApplicationTemporaryDirectory() 
// `/home/[host]/.cache/[com.example.than_pkg_linux]`


pkg.getApplicationConfigDirectory() 
// `/home/[host]/.config/[com.example.than_pkg_linux]`

pkg.getApplicationHomeDirectory() 
// `/home/[host]/[com.example.than_pkg_linux]`

```

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