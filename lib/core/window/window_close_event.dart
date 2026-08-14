// import 'package:flutter/material.dart';
// import 'package:flutter/services.dart';

// class WindowCloseEvent {
//   final MethodChannel _channel;

//   WindowCloseEvent(this._channel);

//   Future<void> listen(BuildContext context) async {
//     print('[CloseEvent] setting handler');

//     _channel.setMethodCallHandler((call) async {
//       print('[CloseEvent] received: ${call.method}');

//       if (call.method == 'onWindowCloseRequested') {
//         await _onWindowCloseRequested(context);
//       }
//     });

//     print('[CloseEvent] invoking native');

//     final result = await _channel.invokeMethod(
//       'setCloseHandlerListening',
//       true,
//     );

//     print('[CloseEvent] native result: $result');
//   }

//   Future<void> _onWindowCloseRequested(BuildContext context) async {
//     final shouldClose = await showDialog<bool>(
//       context: context,
//       builder: (context) {
//         return AlertDialog(
//           title: const Text('Close application?'),
//           content: const Text(
//             'Are you sure you want to close the application?',
//           ),
//           actions: [
//             TextButton(
//               onPressed: () {
//                 Navigator.pop(context, false);
//               },
//               child: const Text('Cancel'),
//             ),
//             FilledButton(
//               onPressed: () {
//                 Navigator.pop(context, true);
//               },
//               child: const Text('Close'),
//             ),
//           ],
//         );
//       },
//     );

//     if (shouldClose == true) {
//       await _channel.invokeMethod('allowWindowClose');
//     }
//   }
// }
