'use strict';

const path = require('node:path');

const fromPackageRoot = (...segments) => path.join(__dirname, ...segments);

module.exports = Object.freeze({
  root: __dirname,
  source: fromPackageRoot('src', 'cpolycall.c'),
  publicHeader: fromPackageRoot('include', 'cpolycall.h'),
  ffiHeader: fromPackageRoot('generated', 'polycall', 'polycall_ffi.h'),
  cmakeLists: fromPackageRoot('CMakeLists.txt'),
  config: fromPackageRoot('cpolycallrc'),
  manifest: fromPackageRoot('polycall-binding.json')
});
