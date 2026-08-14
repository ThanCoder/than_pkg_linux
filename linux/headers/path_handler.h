#pragma once
#include <flutter_linux/flutter_linux.h>

FlMethodResponse *get_application_documents_directory();
FlMethodResponse *get_temporary_directory();
FlMethodResponse *get_application_support_directory();
FlMethodResponse *get_downloads_directory();
FlMethodResponse *get_desktop_directory();
FlMethodResponse *get_pictures_directory();

FlMethodResponse *get_executable_path();
FlMethodResponse *get_working_directory();
