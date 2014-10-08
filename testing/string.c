#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
  char str[10];
  int i, j;
  
  //for(i = 0; i < 99999; i++) {
  sprintf(str, "%d", 99999);
  //}
  
  /* for(j = 0; j < 99999; j++) { */
  /* } */
  
  printf("%s\n", str);

  /* **************************************** */
  
  char *array = malloc(6 * sizeof(char));
  sprintf(array, "%d", 88888);
  printf("%s\n", &array[2]);
  
  return(0);
}
