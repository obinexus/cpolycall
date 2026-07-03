#ifndef CPOLYCALL_H
#define CPOLYCALL_H

#ifdef __cplusplus
extern "C" {
#endif

#define CPOLYCALL_VERSION_MAJOR 1
#define CPOLYCALL_VERSION_MINOR 0
#define CPOLYCALL_VERSION_PATCH 0

/*
 * Run libpolycall with the supplied read-only C configuration.
 *
 * The return value is the unmodified status from
 * polycall_ffi_run_config(config_path, 1).
 */
int cpolycall_run_config(const char *config_path);

#ifdef __cplusplus
}
#endif

#endif /* CPOLYCALL_H */
