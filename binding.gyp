{
  "targets": [
    {
      "target_name": "test_uv_loop",
      "sources": [
        "test/test.c"
      ],
      "include_dirs": [
        "include",
        "<!(node -p \"require('node-addon-api').include_dir\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": [
        "NAPI_VERSION=<(napi_build_version)"
      ]
    }
  ]
}
