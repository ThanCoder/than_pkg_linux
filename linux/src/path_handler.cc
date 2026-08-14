#include "path_handler.h"
#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>

#include <cstdio>
#include <cstring>

// 1. Documents Directory (~/Documents)
FlMethodResponse *get_application_documents_directory() {
  const gchar *path = g_get_user_special_dir(G_USER_DIRECTORY_DOCUMENTS);
  if (path == nullptr)
    path = g_get_home_dir();

  g_autoptr(FlValue) result = fl_value_new_string(path);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// 2. Temporary / Cache Directory (~/.cache သို့မဟုတ် /tmp)
FlMethodResponse *get_temporary_directory() {
  const gchar *path = g_get_user_cache_dir();
  if (path == nullptr)
    path = g_get_tmp_dir();

  g_autoptr(FlValue) result = fl_value_new_string(path);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// 3. Application Support / Config Directory (~/.config)
FlMethodResponse *get_application_support_directory() {
  const gchar *path = g_get_user_config_dir();
  if (path == nullptr)
    path = g_get_home_dir();

  g_autoptr(FlValue) result = fl_value_new_string(path);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// 4. Downloads Directory (~/Downloads)
FlMethodResponse *get_downloads_directory() {
  const gchar *path = g_get_user_special_dir(G_USER_DIRECTORY_DOWNLOAD);
  if (path == nullptr)
    path = g_get_home_dir();

  g_autoptr(FlValue) result = fl_value_new_string(path);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// 5. Desktop Directory (~/Desktop)
FlMethodResponse *get_desktop_directory() {
  const gchar *path = g_get_user_special_dir(G_USER_DIRECTORY_DESKTOP);
  if (path == nullptr)
    path = g_get_home_dir();

  g_autoptr(FlValue) result = fl_value_new_string(path);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// 6. Pictures Directory (~/Pictures)
FlMethodResponse *get_pictures_directory() {
  const gchar *path = g_get_user_special_dir(G_USER_DIRECTORY_PICTURES);
  if (path == nullptr)
    path = g_get_home_dir();

  g_autoptr(FlValue) result = fl_value_new_string(path);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

/********************* Path Funcs **************************** */

// 1. Get Executable Path (e.g.,
// /home/user/my_app/build/linux/x64/debug/bundle/my_app)
FlMethodResponse *get_executable_path() {
  char path[1024] = {0};

  // Read the symbolic link /proc/self/exe on Linux
  ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);
  if (count == -1) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "PATH_ERROR", "Failed to read /proc/self/exe link", nullptr));
  }

  path[count] = '\0'; // Null-terminate the path string

  g_autoptr(FlValue) result = fl_value_new_string(path);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// 2. Get Current Working Directory (e.g., /home/user/my_app)
FlMethodResponse *get_working_directory() {
  g_autofree gchar *cwd = g_get_current_dir();

  if (cwd == nullptr) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "CWD_ERROR", "Failed to get current working directory", nullptr));
  }

  g_autoptr(FlValue) result = fl_value_new_string(cwd);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}