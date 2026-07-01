/*
 * cpolycall - the C reference adapter for libpolycall.
 *
 * The C "binding" is the thinnest possible adapter: it simply uses the native
 * adapter base (polycall_adapter.h) which wraps the public core API. It proves
 * the boundary from the same language the core is written in, and is the
 * template every other native binding (C++, Objective-C, Fortran, Rust FFI)
 * mirrors.
 *
 * Build (after the core is built):
 *   cc -I../../include cpolycall.c ../../build/libpolycall.a -o cpolycall
 * Run:
 *   ./cpolycall ../cpolycallrc
 */
#include "polycall/polycall_adapter.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    polycall_adapter_t a;
    const char        *cfg = (argc > 1) ? argv[1] : "cpolycallrc";
    int                rc;

    rc = polycall_adapter_open(&a, "c", "cpolycallrc");
    if (rc != POLYCALL_OK) {
        fprintf(stderr, "cpolycall: open failed (%s)\n", polycall_status_str(rc));
        return rc;
    }

    rc = polycall_adapter_load(&a, cfg);
    if (rc != POLYCALL_OK) {
        fprintf(stderr, "cpolycall: %s\n", polycall_last_error(a.ctx));
        polycall_adapter_close(&a);
        return rc;
    }

    polycall_adapter_inspect(&a);
    rc = polycall_adapter_run(&a);
    polycall_adapter_close(&a);
    return rc;
}
