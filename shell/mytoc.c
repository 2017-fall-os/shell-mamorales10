#include <stdlib.h>
#include <stdio.h>
#include "mytoc.h"
#include "helpFuncts.h"

/* Prints the tokens in the vector */
void printTokens(char **vect){

  char **tempTok = vect;
  while(*tempTok != 0){
    printf("%s\n", *tempTok);
    tempTok++;
  }
  
}

/* Counts the number of tokens. */
char getTokNum(char *str, char delim){

  char numToks = 0;
  char state = 0;
  char i;
  char *temp = str;
  while(i = *temp){
    if(state == 0){
      if(i != delim){
	numToks++;
	state = 1;
      }
      temp++;
    }
    else{
      if(i == delim)
	state = 0;
      temp++;
    }
  }

  return numToks;
  
}

char **mytoc(char *str, char delim){

  char numToks = getTokNum(str, delim);
  char **vect = (char **)malloc(sizeof(char *) * (numToks+1));
  
  int len = 0;   /*length of the token*/
  char state = 0;
  char toksLeft = numToks;
  char i;  /*index for str*/
  char j;  /*index for tokens*/
  char *temp = str;
  char *tok;  /*temp pointer for tokens found*/
  while(toksLeft > 0){
    i = *temp;
    if(state == 0){
      if(i != delim){
	len++;
	state = 1;
      }
      temp++;
    }
    else{
      if(i == delim || i == '\0'){
	tok = copyString(temp-len,len); /*Copying token into tok array*/
	vect[numToks-toksLeft] = tok; /*Assigning pointer of array to vector*/
	toksLeft--;
	len = 0;
	state = 0;
      }
      else
	len++;
      temp++;
    }
  }
  vect[numToks] = 0;
  return vect;
  
}
