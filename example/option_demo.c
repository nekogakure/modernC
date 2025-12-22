#include <stdio.h>
#include "../include/modern.h"

Result maybe_divide(const i32 a, const i32 b, i32 *out) {
	if (!out) return Err(Status_Invalid);
	if (b == 0) return Err(Status_Invalid);
	*out = a / b;
	return Ok();
}

Result use_try(void) {
	i32 q;
	Try(maybe_divide(10, 2, &q));
	printf("10 / 2 = %d\n", q);

	Try(maybe_divide(1, 0, &q));

	return Ok();
}

Result find_in_array(const i32 *arr, const usize len, i32 v, usize *out_index) {
	if (!arr || !out_index) return Err(Status_Invalid);
	for (usize i = 0; i < len; i++) {
		if (arr[i] == v) {
			*out_index = i;
			return Ok();
		}
	}
	return Err(Status_Err);
}

int main(void) {
	const let r = use_try();
	if (IsErr(r)) {
		printf("use_try returned error: %s\n", status_to_str(r.status));
	}

	constexpr i32 nums[] = {5, 7, 9};
	Option(usize) o = None;
	usize idx;
	Result fr = find_in_array(nums, 3, 7, &idx);
	if (IsOk(fr)) {
		o.is_some = true;
		o.value = idx;
	} else {
		o.is_some = false;
	}

	if (is_some(o)) {
		printf("found at index %zu\n", (size_t) unwrap_option(o));
	} else {
		printf("not found\n");
	}

	fr = find_in_array(nums, 3, 42, &idx);
	if (IsOk(fr)) {
		o.is_some = true;
		o.value = idx;
	} else {
		o.is_some = false;
	}
	if (is_none(o)) {
		printf("42 not found\n");
	}

	return Status_Ok;
}
