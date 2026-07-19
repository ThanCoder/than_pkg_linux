import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/types.dart';

class MChannel {
  final MethodChannel _channel;
  const MChannel(this._channel);

  Future<void> minimizeWindow() async {
    await _channel.invokeMethod('minimizeWindow');
  }

  Future<void> setKeepAbove(bool keepAbove) async {
    await _channel.invokeMethod('setKeepAbove', keepAbove);
  }

  Future<void> setWindowSize({required int width, required int height}) async {
    await _channel.invokeMethod('setWindowSize', {
      'width': width,
      'height': height,
    });
  }

  Future<void> centerWindow() async {
    await _channel.invokeMethod('centerWindow');
  }

  Future<void> setWindowBordered(bool bordered) async {
    await _channel.invokeMethod('setWindowBordered', bordered);
  }

  Future<void> closeWindow() async {
    await _channel.invokeMethod('closeWindow');
  }

  Future<String?> getVersion() async {
    return await _channel.invokeMethod<String>('getPlatformVersion');
  }

  Future<TWindowSize?> getWindowSize() async {
    final res = await _channel.invokeMapMethod('getWindowSize');
    if (res == null) return null;
    return TWindowSize(width: res['width'] ?? 0, height: res['height'] ?? 0);
  }

  Future<void> setFullscreen(bool enable) async {
    await _channel.invokeMethod('setFullscreen', enable);
  }

  Future<void> setWindowTitle(String title) async {
    await _channel.invokeMethod('setWindowTitle', title);
  }

  /// ### Get Window Title
  Future<String?> getWindowTitle() async {
    return await _channel.invokeMethod<String>('getWindowTitle');
  }

  Future<bool> isFullScreen() async {
    return (await _channel.invokeMethod<bool>('isFullScreen')) ?? false;
  }

  Future<void> toggleFullScreen() async {
    await _channel.invokeMethod('toggleFullScreen');
  }
}
