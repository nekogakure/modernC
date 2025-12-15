#include <stdlib.h>
#include <string.h>
#include "../include/m_var.h"
#include "../include/m_result.h"

/**
 * Create a string slice
 * @param s string data
 * @param len length of the string
 * @return string slice
 */
StrSlice str_slice(const char *s, const usize len) {
	return (StrSlice){.data = s, .len = len};
}

/**
 * Compare two string slices for equality
 * @param a first string slice
 * @param b second string slice
 * @return true if equal, false otherwise
 */
boolean str_eq(const StrSlice a, const StrSlice b) {
	if (a.len != b.len) return false;
	for (usize i = 0; i < a.len; i++) {
		if (a.data[i] != b.data[i]) return false;
	}
	return true;
}

/**
 * Get a substring from a string slice
 * @param s original string slice
 * @param pos starting position
 * @param len length of the substring
 * @return substring as a new string slice
 */
StrSlice str_sub(const StrSlice s, const usize pos, usize len) {
	if (pos > s.len) len = 0;
	if (pos + len > s.len) len = s.len - pos;
	return (StrSlice){.data = s.data + pos, .len = len};
}

/**
 * Create a new empty mutable string
 * @return new mutable string
 */
String string_new(void) {
	String s;
	s.cap = 8;
	s.len = 0;
	s.data = (char *) malloc(s.cap);
	s.data[0] = '\0';
	return s;
}

/**
 * Free a mutable string
 * @param s mutable string to free
 */
void string_free(String *s) {
	if (!s || !s->data) return;
	free(s->data);
	s->data = nullptr;
	s->len = s->cap = 0;
}

/**
 * Create a mutable string from a string slice
 * @param src source string slice
 * @return new mutable string
 */
String string_from_slice(const StrSlice src) {
	String s;
	s.cap = src.len + 1;
	s.len = src.len;
	s.data = (char *) malloc(s.cap);
	memcpy(s.data, src.data, src.len);
	s.data[src.len] = '\0';
	return s;
}

/**
 * Push a character to the end of a mutable string
 * @param s mutable string
 * @param c character to push
 * @return status code
 */
Status string_push(String* s, const char c) {
	if (s->len + 1 >= s->cap) {
		const usize new_cap = s->cap * 2;
		char* p = realloc(s->data, new_cap);
		if (!p) return Status_Nomem;
		s->data = p;
		s->cap = new_cap;
	}
	s->data[s->len++] = c;
	s->data[s->len] = '\0';
	return Status_Ok;
}

/**
 * Append a string slice to a mutable string
 * @param s mutable string
 * @param tail string slice to append
 * @return status code
 */
Status string_append(String* s, const StrSlice tail) {
	for (usize i = 0; i < tail.len; i++) {
		const Status st = string_push(s, tail.data[i]);
		if (st != Status_Ok) return st;
	}
	return Status_Ok;
}

/**
 * Convert a mutable string to a string slice
 * @param s mutable string
 * @return string slice
 */
StrSlice string_as_slice(const String* s) {
	return (StrSlice){ .data = s->data, .len = s->len };
}