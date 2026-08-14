import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/launcher.dart';
// import 'package:than_pkg_linux/core/events/event_listener.dart';
import 'package:than_pkg_linux/core/window/window.dart';
import 'package:than_pkg_linux/core/path_provider.dart';
import 'package:than_pkg_linux/core/pkg_info.dart';
import 'package:than_pkg_linux/core/texture/texture_handler.dart';

export './core/texture/texture_dummy_test.dart';
export 'core/models/index.dart';

class ThanPkgLinux {
  static ThanPkgLinux getInstance = ThanPkgLinux._();
  ThanPkgLinux._();
  factory ThanPkgLinux() => getInstance;

  final _channel = const MethodChannel('than_pkg_linux');

  late final window = Window(_channel);
  late final textureHandler = TextureHandler();
  late final info = PkgInfo(_channel);
  late final launcher = Launcher(_channel);
  late final pathHandler = PathProvider(_channel, info);
}
