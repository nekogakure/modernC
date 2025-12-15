#include <stdio.h>
#include "../include/m_result.h"

#include <stdlib.h>

/**
 * Panic function to handle unrecoverable errors
 * @param msg error message to display
 */
void panic(const char *msg) {
	fprintf(stderr, "Panic: %s\n", msg);
	exit(-1);
}

/**
 * Create a ResultString with the given String value
 * @param s String value to wrap
 * @return ResultString containing the String
 */
ResultString f(const String s) {
	return (ResultString)OkVal(s);
}
