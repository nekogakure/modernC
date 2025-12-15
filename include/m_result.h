#ifndef MODERNC_RESULT_H
#define MODERNC_RESULT_H

#include "../include/m_var.h"

/// Result type for functions that can succeed or fail
typedef struct {
	Status status;
} Result;

#define Ok()		((Result){ .status = Status_Ok })	/// success result
#define Err(code)	((Result){ .status = (code) })		/// error result

#define is_ok(r)	((r).status == Status_Ok)		/// check for success
#define is_err(r)	((r).status != Status_Ok)		/// check for error

/// Result type with a value
#define ResultOf(T) \
struct { \
	Status status; \
	T value; \
}

#define OkVal(v)	{ .status = Status_Ok, .value = (v) }	/// success with value
#define ErrVal(e)	{ .status = (e) }			/// error result

typedef ResultOf(String) ResultString;

/// Unwrap a Result, panic if it's an error
#define unwrap(r) \
({ \
	__auto_type _r = (r); \
	if (_r.status != Status_Ok) { \
		panic("unwrap on Err"); \
	} \
	_r.value; \
})

/// Unwrap a Result, return default value if it's an error
#define unwrap_or(r, def) \
({ \
	__auto_type _r = (r); \
	(_r.status == Status_Ok) ? _r.value : (def); \
})

/// Try a Result, return if it's an error
#define TRY(r) \
do { \
	__auto_type _r = (r); \
	if (_r.status != Status_Ok) { \
		return _r; \
	} \
} while (0)

/// Try a Result with value, return if it's an error, otherwise get the value
#define TRY_VAL(r) \
({ \
	__auto_type _r = (r); \
	if (_r.status != Status_Ok) { \
		return _r; \
	} \
	_r.value; \
})

noreturn void panic(const char *msg);
ResultString f(String s);

#endif // MODERNC_RESULT_H
