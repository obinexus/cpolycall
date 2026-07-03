# cpolycall

Reference C binding for libpolycall 1.5.0, published as
`@obinexusltd/cpolycall`.

`cpolycall` is the smallest native adapter in the binding family. It forwards
the caller's configuration path to
`polycall_ffi_run_config(config_path, 1)`, returns the core status unchanged,
and contains no configuration parser or runtime implementation.

## C API

```c
#include <cpolycall.h>

int status = cpolycall_run_config("cpolycallrc");
if (status != 0) {
    /* Apply the host application's error policy. */
}
```

The declaration is in [`include/cpolycall.h`](include/cpolycall.h), and the
entire implementation is in [`src/cpolycall.c`](src/cpolycall.c).

## Install from npm

```sh
npm install @obinexusltd/cpolycall
```

This is a source package for native build tooling. Its CommonJS entry point
exposes absolute paths to the packaged artifacts:

```js
const cpolycall = require('@obinexusltd/cpolycall');

console.log(cpolycall.source);
console.log(cpolycall.publicHeader);
console.log(cpolycall.ffiHeader);
console.log(cpolycall.cmakeLists);
console.log(cpolycall.config);
```

The npm tarball includes `src/`, `include/`, `generated/`, `cmake/`, examples,
tests, scripts, the Makefile, CMake project, manifest, and runtime
configuration. Generated platform binaries are excluded.

## Build and test

Using Make:

```sh
make
make test
make verify-dry
```

The equivalent npm commands are:

```sh
npm run build
npm test
npm run verify
```

Using CMake and CTest:

```sh
cmake -S . -B cmake-build -DBUILD_TESTING=ON
cmake --build cmake-build
ctest --test-dir cmake-build --output-on-failure
```

The tests link the real adapter against a mock core and verify the forwarded
path, fixed `run=1` argument, and unchanged success and failure statuses.

## CMake consumption

Install the library and its CMake package files:

```sh
cmake --install cmake-build --prefix /desired/prefix
```

Then consume the exported target alongside libpolycall:

```cmake
find_package(cpolycall 1 CONFIG REQUIRED)
find_package(polycall 1.5 CONFIG REQUIRED)

target_link_libraries(my_app PRIVATE
    cpolycall::cpolycall
    polycall::polycall)
```

The static adapter intentionally leaves `polycall_ffi_run_config` to be
resolved by the libpolycall v1.5 library at final link time.

## Run the example

Point the link step at a libpolycall v1.5 build that exports the FFI symbol:

```sh
make example POLYCALL_LDFLAGS="-L/path/to/libpolycall/lib -lpolycall"
```

The example accepts an optional configuration path and defaults to
`cpolycallrc`.

## Publishing

Inspect the package and publish the public npm scope:

```sh
npm pack --dry-run
npm publish --access public
```

Publishing is not performed automatically by build or test scripts.

## Author

Nnamdi Michael Okpala — <okpalan@protonmail.com>
