#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

/** other code you might need ***/
unsigned int sleep(unsigned int seconds);
pid_t getpid(void);

void sighandler(int signum){
   printf("Received a signal %d\n", signum);
}

int main(int argc, char ** argv){
   signal(SIGINT, sighandler);
   if(argc != 2){
      printf("Did you forget to specify number of seconds sleep?\n");
      exit(1);
   }
   printf("I am process %d\n", getpid());
   return 0;

   // remaining type on our sleep (before we were interrupted
   int remaining;

   // atoi is to convert string to int - e.g. remember to call ./sleepy 5
   remaining = sleep(atoi(argv[1]));
   printf("remaining time %d\n", remaining);
   exit(0);

}
