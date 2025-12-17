#include <stdio.h>
#include <stdlib.h>
#include "../include/modern.h"

Result run_vec_demo(void) {
	// create an integer vector
	let v = vec_new(i32);

	// push some values
	for (i32 i = 0; i < 10; i++) {
		vec_push(v, i);
	}

	printf("vec len=%zu cap=%zu\n", (size_t)vec_len(v), (size_t)vec_capacity(v));

	// iterate and print
	for (usize i = 0; i < vec_len(v); i++) {
		printf("v[%zu]=%d\n", (size_t)i, v.data[i]);
	}

	while (vec_len(v) > 0) {
		i32 out;
		const let r = vec_try_pop(v.data, &v.len, &out, sizeof(out));
		if (IsErr(r)) {
			panic("vec_try_pop failed");
		}
		printf("popped: %d\n", out);
	}

	vec_free(v);
	return Ok();
}

int main(void) {
	const let r = run_vec_demo();
	if (IsErr(r)) {
		fprintf(stderr, "vec_demo failed: %s\n", status_to_str(r.status));
	}

	return r.status;
}
