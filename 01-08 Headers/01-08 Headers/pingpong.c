#include <stdio.h>
#include "pingpong.h"
//include local files with "" so function prototypes are known ahead of use


void ping()
{
	printf("Ping\n");
	pong(); //pong() is not defined yet - assumed returning int
}

void pong() //actual definition of pong() is here - void
{
	static int iCount = 0; // only 1 copy in memory, only accessible in function

	iCount++;
	printf("Pong\n");
	if (iCount < MAX_PING_PONGS)
	{
		ping();
	}

}