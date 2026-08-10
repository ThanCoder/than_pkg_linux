import 'package:flutter/services.dart';

class Launcher {
  final MethodChannel _channel;
  const Launcher(this._channel);

  /// Web URL တစ်ခုကို Linux Default Browser ဖြင့် ဖွင့်ရန်
  ///
  /// `https://pub.dev/`
  Future<bool> launchUrl(String url) async {
    try {
      final bool? success = await _channel.invokeMethod<bool>(
        'launch_url',
        url,
      );
      return success ?? false;
    } on PlatformException catch (_) {
      return false;
    }
  }

  /// File သို့မဟုတ် Folder Path ကို Default File Manager / App ဖြင့် ဖွင့်ရန်
  ///
  /// [path]
  Future<bool> launchPath(String path) async {
    try {
      final bool? success = await _channel.invokeMethod<bool>(
        'launch_path',
        path,
      );
      return success ?? false;
    } on PlatformException catch (_) {
      return false;
    }
  }

  /// Installed Linux App တစ်ခုခုကို Desktop ID သို့မဟုတ် Command Name ဖြင့် Launch လုပ်ရန်
  ///
  /// Example:
  ///
  /// `launchApp('org.gnome.Nautilus.desktop')` သို့မဟုတ် `launchApp('vlc')`
  ///
  /// Return -> `bool`
  Future<bool> launchApp(String appIdOrCommand) async {
    try {
      final bool? success = await _channel.invokeMethod<bool>(
        'launch_app',
        appIdOrCommand,
      );
      return success ?? false;
    } on PlatformException catch (_) {
      return false;
    }
  }
}

/*
FlMethodResponse *launch_url(FlValue *args);  // Open Web URL (https://...)
FlMethodResponse *launch_path(FlValue *args); // Open File or Folder Path
// Launch App by Desktop ID or Command
FlMethodResponse *launch_app(FlValue *args);


 */
