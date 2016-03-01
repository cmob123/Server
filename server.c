// Chris O'Brien
// CS-311
// server.c

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
  int max = atoi(argv[1]); // number of times to process input
  message.mtype = 2;
  if(max<0 || max>100){ // error checking
    error = 1; 
    printf("ERROR in server: Max (%d) is out of range!\n", max);
  }
  printf("Server got through error checking\n");
  qid = msgget(370, 0600 | IPC_CREAT); // create queue
  if (qid >= 0) printf("Created queue with qid = %d.\n", 370); // error checking
  else printf("ERROR when creating Queue");
  message.nextInt = 1;
  status = msgsnd(372, &message, sizeof(message)-sizeof(long), 0);
  if (status < 0) printf("ERROR sending message");
}
