# cpolycall tests

`cpolycall_test.c` links the real C adapter against a mock libpolycall FFI. It
verifies that the adapter forwards the configuration path, fixes `run=1`, and
propagates both success and failure statuses unchanged.

Run the native and npm package tests with `npm test`. CMake users can also run
`ctest --test-dir <build-directory> --output-on-failure`.
