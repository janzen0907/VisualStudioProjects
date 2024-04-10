//Use Header Guards to prevent these prototypes from being added more than once
//in a file.

//#pragma once //will ensure that the file is only loaded once

#ifndef PINGPONG_H //If not defined (will be true the firt time it is encountered)
#define PINGPONG_H // Define (makes the ifndef false every other time)

#define MAX_PING_PONGS 10 //Maximum number of ping-pong calls

//Must write function prototypes to indicate that these functions are coded
//somewhere in the project
void ping();
void pong(); // semicolons after function prototypes

#endif //End the #ifndef PINGPONG_H

