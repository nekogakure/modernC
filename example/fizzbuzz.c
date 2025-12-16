#include <stdio.h>
#include "../include/modern.h"

int main(void) {
	// FizzBuzz 1 to 100
	for (i32 i = 1; i <= 100; i++) {
		const let fizz = (i % 3 == 0);
		const let buzz = (i % 5 == 0);

		if (fizz && buzz) {
			printf("FizzBuzz\n");
		} else if (fizz) {
			printf("Fizz\n");
		} else if (buzz) {
			printf("Buzz\n");
		} else {
			printf("%d\n", i);
		}
	};
}
