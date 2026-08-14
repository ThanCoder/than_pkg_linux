#include "launcher_handler.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>

#include <cstdio>
#include <cstring>

#include <gio/gio.h>
#include <gtk/gtk.h>

// 1. URL ဖွင့်ရန်
FlMethodResponse *launch_url(FlValue *args) {
  if (fl_value_get_type(args) != FL_VALUE_TYPE_STRING) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGS", "URL must be string", nullptr));
  }

  const gchar *url = fl_value_get_string(args);
  g_autoptr(GError) error = nullptr;

  if (!g_app_info_launch_default_for_uri(url, nullptr, &error)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("LAUNCH_FAILED", error->message, nullptr));
  }

  return FL_METHOD_RESPONSE(
      fl_method_success_response_new(fl_value_new_bool(true)));
}

// 2. File / Folder Path ဖွင့်ရန်
FlMethodResponse *launch_path(FlValue *args) {
  if (fl_value_get_type(args) != FL_VALUE_TYPE_STRING) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGS", "Path must be string", nullptr));
  }

  const gchar *path = fl_value_get_string(args);
  g_autoptr(GFile) file = g_file_new_for_path(path);
  g_autofree gchar *uri = g_file_get_uri(file);
  g_autoptr(GError) error = nullptr;

  if (!g_app_info_launch_default_for_uri(uri, nullptr, &error)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("LAUNCH_FAILED", error->message, nullptr));
  }

  return FL_METHOD_RESPONSE(
      fl_method_success_response_new(fl_value_new_bool(true)));
}

// 3. Command ဖြင့် App ဖွင့်ရန် (e.g. "vlc", "code", "firefox")
FlMethodResponse *launch_app(FlValue *args) {
  if (fl_value_get_type(args) != FL_VALUE_TYPE_STRING) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGS", "Command must be string", nullptr));
  }

  const gchar *command = fl_value_get_string(args);
  g_autoptr(GError) error = nullptr;

  // Pure GLib standard Commandline AppInfo သုံးခြင်း
  g_autoptr(GAppInfo) app_info = g_app_info_create_from_commandline(
      command, nullptr, G_APP_INFO_CREATE_NONE, &error);

  if (app_info == nullptr) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "APP_NOT_FOUND", error ? error->message : "Failed to create app info",
        nullptr));
  }

  if (!g_app_info_launch(app_info, nullptr, nullptr, &error)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("LAUNCH_FAILED", error->message, nullptr));
  }

  return FL_METHOD_RESPONSE(
      fl_method_success_response_new(fl_value_new_bool(true)));
}

// 4. Installed System Apps စာရင်း ရယူရန် (Standard GAppInfo သာသုံးထားသည်)
FlMethodResponse *get_installed_apps() {
  GList *apps = g_app_info_get_all();
  g_autoptr(FlValue) result_list = fl_value_new_list();

  for (GList *l = apps; l != nullptr; l = l->next) {
    GAppInfo *app = G_APP_INFO(l->data);

    if (g_app_info_should_show(app)) {
      g_autoptr(FlValue) app_map = fl_value_new_map();

      const gchar *name = g_app_info_get_name(app);
      const gchar *executable = g_app_info_get_executable(app);

      // fl_value_set_string_take မှာ Value အတွက် fl_value_new_string ကို သုံးတာ မှန်ပါတယ်
      // သို့သော် fl_value_set_string ကို သုံးရင် key ရော value ရော plain string ပဲ ထည့်ရတာမို့
      // ပိုစိတ်ချရပါတယ်:

      fl_value_set_string(app_map, "name",
                          fl_value_new_string(name ? name : ""));
      fl_value_set_string(app_map, "executable",
                          fl_value_new_string(executable ? executable : ""));

      fl_value_append_take(result_list, g_steal_pointer(&app_map));
    }
  }

  g_list_free_full(apps, g_object_unref);

  // result_list ကို Steal လုပ်ပြီး ပို့ပေးရပါမယ်
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result_list));
}