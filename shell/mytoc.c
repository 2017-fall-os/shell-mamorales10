#include <stdlib.h>
#include <stdio.h>
#include "mytoc.h"

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
  
  char len = 0;   /*length of the token*/
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
	tok = (char *)malloc(sizeof(char)*(len+1));
	for(j=0; j<len; j++){
	  tok[j] = temp[j-len];  /*Copying token into an array*/
	}
	tok[len] = 0;
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
