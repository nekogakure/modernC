#include <stdio.h>
#include "../include/modern.h"

int main() {
	String s = string_new();

	if (string_append(&s, str_lit("Hello")) != Status_Ok) {
		fprintf(stderr, "string_append failed\n");
		return 1;
	}

	if (string_push(&s, ' ') != Status_Ok) {
		fprintf(stderr, "string_push failed\n");
		string_free(&s);
		return 1;
	}

	if (string_append(&s, str_lit("world")) != Status_Ok) {
		fprintf(stderr, "string_append failed\n");
		string_free(&s);
		return 1;
	}

	const StrSlice sl = string_as_slice(&s);
	printf("string: %.*s\n", (int) sl.len, sl.data);

	String s2 = string_from_slice(str_lit("from-slice"));
	const StrSlice sl2 = string_as_slice(&s2);
	printf("from-slice: %.*s\n", (int) sl2.len, sl2.data);

	// easy comparison
	if (str_eq(sl, sl2)) {
		printf("s and s2 are equal\n");
	} else {
		printf("s and s2 differ\n");
	}

	string_free(&s);
	string_free(&s2);
	return Status_Ok;
}
