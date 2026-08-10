import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/models/app_info.dart';
import 'package:than_pkg_linux/core/models/installed_app.dart';

class PkgInfo {
  final MethodChannel _channel;
  const PkgInfo(this._channel);

  /// OS ထဲမှာ အင်စတော့လုပ်ထားတဲ့ Application များ စာရင်းကို ရယူရန်
  ///
  /// `id` `name` `executable`
  Future<List<InstalledApp>> getInstalledApps() async {
    try {
      final List<dynamic>? apps = await _channel.invokeMethod<List<dynamic>>(
        'get_installed_apps',
      );
      if (apps == null) return [];
      final list = <InstalledApp>[];
      for (var app in apps) {
        list.add(
          .new(
            id: app['id']?.toString() ?? '',
            name: app['name']?.toString() ?? '',
            executable: app['executable']?.toString() ?? '',
          ),
        );
      }

      return list;
    } on PlatformException catch (_) {
      return [];
    }
  }

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

/*
// Get list of installed system applications
FlMethodResponse *get_installed_apps();
 */
