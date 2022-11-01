#include  <stdio.h>
#include <stdlib.h>
#include  <sys/types.h>
#include <time.h>

#define   MAX_COUNT  200

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
    pid_t pidA;
    pid_t pidB;

    pidA = fork();
    //Error in the Forking
    if (pidA < 0){
      exit(-1);
    }
    //In Child A Process
    else if (pidA == 0){
      ChildProcess();
    }
    //In Parent Process 
    else{
      pidB = fork();
      if(pidB < 0){
        exit(-1);
      }
      //In Child B Process
      else if(pidB == 0){
        ChildProcess();
      }
      else{
          ParentProcess();
      }
    }
}

void  ChildProcess(void)
{
     pid_t child_pid = getpid();
     pid_t parent_pid = getppid();
     int   i;
     int lower = 1;
     int upper = 31;
     srand(time(NULL));
     int iter = (rand() % (upper-lower+1));

     for (i = 1; i <= iter; i++){
          printf("This line is from child, value = %d\n", i);
          printf("Child Pid: %d is going to sleep!\n", child_pid);

          lower = 1;
          upper = 11;
          srand(time(NULL));
          int sleep_count = (rand() % (upper-lower+1));
          sleep(sleep_count);

          printf("Where is my Parent: %d\n", parent_pid);
     }
     printf("   *** Child process is done ***\n");
     exit(0);
}

void  ParentProcess(void)
{
     int   i;
     pid_t t_child;
     for (i = 1; i <= 2; i++){
          printf("This line is from parent, value = %d\n", i);
          t_child = wait(NULL);
          printf("Child Pid: %d has completed\n", t_child);
     }
     printf("*** Parent is done ***\n");
}