'use strict';

const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');

const binding = require('..');

for (const [name, file] of Object.entries(binding)) {
  assert.equal(path.isAbsolute(file), true, `${name} must be an absolute path`);
  assert.equal(fs.existsSync(file), true, `${name} does not exist: ${file}`);
}

assert.equal(
  require.resolve('@obinexusltd/cpolycall/src/cpolycall.c'),
  binding.source
);
assert.equal(
  require.resolve('@obinexusltd/cpolycall/include/cpolycall.h'),
  binding.publicHeader
);

console.log('cpolycall npm package test: PASS');
