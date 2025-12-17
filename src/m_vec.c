#include <stdlib.h>
#include <string.h>
#include "../include/m_var.h"
#include "../include/m_vec.h"
#include "../include/m_result.h"

Result vec_grow(void** data, usize* cap, const usize elem_size) {
	const usize new_cap = *cap == 0 ? 4 : *cap * 2;
	void* p = realloc(*data, new_cap * elem_size);
	if (!p) return Err(Status_Nomem);
	*data = p;
	*cap = new_cap;
	return Ok();
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
Result vec_try_pop(void* data, usize* len, void* out, const usize elem_size) {
	if (!len || !out) return Err(Status_Invalid);
	if (*len == 0) return Err(Status_Err);
	const char* base = data;
	const char* src = base + ( (*len - 1) * elem_size );
	memcpy(out, src, elem_size);
	*len = *len - 1;
	return Ok();
}
