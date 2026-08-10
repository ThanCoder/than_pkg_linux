import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/models/app_info.dart';

class PkgInfo {
  final MethodChannel _channel;
  const PkgInfo(this._channel);

  /// ### App Version
  Future<String?> getVersion() async {
    return await _channel.invokeMethod<String>('getPlatformVersion');
  }

  /// ### App Info
  ///
  /// `packageName`
  /// `app_id`
  /// `version`
  /// `buildNumber`
  Future<AppInfo?> getAppInfo() async {
    final map = await _channel.invokeMapMethod<String, dynamic>('getAppInfo');
    if (map == null) return null;
    return AppInfo.fromMap(map);
  }

  /// `/etc/os-release` ဖိုင်ကို ဖတ်ပြီး 
  /// Linux Distribution Name 
  /// `(ဥပမာ Ubuntu 22.04 LTS, Fedora Linux 38)`
  Future<String?> getOsRelease() async {
    return await _channel.invokeMethod<String>('getOsRelease');
  }
}
