#include <stdlib.h>
#include <stdio.h>
#include "helpFuncts.h"

/* Returns the length of the string */
int strLength(char *str){

  char *temp = str;
  char i;
  int len = 0;
  for(i = 0; temp[i] || temp[i] != '\0'; i++){
    len++;
  }
  return len;
}

char *copyString(char *start, int len){

  char *newString = (char *)malloc(sizeof(char)*(len+1));
  int i;
  for(i = 0; i < len; i++)
    newString[i] = start[i];
  newString[len] = 0;

  return newString;

}

/* Concatenates the given strings with a '/' inbetween */
char *strConcat(char *src, char *dst){

  char srcLen = strLength(src);
  char dstLen = strLength(dst);
  char *finalStr = (char *)malloc(sizeof(char)*(srcLen + dstLen + 2));

  char i;
  for(i = 0; i < (srcLen+dstLen+1); i++){
    if(i < srcLen){
      finalStr[i] = src[i];
    }
    else if(i == srcLen){
      finalStr[i] = '/';
    }
    else{
      finalStr[i] = dst[i-(srcLen+1)];
    }
  }
  finalStr[i] = 0;
  return finalStr;
}

char cmpString(char *str1, char *str2){

  int i = 0;
  for(i = 0; str1[i] == str2[i]; i++){
    if(str1[i] == '\0' && str2[i] == '\0')
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

/* Checks if string has '&'*/
int isBackground(char *s){

  int i;
  for(i = 0; s[i]; i++){
    if(s[i] == '&')
      return 1;
  }
  return 0;
}
