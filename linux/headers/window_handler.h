#pragma once

#include <flutter_linux/flutter_linux.h>

FlMethodResponse *get_window_size();
FlMethodResponse *set_window_size(FlValue *args);

FlMethodResponse *get_window_title();
FlMethodResponse *set_window_title(FlValue *args);

FlMethodResponse *set_fullscreen(FlValue *args);
FlMethodResponse *toggle_fullscreen();
FlMethodResponse *is_fullscreen();

FlMethodResponse *minimize_window();
FlMethodResponse *set_keep_above(FlValue *args);

FlMethodResponse *center_window();
FlMethodResponse *set_window_bordered(FlValue *args);

FlMethodResponse *set_min_window_size(FlValue *args);
FlMethodResponse *set_max_window_size(FlValue *args);
FlMethodResponse *set_window_size_limits(FlValue *args);
