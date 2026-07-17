import 'package:flutter/material.dart';
import 'package:than_pkg_linux/than_pkg_linux.dart';

void main() {
  runApp(MaterialApp(home: const MyApp()));
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(),
      body: Placeholder(),
      floatingActionButton: FloatingActionButton(
        onPressed: () async {
          final pkg = ThanPkgLinux.instance.channel;
          print('version: ${await pkg.getVersion()}');
          print('getWindowSize: ${await pkg.getWindowSize()}');
        },
      ),
    );
  }
}
