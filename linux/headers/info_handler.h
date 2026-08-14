#pragma once

#include <flutter_linux/flutter_linux.h>
#include <sys/utsname.h>

FlMethodResponse *get_platform_version();
FlMethodResponse *get_app_info();
FlMethodResponse *get_os_release();
