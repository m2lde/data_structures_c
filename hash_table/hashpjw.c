#include "hashpjw.h"

#define PRIME_TELSIZ 100

int hashpjw(const void *key){
	const char	*ptr;
	int					val;

	val = 0;
	ptr = (const char *) key;

	while(*ptr != '\0'){
		int tmp;
		val = (val << 4) + (*ptr);
		if((tmp = (val & 0xf0000000))) {
			val ^= (tmp >> 24);
			val ^= tmp;
		}
		ptr++;
	}
	return val & PRIME_TELSIZ;
}
