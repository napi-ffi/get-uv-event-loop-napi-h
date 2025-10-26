@napi-ffi/get-uv-event-loop-napi-h
===================================
### C function to get the current libuv event loop for N-API

[![CI](https://github.com/napi-ffi/get-uv-event-loop-napi-h/actions/workflows/ci.yml/badge.svg)](https://github.com/napi-ffi/get-uv-event-loop-napi-h/actions/workflows/ci.yml)
[![NPM Version](https://img.shields.io/npm/v/@napi-ffi/get-uv-event-loop-napi-h.svg?style=flat)](https://npmjs.org/package/@napi-ffi/get-uv-event-loop-napi-h)
[![NPM Downloads](https://img.shields.io/npm/dm/@napi-ffi/get-uv-event-loop-napi-h.svg?style=flat)](https://npmjs.org/package/@napi-ffi/get-uv-event-loop-napi-h)

> Forked from [node-ffi-napi/get-uv-event-loop-napi-h](https://github.com/node-ffi-napi/get-uv-event-loop-napi-h) to maintain and modernize the project while preserving the original APIs.

Installation
------------

Install with `npm`:

``` bash
$ npm install @napi-ffi/get-uv-event-loop-napi-h
```

Usage
-----

In your `binding.gyp`:

```python
    'include_dirs': ["<!@(node -p \"require('@napi-ffi/get-uv-event-loop-napi-h').include\")"],
```

(Just have `"<!@(node -p \"require('@napi-ffi/get-uv-event-loop-napi-h').include\")"` somewhere in that list, ok?)

In your C code:

```c
#include <get-uv-event-loop-napi.h>

uv_loop_t* loop = get_uv_event_loop(env);
```
