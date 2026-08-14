#pragma once

#include <flutter_linux/flutter_linux.h>

FlMethodResponse *launch_url(FlValue *args);
FlMethodResponse *launch_path(FlValue *args);
FlMethodResponse *launch_app(FlValue *args);
FlMethodResponse *get_installed_apps();
