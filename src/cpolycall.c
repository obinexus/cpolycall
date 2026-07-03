#include "cpolycall.h"

#include <polycall/polycall_ffi.h>

int cpolycall_run_config(const char *config_path) {
    return polycall_ffi_run_config(config_path, 1);
}
