/**
 * JavaScript test runner for get-uv-event-loop-napi.h
 */

const addon = require('../build/Release/test_uv_loop.node');

console.log('Running get-uv-event-loop-napi tests...\n');
const exitCode = addon.runTests();
process.exit(exitCode);
