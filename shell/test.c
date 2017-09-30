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
  
  char **commandVect;
  int *pipeFDs;
  while(!isExit(buff)){

    /* Checking for pipes */
    char numCommands = getTokNum((char *)buff, '|');   /*ADDED THIS*/

    /* If there are pipes, tokenize commands */
    if(numCommands > 1){                               /*ADDED THIS CONDITION*/
      commandVect = mytoc((char *)buff, '|');
      vect = mytoc((char *)commandVect[0], ' ');
      
      pipeFDs = (int *) malloc(2*sizeof(int));
      pipe(pipeFDs);
    }
    else{
      /* Tokenizes command and arguments */
      vect = mytoc((char *)buff, ' ');
    }
    int signal;   /* Signal to check if child process exited normally */

    /* Start Process if command not empty */
    if(vect[0]){
      int pid;  // process id
      if(numCommands > 1){

	for(i = 1; vect[0]; i++){
	  
	  pid = fork();
	  if(pid < 0){
	    printf("Failed to create new process\n");
	  }
	  else if(pid == 0){
	    if(numCommands == 1){
	      close(0);
	      dup(pipeFDs[0]);
	      close(pipeFDs[0]); close(pipeFDs[1]);
	    }
	    else if(numCommands > 1){
	      close(1);
	      dup(pipeFDs[1]);
	      close(pipeFDs[1]); close(pipeFDs[0]);
	    }
	    /* Checks if given absolute path */
	    int execVal = execve(vect[0], vect, envp);
	
	    /* Searching for an executable path */
	    for(i=0; execVal != 0 && pathVect[i]; i++){
	      execVal = execve(strConcat(pathVect[i], vect[0]), vect, envp);
	    }
	    printf("Command Not Found.\n");
	    return 0;
	  
	  }
	  free(vect);
	  vect = mytoc((char *)commandVect[i], ' ');
	  numCommands--;
	}
	free(vect);
	wait(&signal);
	if(WIFSIGNALED(signal))
	  printf("Program terminated with exit code %d\n", WTERMSIG(signal));
       
	
      }
      else{
	pid = fork();
	if(pid < 0){
	  printf("Failed to create new process\n");
	}
	else if(pid == 0){
	
	  /* Checks if given absolute path */
	  int execVal = execve(vect[0], vect, envp);
	
	  /* Searching for an executable path */
	  for(i=0; execVal != 0 && pathVect[i]; i++){
	    execVal = execve(strConcat(pathVect[i], vect[0]), vect, envp);
	  }
	  printf("Command Not Found.\n");
	  return 0;
	}
	else{
	  wait(&signal);
	  if(WIFSIGNALED(signal))
	    printf("Program terminated with exit code %d\n", WTERMSIG(signal));
	}
      }
    }
    free(vect); //Frees token vector
    if(write(1, "$ ", 2) != 2){
      write(2, "There was an error.\n", 20);
      return -1;
    }
    getString(buff, 200);
  
  }
  free(pathVect); /* Free tokenized paths */
  printf("Program Ended\n");    

}
