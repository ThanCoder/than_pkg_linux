// ignore_for_file: public_member_api_docs, sort_constructors_first
class AppInfo {
  final String packageName;
  final String version;
  final String buildNumber;
  const AppInfo({
    required this.packageName,
    required this.version,
    required this.buildNumber,
  });

  factory AppInfo.empty() {
    return AppInfo(packageName: '', version: '', buildNumber: '');
  }

  factory AppInfo.fromMap(Map<String, dynamic> map) {
    return AppInfo(
      packageName: map['packageName'] as String,
      version: map['version'] as String,
      buildNumber: map['buildNumber'] as String,
    );
  }

  @override
  String toString() =>
      'AppInfo(packageName: $packageName, version: $version, buildNumber: $buildNumber)';
}
