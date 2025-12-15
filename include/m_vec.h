#ifndef MODERNC_VEC_H
#define MODERNC_VEC_H

#include "../include/m_var.h"
#include "../include/m_result.h"

/// Dynamic array (vector) type
#define Vec(T) \
struct { \
	T* data; \
	usize len; \
	usize cap; \
}

/// Create a new empty vector
#define vec_new(T) \
((Vec(T)){ .data = NULL, .len = 0, .cap = 0 })

/// Create a new vector with specified capacity
#define vec_with_capacity(T, c) \
((Vec(T)){ \
	.data = (T*)malloc(sizeof(T) * (c)), \
	.len = 0, \
	.cap = (c) \
})

/// Get the length and capacity of the vector
#define vec_len(v) ((v).len)

/// Get the capacity of the vector
#define vec_capacity(v) ((v).cap)

/// Access element at index i
#define vec_push(v, item) \
do { \
	if ((v).len >= (v).cap) { \
		Result _r = vec_grow((void**)&(v).data, &(v).cap, sizeof(*(v).data)); \
		if (is_err(_r)) return _r; \
	} \
	(v).data[(v).len++] = (item); \
} while (0)

/// Pop an element from the end of the vector
#define vec_pop(v) \
({ \
	Option(__typeof__(*(v).data)) _res = None; \
	if ((v).len > 0) { \
		_res = Some((v).data[--(v).len]); \
	} \
	_res; \
})

/// Free the vector's memory
#define vec_free(v) \
do { \
	free((v).data); \
	(v).data = NULL; \
	(v).len = 0; \
	(v).cap = 0; \
} while (0)


Result vec_grow(void** data, usize* cap, usize elem_size);

#endif //MODERNC_VEC_H