// Chris O'Brien
// CS-311
// mult.c

#include <stdio.h>  // acts like import "java.io.*;"
#include <stdlib.h> // for library function prototypes
#include <string.h> // for manipulating strings
#include <sys/types.h> // for queueing
#include <sys/ipc.h> // for queueing
#include <sys/msg.h> // for queueing

struct mess { // structure of messages
  long mtype;
  int nextInt;
} message;

void main(int argc, char *argv[]) {
  struct mess message; // message
  int qid, status; // store return values for IPC functions
  int error = 0; // 0: no error, 1: error
  int factor = atoi(argv[1]); // multiplier
  int max = atoi(argv[2]); // number of times to process input
  message.mtype = 2;
  if(factor<0 || factor>100 || max<0 || max>100){ // error checking
    error = 1; 
    printf("ERROR in mult(%d)!: invalid value passed.\n", factor);
  }
  printf("Mult(%d) got through error checking\n", factor);
  qid = msgget(370 + factor, 0600 | IPC_CREAT); // create queue
  if (qid >= 0) printf("Created queue with qid = %d.\n", 370 + factor);
  else printf("ERROR when creating Queue");
  status = msgrcv(370+factor, &message, sizeof(message)-sizeof(long),2,0);
  if (status < 0) printf("ERROR receiving message");
}
