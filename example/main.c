#include "../include/modern.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int tests_run = 0;
static int failures = 0;

static void fail(const char *msg) {
    fprintf(stderr, "FAIL: %s\n", msg);
    failures++;
}

static void pass(const char *msg) {
    printf("ok: %s\n", msg);
}

static void assert_true(const char *name, const boolean cond) {
    tests_run++;
    if (!cond) fail(name);
    else pass(name);
}

static void assert_strslice_eq(const char *name, const StrSlice a, const StrSlice b) {
    tests_run++;
    if (!str_eq(a, b)) {
        const let as = (char*)malloc(a.len + 1);
        const let bs = (char*)malloc(b.len + 1);
        memcpy(as, a.data, a.len); as[a.len] = '\0';
        memcpy(bs, b.data, b.len); bs[b.len] = '\0';
        fprintf(stderr, "FAIL: %s - expected '%s' == '%s'\n", name, as, bs);
        free(as); free(bs);
        failures++;
    } else {
        pass(name);
    }
}

/* Test: StrSlice utilities */
static int test_str_slice_and_eq(void) {
    const let a = str_lit("hello");
    const let b = str_slice("hello", 5);
    assert_strslice_eq("str_lit == str_slice", a, b);

    const let sub = str_sub(a, 1, 3); // "ell"
    const let exp = str_lit("ell");
    assert_strslice_eq("str_sub middle", sub, exp);

    const let sub0 = str_sub(a, 0, 2); // "he"
    assert_strslice_eq("str_sub start", sub0, str_lit("he"));

    const let sub_tail = str_sub(a, 4, 10); // "o"
    assert_strslice_eq("str_sub tail", sub_tail, str_lit("o"));

    const let sub_out = str_sub(a, 10, 5); // out of range -> empty
    assert_strslice_eq("str_sub out_of_range", sub_out, str_lit(""));

    return 0;
}

static int test_string_ops(void) {
    let s = string_new();
    assert_true("string_new len==0", s.len == 0);

    let st = string_push(&s, 'a');
    assert_true("string_push ok 1", st == Status_Ok);
    st = string_push(&s, 'b');
    assert_true("string_push ok 2", st == Status_Ok);
    st = string_push(&s, 'c');
    assert_true("string_push ok 3", st == Status_Ok);

    const let ss = string_as_slice(&s);
    assert_strslice_eq("string_as_slice content", ss, str_lit("abc"));

    let from = string_from_slice(str_lit("xyz"));
    assert_strslice_eq("string_from_slice", string_as_slice(&from), str_lit("xyz"));

    st = string_append(&s, string_as_slice(&from));
    assert_true("string_append ok", st == Status_Ok);
    assert_strslice_eq("string_append content", string_as_slice(&s), str_lit("abcxyz"));

    string_free(&s);
    string_free(&from);

    return 0;
}

static Result test_vec_ops(void) {
    Vec(i32) v;
    v.data = nullptr;
    v.len = 0;
    v.cap = 0;
    // push several elements to trigger growth
    for (int i = 0; i < 10; i++) {
        vec_push(v, i);
    }
    // check length
    if (vec_len(v) != 10) return Err(Status_Err);

    // check content LIFO by manual pop without using vec_pop macro
    for (int i = 9; i >= 0; i--) {
        if (v.len == 0) return Err(Status_Err);
        const let val = v.data[--v.len];
        if (val != i) return Err(Status_Err);
    }

    // now empty
    if (v.len != 0) return Err(Status_Err);

    vec_free(v);
    return Ok();
}

/* Test: Result and Option simple usage */
static int test_result_and_option(void) {
    let s = string_from_slice(str_lit("value"));
    const let r = f(s);
    assert_true("f() is_ok", is_ok(r));
    // unwrap_or with default
    let def = string_from_slice(str_lit("def"));
    const let got = unwrap_or(r, def);
    assert_strslice_eq("unwrap_or value", string_as_slice(&got), string_as_slice(&s));
    string_free(&s);
    string_free(&def);
    return 0;
}

int main(const int argc, char **argv) {
    (void)argc; (void)argv;

    printf("Running modern.h tests...\n");

    test_str_slice_and_eq();
    test_string_ops();

    const let vr = test_vec_ops();
    tests_run++;
    if (is_err(vr)) {
        fail("vec operations");
    } else {
        pass("vec operations");
    }

    test_result_and_option();

    printf("\nSummary: tests run=%d, failures=%d\n", tests_run, failures);
    return failures;
}