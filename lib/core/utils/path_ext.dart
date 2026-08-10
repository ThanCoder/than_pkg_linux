import 'dart:io';

extension PathExt on String {
  String join(String name) {
    return '$this${Platform.pathSeparator}$name';
  }
}
