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
  for(i=0; !cmpString(*(envpVect = mytoc((char *)envp[i], '=')), "PATH"); i++){
    free(envpVect);
  }

  /* Tokenizes each path in the PATH variable */
  char **pathVect = mytoc((char *)envpVect[1], ':');
  free(envpVect);

  /* Searches envp for home directory for cd command */
  for(i=0; !cmpString(*(envpVect = mytoc((char *)envp[i], '=')), "HOME"); i++){
    free(envpVect);
  }
  char *homePath = (char *)envpVect[1];
  free(envpVect);

  /* Prompt */
  if(write(1, "$ ", 2) != 2){
    write(2, "There was an error.\n", 20);
    return -1;
  }
  getString(buff, 200);
  int bg = isBackground((char *)buff);/* Checking for background tasks */
  
  char **commandVect;
  char numCommands;
  int  *pipeFDs;  //Pipe
  char **nextBuffer;  //command go into this after checking for '&'
  while(!cmpString(buff, "exit")){
    
    
    /* Tokenizes '&' */
    //nextBuffer = mytoc((char *)buff, '&');

    /* Checking for pipes */
    numCommands = getTokNum(buff, '|');
    
    /* If there are pipes, tokenize commands */
    if(numCommands > 1){
      commandVect = mytoc(buff, '|');
      vect = mytoc(commandVect[0], ' ');
      
      pipeFDs = (int *) malloc(2*sizeof(int));
    }
    else{
      /* Tokenizes command and arguments */
      vect = mytoc(buff, ' ');
    }
    int signal;   /* Signal to check if child process exited normally */

    /* Start Process if vector not empty */
    if(vect[0]){
      int pid;  // process id
      /*If there is a pipe*/
      if(numCommands > 1){

	int inCopy = dup(0);
	int outCopy = dup(1);
	for(i = 1; commandVect[i]; i++){
	  pipe(pipeFDs);
	  pid = fork();
	  if(pid < 0){
	    printf("Failed to create new process\n");
	  }
	  else if(pid == 0){
	    
	    close(1);
	    dup(pipeFDs[1]);
	    close(pipeFDs[1]); close(pipeFDs[0]);
	    
	    /* Checks if given absolute path */
	    int execVal = execve(vect[0], vect, envp);
	 
	    /* Searching for an executable path */
	    int j;
	    for(j=0; execVal != 0 && pathVect[j]; j++){
	      execVal = execve(strConcat(pathVect[j], vect[0]), vect, envp);
	    }
	    printf("Command Not Found.\n");
	    return 0;
	  }
	  else{
	    wait(NULL);
	    close(0);
	    dup(pipeFDs[0]);
	    close(pipeFDs[0]); close(pipeFDs[1]);
	    free(vect);
	    vect = mytoc((char *)commandVect[i], ' '); //Get next command
	  }
	}
	/* Next fork() is last command */
	pid = fork();
	if(pid < 0)
	  printf("Failed to create new process.\n");
	else if(pid == 0){
	  /* Checks if given absolute path */
	  int execVal = execve(vect[0], vect, envp);
	 
	  /* Searching for an executable path */
	  for(i=0; execVal != 0 && pathVect[i]; i++)
	    execVal = execve(strConcat(pathVect[i], vect[0]), vect, envp);
	  
	  printf("Command not found.\n");
	  return 0;
	}
	else{
	  free(commandVect);
	  wait(&signal);
	  if(WIFSIGNALED(signal))
	    printf("Program terminated with exit code %d\n", WTERMSIG(signal));
	}
	dup2(inCopy, 0); /*put stdin back*/
	dup2(outCopy, 1); /*Put stdout back*/
	free(pipeFDs); /*Free pipe*/
       
      }
      /*else no pipe*/
      else{
	if(cmpString(vect[0], "cd") && getTokNum(buff, ' ') == 2)
	  chdir(vect[1]);
	else if(cmpString(vect[0], "cd") && getTokNum(buff, ' ') == 1)
	  chdir(homePath);
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
    }
    
    free(vect); //Frees token vector
    if(write(1, "$ ", 2) != 2){
      write(2, "There was an error.\n", 20);
      return -1;
    }
    getString(buff, 200);
    bg = isBackground((char *)buff);
  }
  free(pathVect); /* Free tokenized paths */
  printf("Program Ended\n");    

}
