/**
 * Unit tests for get-uv-event-loop-napi.h
 *
 * This test suite verifies the functionality of the get_uv_event_loop
 * function with N-API.
 */

#include <stdio.h>
#include <assert.h>
#include <node_api.h>
#include <uv.h>
#include "../include/get-uv-event-loop-napi.h"

/* Test counter */
static int tests_passed = 0;
static int tests_failed = 0;

/* Test macros */
#define TEST(name) \
    static napi_value test_##name(napi_env env, napi_callback_info info); \
    static void run_test_##name(napi_env env) { \
        printf("Running test: %s\n", #name); \
        test_##name(env, NULL); \
    } \
    static napi_value test_##name(napi_env env, napi_callback_info info)

#define ASSERT(condition, message) \
    do { \
        if (condition) { \
            printf("  ✓ PASS: %s\n", message); \
            tests_passed++; \
        } else { \
            printf("  ✗ FAIL: %s\n", message); \
            tests_failed++; \
        } \
    } while (0)

#define RUN_TEST(name) run_test_##name(env)

/* Test: Getting UV event loop should return non-NULL */
TEST(get_uv_loop_not_null) {
    uv_loop_t* loop = get_uv_event_loop(env);
    ASSERT(loop != NULL, "get_uv_event_loop should return non-NULL");
    return NULL;
}

/* Test: UV loop should be valid and active */
TEST(uv_loop_is_valid) {
    uv_loop_t* loop = get_uv_event_loop(env);
    ASSERT(loop != NULL, "Loop should be non-NULL");

    /* Check if we can access loop structure - it should be alive */
    if (loop != NULL) {
        ASSERT(uv_loop_alive(loop) >= 0, "Loop should be alive or valid");
    }
    return NULL;
}

/* Test: Multiple calls should return same loop */
TEST(multiple_calls_same_loop) {
    uv_loop_t* loop1 = get_uv_event_loop(env);
    uv_loop_t* loop2 = get_uv_event_loop(env);

    ASSERT(loop1 != NULL, "First call should return non-NULL");
    ASSERT(loop2 != NULL, "Second call should return non-NULL");
    ASSERT(loop1 == loop2, "Multiple calls should return the same loop");
    return NULL;
}

/* Test: UV loop should match default loop for Node.js */
TEST(matches_default_loop) {
    uv_loop_t* loop = get_uv_event_loop(env);
    uv_loop_t* default_loop = uv_default_loop();

    ASSERT(loop != NULL, "get_uv_event_loop should return non-NULL");
    ASSERT(default_loop != NULL, "uv_default_loop should return non-NULL");

    /* In Node.js, the N-API loop should be the default loop */
    ASSERT(loop == default_loop, "N-API loop should match uv_default_loop");
    return NULL;
}

/* N-API module initialization that runs tests */
static napi_value RunTests(napi_env env, napi_callback_info info) {
    printf("\n");
    printf("===========================================\n");
    printf("Testing get-uv-event-loop-napi.h\n");
    printf("===========================================\n\n");

    RUN_TEST(get_uv_loop_not_null);
    printf("\n");

    RUN_TEST(uv_loop_is_valid);
    printf("\n");

    RUN_TEST(multiple_calls_same_loop);
    printf("\n");

    RUN_TEST(matches_default_loop);
    printf("\n");

    printf("===========================================\n");
    printf("Test Results:\n");
    printf("  Passed: %d\n", tests_passed);
    printf("  Failed: %d\n", tests_failed);
    printf("  Total:  %d\n", tests_passed + tests_failed);
    printf("===========================================\n\n");

    napi_value result;
    napi_create_int32(env, tests_failed > 0 ? 1 : 0, &result);
    return result;
}

/* Module initialization */
NAPI_MODULE_INIT() {
    napi_value fn;
    napi_create_function(env, NULL, 0, RunTests, NULL, &fn);
    napi_set_named_property(env, exports, "runTests", fn);
    return exports;
}
