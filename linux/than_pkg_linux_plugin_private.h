#include <flutter_linux/flutter_linux.h>

#include "include/than_pkg_linux/than_pkg_linux_plugin.h"

// This file exposes some plugin internals for unit testing. See
// https://github.com/flutter/flutter/issues/88724 for current limitations
// in the unit-testable API.

// Handles the getPlatformVersion method call.
FlMethodResponse* get_platform_version();
FlMethodResponse* get_window_size();

FlMethodResponse* set_window_title(FlValue* args);
FlMethodResponse* set_fullscreen(FlValue* args);
FlMethodResponse* get_window_title();
FlMethodResponse* toggle_fullscreen();
FlMethodResponse* is_fullscreen();
FlMethodResponse* set_window_size(FlValue* args);
FlMethodResponse* center_window();
FlMethodResponse* set_window_bordered(FlValue* args);
FlMethodResponse* close_window();
FlMethodResponse* minimize_window();
FlMethodResponse* set_keep_above(FlValue* args);

// window close listener
FlMethodResponse* set_close_handler_listening(FlValue* args);