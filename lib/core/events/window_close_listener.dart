// ignore_for_file: avoid_print

import 'dart:async';

import 'package:flutter/services.dart';

class WindowCloseListener {
  final MethodChannel _channel;
  WindowCloseListener(this._channel);

  final StreamController<WindowCloseEvent> _controller =
      StreamController<WindowCloseEvent>.broadcast();

  Stream<WindowCloseEvent> get onCloseRequest => _controller.stream;

  Future<void> startWindowCloseListen() async {
    _channel.setMethodCallHandler((call) async {
      if (call.method == 'onWindowCloseRequest') {
        final event = WindowCloseEvent();
        _controller.add(event);

        final shouldClose = await event.future;
        return shouldClose;
      }
      throw MissingPluginException();
    });
    _controller.onListen = () {
      print('on start');
      _channel.invokeMethod('setCloseHandlerListening', true);
    };
    _controller.onCancel = () {
      print('on cancel');
      _channel.invokeMethod('setCloseHandlerListening', false);
    };
  }
}

class WindowCloseEvent {
  final Completer<bool> _completer = Completer<bool>();

  Future<bool> get future => _completer.future;

  // App ကို ပိတ်ခွင့်ပြုလိုက်မယ်
  void accept() => _completer.complete(true);

  // App ပိတ်မယ့်အစီအစဉ်ကို ဖျက်သိမ်းမယ်
  void reject() => _completer.complete(false);
}
