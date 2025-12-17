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

/**
 * Create an error Result with a status code and message
 * @param code Status code of the error
 * @param msg Error message as a String
 * @return Result containing the error information
 */
Result ErrWithMsg(Status code, String msg) {
	return (Result){ .status = code, .err = { .code = code, .msg = msg } };
}

/**
 * Create a successful Result
 * @return Result indicating success
 */
Result Ok() {
	return (Result){ Status_Ok, { Status_Ok, (String){0} } };
}

/**
 * Create an error Result with the given status code
 * @param st Status code of the error
 * @return Result containing the error information
 */
Result Err(const Status st) {
	return (Result){ st, { st, (String){0} } };
}