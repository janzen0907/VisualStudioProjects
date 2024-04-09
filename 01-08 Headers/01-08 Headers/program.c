#include <stdio.h>
#include <stdlib.h>
#include "pingpong.h"


// A function prototype(signature) lists the types for that function (its signature)
// so that the compiler knows how to call that function
void demo();


int main(void)
{
	printf("Welcome to main!\n");
	demo(); //call to a function after main -- error if redefined

	return EXIT_SUCCESS;
}

void demo()
{
	printf("Welcome to demo!\n");
	ping();
}
