#include <stdio.h>
#include "../include/modern.h"

Result maybe_divide_err(const i32 a, const i32 b, i32 *out) {
    if (!out) return Err(Status_Invalid);
    if (b == 0) {
        String msg = string_from_slice(str_lit("division by zero"));
        return ErrWithMsg(Status_Invalid, msg);
    }
    *out = a / b;
    return Ok();
}

int main(void) {
    i32 q;
    Result r = maybe_divide_err(10, 2, &q);
    if (IsOk(r)) {
        printf("10 / 2 = %d\n", q);
    } else {
        printf("error: %s\n", status_to_str(r.status));
        if (r.err.msg.data) {
            printf("message: %s\n", r.err.msg.data);
            string_free(&r.err.msg);
        }
    }

    r = maybe_divide_err(1, 0, &q);
    if (IsOk(r)) {
        printf("1 / 0 = %d\n", q);
    } else {
        printf("error: %s\n", status_to_str(r.status));
        if (r.err.msg.data) {
            printf("message: %s\n", r.err.msg.data);
            string_free(&r.err.msg);
        }
    }

    return Status_Ok;
}
