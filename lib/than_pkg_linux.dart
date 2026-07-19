import 'package:flutter/services.dart';
// import 'package:than_pkg_linux/core/events/event_listener.dart';
import 'package:than_pkg_linux/core/m_channel.dart';
import 'package:than_pkg_linux/core/texture/texture_handler.dart';

export './core/texture/texture_dummy_test.dart';

class ThanPkgLinux {
  static ThanPkgLinux getInstance = ThanPkgLinux._();
  ThanPkgLinux._();
  factory ThanPkgLinux() => getInstance;

  final _channel = const MethodChannel('than_pkg_linux');

  late final channel = MChannel(_channel);
  late final textureHandler = TextureHandler();
  // late final listener = EventListener(_channel);
}
