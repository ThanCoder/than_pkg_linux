// ignore_for_file: public_member_api_docs, sort_constructors_first
class InstalledApp {
  final String id;
  final String name;
  final String executable;
  const InstalledApp({
    required this.id,
    required this.name,
    required this.executable,
  });

  @override
  String toString() =>
      'InstalledApp(id: $id, name: $name, executable: $executable)';
}
