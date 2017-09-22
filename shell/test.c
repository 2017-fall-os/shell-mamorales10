#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mytoc.h"

/* Prints the tokens in the vector */
void printTokens(char **vect){

  char **tempTok = vect;
  while(*tempTok != 0){
    printf("%s\n", *tempTok);
    tempTok++;
  }
  
}

/* Checks if input equals PATH*/
char isPath(char *str){

  char path[] = "PATH";
  int i;
  for(i = 0; str[i] == path[i]; i++){
    if(str[i] == '\0')
      return 1;
  }
  return 0;
}

/* Checks if input equals exit */
char isExit(char *str){

  char exit[] = "exit";
  int i;

  for(i = 0; str[i] == exit[i]; i++){
    if(str[i] == '\0')
      return 1;
  }
  
  return 0;
  
}

/* Receives string and replaces '\n' with 0 */
void getString(char* s, int limit){

  char *p = s;
  char c;
  fgets(s, limit, stdin);
  while((c = *p) && (c != '\n'))
    p++;
  if(c == '\n')
    *p = 0;
  
}

int main(int argc, char** argv, char** envp){

  char buff[200];
  char **vect;

  /* Searches envp for PATH variable */
  char **testVect;
  char i;
  for(i=0; !isPath(*(testVect = mytoc((char *)envp[i], '='))); i++){
    free(testVect);
  }
  printTokens(testVect);         /*DELETE THIS*/

  /* Tokenizes each path */
  char **pathVect = mytoc((char *)testVect[1], ':');
  free(testVect);
  printTokens(pathVect);        /*DELETE THIS*/
  



  
  if(write(1, "$ ", 2) != 2){
    write(2, "There was an error.\n", 20);
    return -1;
  }
  getString(buff, 200);

  while(!isExit(buff)){
  
    vect = mytoc((char *)buff, ' ');

    printTokens(vect);        /*DELETE THIS*/

    

    free(vect); //Frees token vector
    if(write(1, "$ ", 2) != 2){
      write(2, "There was an error.\n", 20);
      return -1;
    }
    getString(buff, 200);
  
  }
  
  printf("Program Ended\n");    

}
