#ifndef MODERNC_OPTION_H
#define MODERNC_OPTION_H

#include "../include/m_var.h"
#include "../include/m_result.h"

/// Option type for optional values
#define Option(T) \
struct { \
	boolean is_some; \
	T value; \
}

/// Create a Some option with the given value
#define Some(v) \
{ .is_some = true, .value = (v) }

/// Create a None option
#define None \
{ .is_some = false }

/// Check if the option is Some
#define is_some(o) ((o).is_some)
#define is_none(o) (!(o).is_some)

/// Unwrap an Option, panic if it's None
#define unwrap_option(o) \
({ \
	__auto_type _o = (o); \
	if (!_o.is_some) { \
		panic("unwrap_option on None"); \
	} \
	_o.value; \
})


#endif //MODERNC_OPTION_H
