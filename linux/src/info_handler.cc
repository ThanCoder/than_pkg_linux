#include "info_handler.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>

#include <cstdio>
#include <cstring>


/********************* System Info Func **************************** */
FlMethodResponse *get_os_release() {
  g_autofree gchar *pretty_name = nullptr;

  // /etc/os-release ကို ဖတ်ယူခြင်း
  if (g_file_test("/etc/os-release", G_FILE_TEST_EXISTS)) {
    g_autoptr(GKeyFile) key_file = g_key_file_new();
    if (g_key_file_load_from_file(key_file, "/etc/os-release", G_KEY_FILE_NONE,
                                  nullptr)) {
      pretty_name =
          g_key_file_get_string(key_file, "os-release", "PRETTY_NAME", nullptr);
    }
  }

  // ဖတ်လို့မရခဲ့ရင် fallback ထားပေးခြင်း
  if (pretty_name == nullptr) {
    pretty_name = g_strdup("Linux");
  }

  g_autoptr(FlValue) result = fl_value_new_string(pretty_name);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// version
FlMethodResponse *get_platform_version() {
  struct utsname uname_data = {};
  uname(&uname_data);
  g_autofree gchar *version = g_strdup_printf("Linux %s", uname_data.version);
  g_autoptr(FlValue) result = fl_value_new_string(version);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

/*********************app info**************************** */
FlMethodResponse *get_app_info() {
  g_autoptr(FlValue) result = fl_value_new_map();

  // Package Name (Application ID) ရယူခြင်း
  GApplication *app = g_application_get_default();
  const gchar *app_id = app ? g_application_get_application_id(app) : nullptr;
  fl_value_set_string_take(result, "packageName",
                           fl_value_new_string(app_id ? app_id : "unknown"));

  // App Version (CMake / Pubspec ကလာသော Value)
#ifdef FLUTTER_BUILD_NAME
  fl_value_set_string_take(result, "version",
                           fl_value_new_string(FLUTTER_BUILD_NAME));
#else
  fl_value_set_string_take(result, "version", fl_value_new_string("1.0.0"));
#endif

  // Build Number
#ifdef FLUTTER_BUILD_NUMBER
  fl_value_set_string_take(result, "buildNumber",
                           fl_value_new_string(FLUTTER_BUILD_NUMBER));
#else
  fl_value_set_string_take(result, "buildNumber", fl_value_new_string("1"));
#endif

  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}
