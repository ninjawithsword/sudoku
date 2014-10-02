#include <stdio.h>

void string_print(char* str) {
  printf("%s\n", str);
  printf("%d\n", sizeof(str));
}

int main(void) {
  char str[4] = "tau";
  
  /* str[0] = 't'; */
  /* str[1] = 'a'; */
  /* str[2] = 'u'; */
  /* str[3] = '\0'; */

  string_print(str);
  
  char tmp[2];

  tmp[0] = '2';
  tmp[1] = '\0';

  printf("%d\n", atoi(tmp));
  return(0);
}
