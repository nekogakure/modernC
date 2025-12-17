#ifndef MODERNC_VAR_H
#define MODERNC_VAR_H

#include <stdint.h>

typedef int8_t i8; /// 8-bit signed integer
typedef int16_t i16; /// 16-bit signed integer
typedef int32_t i32; /// 32-bit signed integer
typedef int64_t i64; /// 64-bit signed integer

typedef uint8_t u8; /// 8-bit unsigned integer
typedef uint16_t u16; /// 16-bit unsigned integer
typedef uint32_t u32; /// 32-bit unsigned integer
typedef uint64_t u64; /// 64-bit unsigned integer

typedef intptr_t isize; /// Signed integer type capable of holding a pointer
typedef uintptr_t usize; /// Unsigned integer type capable of holding a pointer

typedef float f32; /// 32-bit floating point
typedef double f64; /// 64-bit floating point

#define let __auto_type /// auto type inference

/// Read-only string slice
typedef struct {
	const char *data; /// borrowed, read-only, not null
	usize len; /// length of the string
} StrSlice;

/// Mutable string
typedef struct {
	char *data; /// owned, mutable, null-terminated
	usize len; /// current length of the string
	usize cap; /// capacity of the string
} String;


typedef unsigned char boolean; /// Boolean type
#ifndef true
#define true  1
#endif
#ifndef false
#define false 0
#endif

/// Status codes (Use Result if possible)
typedef enum {
	Status_Ok = 0, /// Operation successful
	Status_Err = -1, /// Generic error
	Status_Nomem = -2, /// Out of memory
	Status_Invalid = -3, /// Invalid argument
} Status;

#define pure        __attribute__((pure))
#define const_fn    __attribute__((const))
#define noreturn    __attribute__((noreturn))
#define unused      __attribute__((unused))
#define packed      __attribute__((packed))
#define aligned(x) __attribute__((aligned(x)))
#define deprecated  __attribute__((deprecated))
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

StrSlice str_slice(const char *s, usize len);

boolean str_eq(StrSlice a, StrSlice b);

StrSlice str_sub(StrSlice s, usize pos, usize len);

String string_new(void);

void string_free(String *s);

String string_from_slice(StrSlice src);

Status string_push(String *s, char c);

Status string_append(String *s, StrSlice tail);

StrSlice string_as_slice(const String *s);

const char *status_to_str(Status s);

#define str_lit(lit) \
	((StrSlice){ .data = (lit), .len = sizeof(lit) - 1 })

#endif // MODERNC_VAR_H
