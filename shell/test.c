#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mytoc.h"
#include "helpFuncts.h"


int main(int argc, char** argv, char** envp){

  char buff[200];
  char **vect;

  /* Searches envp for PATH variable */
  char **envpVect;
  char i;
  for(i=0; !isPath(*(envpVect = mytoc((char *)envp[i], '='))); i++){
    free(envpVect);
  }

  /* Tokenizes each path in the PATH variable */
  char **pathVect = mytoc((char *)envpVect[1], ':');
  free(envpVect);
  
  if(write(1, "$ ", 2) != 2){
    write(2, "There was an error.\n", 20);
    return -1;
  }
  getString(buff, 200);

  while(!isExit(buff)){
    /* Tokenezes command and arguments */
    vect = mytoc((char *)buff, ' ');
    int signal;   /* Signal to check if child process exited normally */

    /* Start Process if command not empty */
    if(vect[0]){
      int pid = fork();
      if(pid < 0){
	printf("Failed to create new process\n");
      }
      else if(pid == 0){
	int execVal = execve(vect[0], vect, envp);

	for(i=0; execVal != 0 && pathVect[i]; i++){
	  execVal = execve(strConcat(pathVect[i], vect[0]), vect, envp);
	}
	printf("Command Not Found.\n");
	return 0;
      }
      else{
	wait(&signal);
	if(WIFEXITED(signal))    /* Checking for exit signal of child */
	  printf("Child Process Returned.\n");
	else if(WIFSIGNALED(signal))
	  printf("Program terminated with exit code %d\n", WTERMSIG(signal));
      }
    }
    free(vect); //Frees token vector
    if(write(1, "$ ", 2) != 2){
      write(2, "There was an error.\n", 20);
      return -1;
    }
    getString(buff, 200);
  
  }
  
  printf("Program Ended\n");    

}
