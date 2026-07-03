#include "cpolycall.h"

#include <stdio.h>

int main(int argc, char **argv) {
    const char *config_path = argc > 1 ? argv[1] : "cpolycallrc";
    int status = cpolycall_run_config(config_path);

    if (status != 0) {
        fprintf(stderr, "cpolycall failed with status %d\n", status);
        return status;
    }

    puts("cpolycall: configuration started successfully");
    return 0;
}
