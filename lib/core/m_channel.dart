import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/types.dart';

class MChannel {
  final MethodChannel _channel;
  const MChannel(this._channel);

  Future<String?> getVersion() async {
    return await _channel.invokeMethod<String>('getPlatformVersion');
  }

  Future<TWindowSize?> getWindowSize() async {
    final res = await _channel.invokeMapMethod('getWindowSize');
    if (res == null) return null;
    return TWindowSize(width: res['width'] ?? 0, height: res['height'] ?? 0);
  }
}
