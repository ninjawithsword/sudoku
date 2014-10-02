#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
  int i, j;
  
  char *pointer;// = malloc(sizeof(char));
  
  printf("Size of char: %d\n", sizeof(char));
  
  for(i = 0; i < 100; i++) {
    sprintf(&pointer[i*8], "hello%d", i);
  }

  for(j = 0; j < 100; j++) {
    printf("%s\n", &pointer[j*8]);
  }
  
  return(0);
}
