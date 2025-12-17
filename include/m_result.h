#ifndef MODERNC_RESULT_H
#define MODERNC_RESULT_H

#include "../include/m_var.h"

/// Error value that can accompany an error Status
typedef struct {
    Status code;    /// status code (same as Result.status)
    String msg;     /// optional owned message (maybe empty)
} Error;

/// Result type for functions that can succeed or fail, optionally carrying an Error
typedef struct {
    Status status;  /// success or error status
    Error err;      /// error details if status != Status_Ok
} Result;

#define IsOk(r) ((r).status == Status_Ok)      /// check for success
#define IsErr(r) ((r).status != Status_Ok)     /// check for error

/// Result type with a value
#define ResultOf(T) \
struct { \
    Status status; \
    Error err; \
    T value; \
}

#define OkVal(v)   { Status_Ok, { Status_Ok, (String){0} }, (v) }    /// success with value
#define ErrVal(e)  { (e), { (e), (String){0} } }           /// error result

typedef ResultOf(String) ResultString;

/// Unwrap a Result (with value), panic if it's an error
#define unwrap(r) \
({ \
    __auto_type _r = (r); \
    if (_r.status != Status_Ok) { \
        if (_r.err.msg.data) { \
            panic(_r.err.msg.data); \
        } else { \
            panic("unwrap on Err"); \
        } \
    } \
    _r.value; \
})

/// Unwrap a Result (with value), return default value if it's an error
#define unwrap_or(r, def) \
({ \
    __auto_type _r = (r); \
    (_r.status == Status_Ok) ? _r.value : (def); \
})

/// Try a Result, return if it's an error
#define Try(r) \
do { \
    __auto_type _r = (r); \
    if (_r.status != Status_Ok) { \
        return _r; \
    } \
} while (0)

/// Try a Result with value, return if it's an error, otherwise get the value
#define TryVal(r) \
({ \
    __auto_type _r = (r); \
    if (_r.status != Status_Ok) { \
        return _r; \
    } \
    _r.value; \
})

noreturn void panic(const char *msg);
ResultString f(String s);
Result ErrWithMsg(Status code, String msg);
Result Ok();
Result Err(Status st);

#endif // MODERNC_RESULT_H
