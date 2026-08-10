#include <flutter_linux/flutter_linux.h>

#include "include/than_pkg_linux/than_pkg_linux_plugin.h"

// This file exposes some plugin internals for unit testing. See
// https://github.com/flutter/flutter/issues/88724 for current limitations
// in the unit-testable API.

// Handles the getPlatformVersion method call.
/// pkginfo
FlMethodResponse *get_os_release();
FlMethodResponse *get_platform_version();
FlMethodResponse *get_app_info();

// channel
FlMethodResponse *get_window_size();
FlMethodResponse *set_window_title(FlValue *args);
FlMethodResponse *set_fullscreen(FlValue *args);
FlMethodResponse *get_window_title();
FlMethodResponse *toggle_fullscreen();
FlMethodResponse *is_fullscreen();
FlMethodResponse *set_window_size(FlValue *args);
FlMethodResponse *center_window();
FlMethodResponse *set_window_bordered(FlValue *args);
FlMethodResponse *close_window();
FlMethodResponse *minimize_window();
FlMethodResponse *set_keep_above(FlValue *args);

// window close listener
FlMethodResponse *set_close_handler_listening(FlValue *args);

/********************* Path Provider Funcs **************************** */
FlMethodResponse *get_application_documents_directory();
FlMethodResponse *get_temporary_directory();
FlMethodResponse *get_application_support_directory();
FlMethodResponse *get_downloads_directory();
FlMethodResponse *get_desktop_directory();
FlMethodResponse *get_pictures_directory();

FlMethodResponse *get_executable_path();
FlMethodResponse *get_working_directory();