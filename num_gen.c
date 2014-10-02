#include <stdio.h>

#define MAX_RANGE 987654321 
#define MIN_RANGE 123456789

int string_ok(char* str) {
  int u, j, k, l, num[10];
  char holder[2];
  holder[1] = '\0';

  for(u = 0; u < 10; u++) {
    num[u] = 0;
  }

  for(j = 0; j < 9; j++) {
    if(str[j] == '0')
      return(0);
  }

  for(k = 0; k < 9; k++) {
    holder[0] = str[k];    
    int tmp = atoi(holder);
    num[tmp]++;
  }
  
  for(l = 1; l < 10; l++) {
    if(num[l] != 1)
      return(0);
  }
  
  return(1);
}

int main(void) {
  int i;
  char str[10];
  
  for(i = MIN_RANGE; i <= MAX_RANGE; i++) {
    sprintf(str, "%d", i);
    
    if(string_ok(str)) {
      printf("%s\n", str);
    }
  }
  
  return(0);
}
  
