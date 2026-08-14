import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/models/t_window_size.dart';

class Window {
  final MethodChannel _channel;

  Window(this._channel);

  // late final closeEvent = WindowCloseEvent(_channel);

  /// Sets the minimum and maximum size of the application window.
  ///
  /// The window cannot be resized below [minWidth] x [minHeight]
  /// or beyond [maxWidth] x [maxHeight].
  Future<void> setWindowSizeLimits({
    required int minWidth,
    required int minHeight,
    required int maxWidth,
    required int maxHeight,
  }) {
    return _channel.invokeMethod('setWindowSizeLimits', {
      'minWidth': minWidth,
      'minHeight': minHeight,
      'maxWidth': maxWidth,
      'maxHeight': maxHeight,
    });
  }

  /// Sets the maximum size of the application window.
  ///
  /// The window cannot be resized beyond the specified width and height.
  Future<void> setMaxWindowSize({required int width, required int height}) {
    return _channel.invokeMethod('setMaxWindowSize', {
      'width': width,
      'height': height,
    });
  }

  /// Sets the minimum size of the application window.
  ///
  /// The window cannot be resized below the specified width and height.
  Future<void> setMinWindowSize({required int width, required int height}) {
    return _channel.invokeMethod('setMinWindowSize', {
      'width': width,
      'height': height,
    });
  }

  /// Minimizes the application window.
  Future<void> minimizeWindow() async {
    await _channel.invokeMethod('minimizeWindow');
  }

  /// Keeps the application window above other windows.
  ///
  /// Set [keepAbove] to `true` to keep the window above other windows,
  /// or `false` to restore the default behavior.
  Future<void> setKeepAbove(bool keepAbove) async {
    await _channel.invokeMethod('setKeepAbove', keepAbove);
  }

  /// Sets the size of the application window.
  Future<void> setWindowSize({required int width, required int height}) async {
    await _channel.invokeMethod('setWindowSize', {
      'width': width,
      'height': height,
    });
  }

  /// Centers the application window on the screen.
  Future<void> centerWindow() async {
    await _channel.invokeMethod('centerWindow');
  }

  /// Enables or disables the window border.
  ///
  /// Set [bordered] to `true` to show the window border,
  /// or `false` to remove it.
  Future<void> setWindowBordered(bool bordered) async {
    await _channel.invokeMethod('setWindowBordered', bordered);
  }

  /// Closes the application window.
  Future<void> closeWindow() async {
    await _channel.invokeMethod('closeWindow');
  }

  /// Returns the current size of the application window.
  ///
  /// Returns `null` if the window size cannot be retrieved.
  Future<TWindowSize?> getWindowSize() async {
    final res = await _channel.invokeMapMethod('getWindowSize');
    if (res == null) return null;

    return TWindowSize(width: res['width'] ?? 0, height: res['height'] ?? 0);
  }

  /// Enables or disables fullscreen mode.
  ///
  /// Set [enable] to `true` to enter fullscreen mode,
  /// or `false` to exit fullscreen mode.
  Future<void> setFullscreen(bool enable) async {
    await _channel.invokeMethod('setFullscreen', enable);
  }

  /// Sets the title of the application window.
  Future<void> setWindowTitle(String title) async {
    await _channel.invokeMethod('setWindowTitle', title);
  }

  /// Returns the current title of the application window.
  ///
  /// Returns `null` if the window title cannot be retrieved.
  Future<String?> getWindowTitle() async {
    return await _channel.invokeMethod<String>('getWindowTitle');
  }

  /// Returns whether the application window is currently fullscreen.
  Future<bool> isFullScreen() async {
    return (await _channel.invokeMethod<bool>('isFullScreen')) ?? false;
  }

  /// Toggles fullscreen mode.
  ///
  /// Enters fullscreen mode if the window is not fullscreen,
  /// or exits fullscreen mode if it is already fullscreen.
  Future<void> toggleFullScreen() async {
    await _channel.invokeMethod('toggleFullScreen');
  }
}
