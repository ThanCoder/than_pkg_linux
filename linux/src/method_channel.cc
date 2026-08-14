#include "method_channel.h"
#include "info_handler.h"
#include "launcher_handler.h"
#include "path_handler.h"
#include "window_handler.h"
#include <cstring>

static void handle_method_call(FlMethodCall *method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar *method = fl_method_call_get_name(method_call);
  FlValue *args = fl_method_call_get_args(method_call);

  // =========================
  // Info
  // =========================

  if (strcmp(method, "getPlatformVersion") == 0) {
    response = get_platform_version();

  } else if (strcmp(method, "getAppInfo") == 0) {
    response = get_app_info();

  } else if (strcmp(method, "getOsRelease") == 0) {
    response = get_os_release();

    // =========================
    // Window
    // =========================

  } else if (strcmp(method, "getWindowSize") == 0) {
    response = get_window_size();

  } else if (strcmp(method, "setFullscreen") == 0) {
    response = set_fullscreen(args);

  } else if (strcmp(method, "setWindowTitle") == 0) {
    response = set_window_title(args);

  } else if (strcmp(method, "getWindowTitle") == 0) {
    response = get_window_title();

  } else if (strcmp(method, "isFullScreen") == 0) {
    response = is_fullscreen();

  } else if (strcmp(method, "toggleFullScreen") == 0) {
    response = toggle_fullscreen();

  } else if (strcmp(method, "setKeepAbove") == 0) {
    response = set_keep_above(args);

  } else if (strcmp(method, "minimizeWindow") == 0) {
    response = minimize_window();

  } else if (strcmp(method, "setWindowSize") == 0) {
    response = set_window_size(args);

  } else if (strcmp(method, "centerWindow") == 0) {
    response = center_window();

  } else if (strcmp(method, "setWindowBordered") == 0) {
    response = set_window_bordered(args);

  } else if (strcmp(method, "setMinWindowSize") == 0) {
    response = set_min_window_size(args);

  } else if (strcmp(method, "setMaxWindowSize") == 0) {
    response = set_max_window_size(args);

  } else if (strcmp(method, "setWindowSizeLimits") == 0) {
    response = set_window_size_limits(args);

    // =========================
    // Path
    // =========================

  } else if (strcmp(method, "get_application_documents_directory") == 0) {
    response = get_application_documents_directory();

  } else if (strcmp(method, "get_temporary_directory") == 0) {
    response = get_temporary_directory();

  } else if (strcmp(method, "get_application_support_directory") == 0) {
    response = get_application_support_directory();

  } else if (strcmp(method, "get_downloads_directory") == 0) {
    response = get_downloads_directory();

  } else if (strcmp(method, "get_desktop_directory") == 0) {
    response = get_desktop_directory();

  } else if (strcmp(method, "get_pictures_directory") == 0) {
    response = get_pictures_directory();

  } else if (strcmp(method, "get_executable_path") == 0) {
    response = get_executable_path();

  } else if (strcmp(method, "get_working_directory") == 0) {
    response = get_working_directory();

    // =========================
    // Launcher
    // =========================

  } else if (strcmp(method, "launch_url") == 0) {
    response = launch_url(args);

  } else if (strcmp(method, "launch_path") == 0) {
    response = launch_path(args);

  } else if (strcmp(method, "launch_app") == 0) {
    response = launch_app(args);

  } else if (strcmp(method, "get_installed_apps") == 0) {
    response = get_installed_apps();

    // =========================
    // Not implemented
    // =========================

  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

static void method_call_cb(FlMethodChannel *channel, FlMethodCall *method_call,
                           gpointer user_data) {

  handle_method_call(method_call);
}

void register_method_channel(FlPluginRegistrar *registrar) {
  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();

  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "than_pkg_linux", FL_METHOD_CODEC(codec));

  fl_method_channel_set_method_call_handler(channel, method_call_cb, nullptr,
                                            nullptr);
}