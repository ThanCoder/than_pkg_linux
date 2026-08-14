// ignore_for_file: unused_local_variable, avoid_print

import 'package:flutter/material.dart';
import 'package:than_pkg_linux/than_pkg_linux.dart';
import 'package:than_pkg_linux_example/texture_id_example.dart';

void main() {
  runApp(MaterialApp(home: const MyApp()));
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(),
      body: Placeholder(),
      floatingActionButton: FloatingActionButton(onPressed: test),
    );
  }

  void test() async {
    print('ThanDev Start....');
    final pkg = ThanPkgLinux.getInstance;

    // await pkg.launcher.launchPath(
    //   '/home/thancoder/Videos/queena26_music-test.mp4',
    // );

    // print(await pkg.info.getAppInfo());
    goTexture();
  }

  void goTexture() {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => TextureIdExample()),
    );
  }
}
