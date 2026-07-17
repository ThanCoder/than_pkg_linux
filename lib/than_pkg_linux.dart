import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/m_channel.dart';

class ThanPkgLinux {
  static ThanPkgLinux instance = ThanPkgLinux._();
  ThanPkgLinux._();
  factory ThanPkgLinux() => instance;

  final _channel = const MethodChannel('than_pkg_linux');

  late final channel = MChannel(_channel);
}
