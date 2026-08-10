import 'dart:io';

import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/utils/path_ext.dart';
import 'package:than_pkg_linux/core/pkg_info.dart';

class PathProvider {
  final MethodChannel _channel;
  final PkgInfo _pkgInfo;
  const PathProvider(this._channel, this._pkgInfo);

  //*****************App Path************************* */

  /// `/home/[host]/[com.example.than_pkg_linux]`
  Future<Directory?> getApplicationHomeDirectory() async {
    final home = Platform.environment['HOME'];
    if (home == null) return null;

    final info = await _pkgInfo.getAppInfo();
    if (info == null) return null;
    final dir = Directory(home.join(info.packageName));
    if (!dir.existsSync()) {
      await dir.create(recursive: true);
    }

    return dir;
  }

  /// `/home/[host]/.cache/[com.example.than_pkg_linux]`
  Future<Directory?> getApplicationTemporaryDirectory() async {
    final home = Platform.environment['HOME'];
    if (home == null) return null;

    final info = await _pkgInfo.getAppInfo();
    if (info == null) return null;
    final dir = Directory(home.join('.cache').join(info.packageName));
    if (!dir.existsSync()) {
      await dir.create(recursive: true);
    }

    return dir;
  }

  /// `/home/[host]/.config/[com.example.than_pkg_linux]`
  Future<Directory?> getApplicationConfigDirectory() async {
    final home = Platform.environment['HOME'];
    if (home == null) return null;

    final info = await _pkgInfo.getAppInfo();
    if (info == null) return null;
    final dir = Directory(home.join('.config').join(info.packageName));
    if (!dir.existsSync()) {
      await dir.create(recursive: true);
    }

    return dir;
  }

  //*****************Path Only************************* */
  /// /home/[host]
  Future<Directory?> getHomeDirectory() async {
    final home = Platform.environment['HOME'];
    if (home == null) return null;
    final dir = Directory(home);
    if (!dir.existsSync()) {
      await dir.create(recursive: true);
    }
    return dir;
  }

  ///  /home/[host]/Documents
  Future<String?> getApplicationDocumentsDirectory() async {
    return await _channel.invokeMethod<String>(
      'get_application_documents_directory',
    );
  }

  /// /home/[host]/.cache
  Future<String?> getTemporaryDirectory() async {
    return await _channel.invokeMethod<String>('get_temporary_directory');
  }

  ///  /home/[host]/.config
  Future<String?> getApplicationSupportDirectory() async {
    return await _channel.invokeMethod<String>(
      'get_application_support_directory',
    );
  }

  /// /home/[host]/Downloads
  Future<String?> getDownloadsDirectory() async {
    return await _channel.invokeMethod<String>('get_downloads_directory');
  }

  /// /home/[host]/Desktop
  Future<String?> getDesktopDirectory() async {
    return await _channel.invokeMethod<String>('get_desktop_directory');
  }

  /// /home/[host]/Pictures
  Future<String?> getPicturesDirectory() async {
    return await _channel.invokeMethod<String>('get_pictures_directory');
  }

  /// `/home/[host]/projects/[project path]/build/linux/x64/debug/bundle/than_pkg_linux_example`
  Future<String?> getExecutablePath() async {
    return await _channel.invokeMethod<String>('get_executable_path');
  }

  /// `/home/[host]/projects/[project path]/example`
  Future<String?> getWorkingDirectory() async {
    return await _channel.invokeMethod<String>('get_working_directory');
  }
}
/*
FlMethodResponse *get_application_documents_directory();
FlMethodResponse *get_temporary_directory();
FlMethodResponse *get_application_support_directory();
FlMethodResponse *get_downloads_directory();
FlMethodResponse *get_desktop_directory();
FlMethodResponse *get_pictures_directory();


FlMethodResponse *get_executable_path();
FlMethodResponse *get_working_directory(
*/