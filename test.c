#include "objstring.h"
#include "objstringcollection.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsequence-point"

void each(string string, size_t index){
	printf("String '%s' at index %d\n\n", string.string, index);
}

int main() {
	// TESTING
	
	string line = objstr(0);
	$(line).c_copy("am O o O pisica O foarte O mare.");
	stringcollection parts = $(line).c_split(" O ");
	string repeat = $(parts.items[0]).repeat(2);
	printf("%s <- original\n", repeat.string);
	$(repeat).convert_upper();
	printf("%s <- uppercase\n\n", repeat.string);
	printf("starts with 'am' -> %d, ends with 'mare.' -> %d\n\n", $(line).c_starts("am"), $(line).c_ends("mare."));

	$(line).c_concat("MORE DATA!!!!");

	#ifndef typeof
		$(parts).foreach(each);
	#elif
		$c(parts).foreach(each); // BOOHOO
	#endif

	$(line).c_copy("e");

	$(line).free();

	#ifndef typeof
		$(parts).free();
	#elif
		$c(parts).free(); // BOOHOO
	#endif
	$(repeat).free();

	// compat
	printf("\n\nuser input test\n\n");

	string input = objstr(0);
	$(input).prealloc(128);
	fgets(input.string, 128, stdin);
	
	printf("normal : %s\n", input.string);
	$(input).convert_upper();
	printf("uppercase : %s\n", input.string);
	$(input).convert_lower();
	printf("lowercase : %s\n", input.string);
	string subs = $(input).substring(0, 6);
	printf("first 6 : %s\n", subs.string);

	$(input).free();
	$(subs).free();

	return 0;
}
