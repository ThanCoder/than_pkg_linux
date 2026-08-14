#include "window_handler.h"
#include "than_globals.h"
#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>

#include <cstdio>
#include <cstring>

FlMethodResponse *set_window_size_limits(FlValue *args) {
  if (g_toplevel_window == nullptr) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "WINDOW_NOT_FOUND", "Toplevel window is not available.", nullptr));
  }

  if (args == nullptr || fl_value_get_type(args) != FL_VALUE_TYPE_MAP) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGUMENT", "Arguments must be a map.", nullptr));
  }

  FlValue *min_width_value = fl_value_lookup_string(args, "minWidth");
  FlValue *min_height_value = fl_value_lookup_string(args, "minHeight");
  FlValue *max_width_value = fl_value_lookup_string(args, "maxWidth");
  FlValue *max_height_value = fl_value_lookup_string(args, "maxHeight");

  if (min_width_value == nullptr || min_height_value == nullptr ||
      max_width_value == nullptr || max_height_value == nullptr ||
      fl_value_get_type(min_width_value) != FL_VALUE_TYPE_INT ||
      fl_value_get_type(min_height_value) != FL_VALUE_TYPE_INT ||
      fl_value_get_type(max_width_value) != FL_VALUE_TYPE_INT ||
      fl_value_get_type(max_height_value) != FL_VALUE_TYPE_INT) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGUMENT", "All size values must be integers.", nullptr));
  }

  const int min_width = fl_value_get_int(min_width_value);
  const int min_height = fl_value_get_int(min_height_value);
  const int max_width = fl_value_get_int(max_width_value);
  const int max_height = fl_value_get_int(max_height_value);

  if (min_width <= 0 || min_height <= 0 || max_width <= 0 || max_height <= 0) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_SIZE", "All size values must be greater than zero.", nullptr));
  }

  if (min_width > max_width || min_height > max_height) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_SIZE_LIMITS",
        "Minimum size cannot be greater than maximum size.", nullptr));
  }

  GdkGeometry geometry = {};

  geometry.min_width = min_width;
  geometry.min_height = min_height;
  geometry.max_width = max_width;
  geometry.max_height = max_height;

  gtk_window_set_geometry_hints(
      GTK_WINDOW(g_toplevel_window), nullptr, &geometry,
      static_cast<GdkWindowHints>(GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE));

  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

FlMethodResponse *set_max_window_size(FlValue *args) {
  if (g_toplevel_window == nullptr) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "WINDOW_NOT_FOUND", "Toplevel window is not available.", nullptr));
  }

  if (args == nullptr || fl_value_get_type(args) != FL_VALUE_TYPE_MAP) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGUMENT", "Arguments must be a map.", nullptr));
  }

  FlValue *width_value = fl_value_lookup_string(args, "width");
  FlValue *height_value = fl_value_lookup_string(args, "height");

  if (width_value == nullptr || height_value == nullptr ||
      fl_value_get_type(width_value) != FL_VALUE_TYPE_INT ||
      fl_value_get_type(height_value) != FL_VALUE_TYPE_INT) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGUMENT", "width and height must be integers.", nullptr));
  }

  const int width = fl_value_get_int(width_value);
  const int height = fl_value_get_int(height_value);

  if (width <= 0 || height <= 0) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_SIZE", "width and height must be greater than zero.",
        nullptr));
  }

  GdkGeometry geometry = {};
  geometry.max_width = width;
  geometry.max_height = height;

  gtk_window_set_geometry_hints(GTK_WINDOW(g_toplevel_window), nullptr,
                                &geometry, GDK_HINT_MAX_SIZE);

  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

FlMethodResponse *set_min_window_size(FlValue *args) {
  if (g_toplevel_window == nullptr) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "WINDOW_NOT_FOUND", "Toplevel window is not available.", nullptr));
  }

  if (args == nullptr || fl_value_get_type(args) != FL_VALUE_TYPE_MAP) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGUMENT", "Arguments must be a map.", nullptr));
  }

  FlValue *width_value = fl_value_lookup_string(args, "width");

  FlValue *height_value = fl_value_lookup_string(args, "height");

  if (width_value == nullptr || height_value == nullptr ||
      fl_value_get_type(width_value) != FL_VALUE_TYPE_INT ||
      fl_value_get_type(height_value) != FL_VALUE_TYPE_INT) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_ARGUMENT", "width and height must be integers.", nullptr));
  }

  const int width = fl_value_get_int(width_value);
  const int height = fl_value_get_int(height_value);

  if (width <= 0 || height <= 0) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "INVALID_SIZE", "width and height must be greater than zero.",
        nullptr));
  }

  GdkGeometry geometry = {};
  geometry.min_width = width;
  geometry.min_height = height;

  gtk_window_set_geometry_hints(GTK_WINDOW(g_toplevel_window), nullptr,
                                &geometry, GDK_HINT_MIN_SIZE);

  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

FlMethodResponse *get_window_size() {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  gint width = 0;
  gint height = 0;
  // Window ရဲ့ လက်ရှိ size ကို ယူခြင်း
  gtk_window_get_size(GTK_WINDOW(g_toplevel_window), &width, &height);

  g_autoptr(FlValue) result = fl_value_new_map();
  fl_value_set_string_take(result, "width", fl_value_new_int(width));
  fl_value_set_string_take(result, "height", fl_value_new_int(height));

  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

FlMethodResponse *get_window_title() {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  const gchar *title = gtk_window_get_title(GTK_WINDOW(g_toplevel_window));
  // Title မရှိရင် empty string ပြန်မယ်
  g_autoptr(FlValue) result = fl_value_new_string(title ? title : "");

  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

// 2. Window Title ကို ပြောင်းလဲခြင်း
FlMethodResponse *set_window_title(FlValue *args) {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  // Dart ဘက်က ပို့လိုက်တဲ့ title string ကို စစ်ဆေးခြင်း
  if (fl_value_get_type(args) != FL_VALUE_TYPE_STRING) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "bad_arguments", "Title must be a string", nullptr));
  }

  const gchar *new_title = fl_value_get_string(args);
  gtk_window_set_title(GTK_WINDOW(g_toplevel_window), new_title);

  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

// Fullscreen အဖွင့် / အပိတ် လုပ်ခြင်း (bool argument လက်ခံသည်)
FlMethodResponse *set_fullscreen(FlValue *args) {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  // Dart ဘက်က ပို့လိုက်တဲ့ argument သည် boolean ဟုတ်မဟုတ် စစ်ဆေးခြင်း
  if (fl_value_get_type(args) != FL_VALUE_TYPE_BOOL) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "bad_arguments", "Argument must be a boolean", nullptr));
  }

  // true သို့မဟုတ် false တန်ဖိုးကို ယူခြင်း
  auto enable = fl_value_get_bool(args);

  if (enable) {
    gtk_window_fullscreen(GTK_WINDOW(g_toplevel_window));
  } else {
    gtk_window_unfullscreen(GTK_WINDOW(g_toplevel_window));
  }

  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

// 3. Fullscreen ကို Toggle (အဖွင့်/အပိတ်) လုပ်ခြင်း
FlMethodResponse *toggle_fullscreen() {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(g_toplevel_window));
  if (gdk_window != nullptr) {
    GdkWindowState state = gdk_window_get_state(gdk_window);

    // လက်ရှိ fullscreen ဖြစ်နေရင် ပုံမှန် window ပြန်လုပ်၊ မဖြစ်သေးရင် fullscreen လုပ်
    if (state & GDK_WINDOW_STATE_FULLSCREEN) {
      gtk_window_unfullscreen(GTK_WINDOW(g_toplevel_window));
    } else {
      gtk_window_fullscreen(GTK_WINDOW(g_toplevel_window));
    }
  }

  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

FlMethodResponse *is_fullscreen() {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(g_toplevel_window));
  bool isFullscreen = false;

  if (gdk_window != nullptr) {
    GdkWindowState state = gdk_window_get_state(gdk_window);
    isFullscreen = (state & GDK_WINDOW_STATE_FULLSCREEN) != 0;
  }

  auto val = fl_value_new_bool(isFullscreen);

  return FL_METHOD_RESPONSE(fl_method_success_response_new(val));
}

// Window ကို အောက်ချခြင်း (Minimize)
FlMethodResponse *minimize_window() {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }
  gtk_window_iconify(GTK_WINDOW(g_toplevel_window));
  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

// Window ကို အမြဲတမ်း အပေါ်ဆုံးမှာ ထားခြင်း/ဖြုတ်ခြင်း (Always on Top)
FlMethodResponse *set_keep_above(FlValue *args) {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }
  if (fl_value_get_type(args) != FL_VALUE_TYPE_BOOL) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "bad_arguments", "Arg must be bool", nullptr));
  }

  auto keep_above = fl_value_get_bool(args);
  gtk_window_set_keep_above(GTK_WINDOW(g_toplevel_window), keep_above);

  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

// 1. Window ရဲ့ Size ကို စိတ်ကြိုက် သတ်မှတ်ခြင်း
FlMethodResponse *set_window_size(FlValue *args) {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  // Dart ကနေ Map အနေနဲ့ ပို့ပေးရပါမယ် (ဥပမာ - {"width": 800, "height": 600})
  if (fl_value_get_type(args) != FL_VALUE_TYPE_MAP) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "bad_arguments", "Args must be a Map", nullptr));
  }

  FlValue *width_val = fl_value_lookup_string(args, "width");
  FlValue *height_val = fl_value_lookup_string(args, "height");

  if (width_val == nullptr || height_val == nullptr) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "bad_arguments", "Missing width or height", nullptr));
  }

  gint width = fl_value_get_int(width_val);
  gint height = fl_value_get_int(height_val);

  gtk_window_resize(GTK_WINDOW(g_toplevel_window), width, height);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

// 2. Window ကို Screen ရဲ့ အလယ်တည့်တည့်သို့ ရွှေ့ခြင်း
FlMethodResponse *center_window() {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  // GTK ရဲ့ built-in အလယ်ပို့တဲ့ စနစ်ကို သုံးခြင်း
  gtk_window_set_position(GTK_WINDOW(g_toplevel_window), GTK_WIN_POS_CENTER);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}

// 3. Window ရဲ့ Default ဘောင် (Title Bar) ကို ဖျောက်ခြင်း/ပြခြင်း
// Custom Title Bar ကို Flutter ဘက်ကနေ ကိုယ်တိုင် Design ဆွဲချင်ရင် သုံးပါတယ်
FlMethodResponse *set_window_bordered(FlValue *args) {
  if (g_toplevel_window == nullptr || !GTK_IS_WINDOW(g_toplevel_window)) {
    return FL_METHOD_RESPONSE(
        fl_method_error_response_new("no_window", "Window not found", nullptr));
  }

  if (fl_value_get_type(args) != FL_VALUE_TYPE_BOOL) {
    return FL_METHOD_RESPONSE(fl_method_error_response_new(
        "bad_arguments", "Arg must be a boolean", nullptr));
  }

  gboolean bordered = fl_value_get_bool(args);
  gtk_window_set_decorated(GTK_WINDOW(g_toplevel_window), bordered);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
}