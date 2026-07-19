// // ignore_for_file: avoid_print

// import 'dart:async';

// import 'package:flutter/material.dart';
// import 'package:than_pkg_linux/than_pkg_linux.dart';

// class WindowCloseListenerExample extends StatefulWidget {
//   const WindowCloseListenerExample({super.key});

//   @override
//   State<WindowCloseListenerExample> createState() =>
//       _WindowCloseListenerExampleState();
// }

// class _WindowCloseListenerExampleState
//     extends State<WindowCloseListenerExample> {
//   StreamSubscription? _sub;
//   @override
//   void initState() {
//     init();
//     super.initState();
//   }

//   @override
//   void dispose() {
//     _sub?.cancel();
//     super.dispose();
//   }

//   void init() {
//     // start listen
//     ThanPkgLinux.instance.listener.windowCloseEvent.startWindowCloseListen();

//     // listen
//     _sub = ThanPkgLinux.instance.listener.windowCloseEvent.onCloseRequest.listen((
//       event,
//     ) async {
//       print('windowCloseEvent: $event');
//       if (!mounted) return;
//       // ဥပမာ - Dialog ပြပြီး အဖြေစောင့်မယ်
//       bool? dialogResult = await showDialog<bool>(
//         context: context,
//         builder: (context) => AlertDialog(
//           title: Text("ပိတ်မှာ သေချာလား?"),
//           actions: [
//             TextButton(
//               onPressed: () => Navigator.pop(context, false),
//               child: Text("မပိတ်ပါ"),
//             ),
//             TextButton(
//               onPressed: () => Navigator.pop(context, true),
//               child: Text("ပိတ်မည်"),
//             ),
//           ],
//         ),
//       );

//       if (dialogResult == true) {
//         event.accept(); // တကယ်ပိတ်ခိုင်းလိုက်မယ် (C++ ဘက်ကို true ပြန်ပို့မယ်)
//       } else {
//         event
//             .reject(); // ပိတ်မယ့်အစီအစဉ်ကို ဖျက်မယ် (C++ ဘက်ကို false ပြန်ပို့မယ်)
//       }
//     });
//   }

//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(title: Text('WindowCloseListenerExample')),
//       body: Placeholder(),
//     );
//   }
// }
