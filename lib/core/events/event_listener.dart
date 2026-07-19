import 'package:flutter/services.dart';
import 'package:than_pkg_linux/core/events/window_close_listener.dart';

class EventListener {
  final MethodChannel _channel;
  EventListener(this._channel);

  late final windowCloseEvent = WindowCloseListener(_channel);
}
