#include <stdlib.h>
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
