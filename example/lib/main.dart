// ignore_for_file: unused_local_variable, avoid_print

import 'package:flutter/material.dart';
import 'package:than_pkg_linux/than_pkg_linux.dart';
import 'package:than_pkg_linux_example/texture_id_example.dart';

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
          await Navigator.push(
            context,
            MaterialPageRoute(builder: (context) => TextureIdExample()),
          );

          print('ThanDev Start....');
          final pkg = ThanPkgLinux.getInstance.textureHandler;
        },
      ),
    );
  }
}
