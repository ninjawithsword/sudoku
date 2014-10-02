#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RANGE 987654321
#define MIN_RANGE 123456789

char* places;
char* new_places;
char** potential;
int num_of_solutions[9];

void read_input() {
  int holder;
  char string[2];
  places = malloc(9 * 9 * sizeof(char));
  
  for(int i = 0; i < 9 * 9; i++) {
    scanf("%d", &holder);
    sprintf(string, "%d", holder);
    places[i] = string[0];
  }
}

void print_solution() {
  for(int i = 0; i < 9 * 9; i++) {
    printf("%c ", new_places[i]);
    if((i + 1) % 9 == 0 && i != 0) 
      printf("\n");
  }
}

void copy_puzzle() {
  for(int i = 0; i < 9 * 9; i++) {
    new_places[i] = places[i];
  }
}

void init_numbers(int* numbers) {
  for(int i = 0; i < 10; i++) {
    numbers[i] = 0;
  }
}

int lines_valid() {
  int* numbers = malloc(10 * sizeof(int));
  
  for(int i = 0; i < 9; i++){ 
    init_numbers(numbers);
    for(int j = 0; j < 9; j++) {
      numbers[new_places[i * 9 + j] - '0']++;
    }
    for(int k = 1; k < 10; k++) {
      if(numbers[k] != 1) {
	free(numbers);
	return(0);
      }
    }
  }
  free(numbers);
  return(1);
}

int columns_valid() {
  int* numbers = malloc(10 * sizeof(int));
  
  for(int i = 0; i < 9; i++) {
     init_numbers(numbers);
    for(int j = 0; j < 9; j++) {
      numbers[new_places[i + 9 * j] - '0']++;
    }
    for(int k = 1; k < 10; k++) {
      if(numbers[k] != 1) {
	free(numbers);
	return(0);
      }
    }
  }
  free(numbers);
  return(1);
}

int squares_valid() {
  int* numbers = malloc(10 * sizeof(int));
  int h, i, j, k;
  for(h = 0; h < 3; h++) {
    for(i = 0; i < 3; i++) {
      init_numbers(numbers);
      for(j = 0; j < 3; j++) {
	for(k = 0; k < 3; k++) {
	  numbers[new_places[(h * 9 * 3) + i * 3 + j * 9 + k] - '0']++;
	}
      }
      for(int l = 1; l < 10; l++) {
	if(numbers[l] != 1) {
	  free(numbers);
	  return(0);
	}
      }
    }
  }
  free(numbers);
  return(1);
}

int string_ok(int n, char* str) {
  int v, u, j, k, l, num[10];
  char holder[2];
  holder[1] = '\0';
  
  // check to see if the numbers given by input
  // occur in the potential complete sudoku row
  for(v = 0; v < 9; v++) {
    /* printf("%d, %d\n", (n*9+v), v); */
    /* printf("places: %c str: %c\n", places[n * 9 + v], str[v]); */
    if((places[n * 9 + v] != '0') && (str[v] != places[n * 9 + v]))
      return(0);
  }
  
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

void find_possible_lines() {
  int line, j, k;
  char str[10];
  
  for(line = 0; line < 9; line++) { // one for each sudoku line
    k = 0;
    for(j = MIN_RANGE; j <= MAX_RANGE; j++) {
      sprintf(str, "%d", j);   
      if(string_ok(line, str)) {
	strcpy(potential[line][k], str);
	k++;
      }
    }
    num_of_solutions[line] = k;
  }
}

int combinations(int line) {
  //returns the num of combinations of the other lines of the puzzle
  int i, sum;

  for(i = 0; i < 9; i++) {
    if(i != line)
      sum += num_of_solutions[i];
  }
  
  return(sum);
}

int offset(int line) {
  int i, offset;

  for(i = 0; i < line; i++) {
    offset += num_of_solutions[i];
  }
  
  return(offset);
}

void solver() {
  int i, j, k;
  
  potential = malloc(9 * 362880 * 9 * sizeof(char));
  
  new_places = malloc(9 * 9 * sizeof(int));
  copy_puzzle();
  
  find_possible_lines();
  
  for(i = 0; i < 9; i++) { // one for each line
    for(j = 0; j < num_of_solutions[i]; j++) {
      copy_line(i, potential[j + offset(i)]);
      for(k = 0; k < combinations(i); k++) {
	//copy the other lines to the new puzzle
	if(lines_valid() && columns_valid() && squares_valid())
	  return(1);
      }
    }
  }
  return(0);
}

int main(void) {
  read_input();
  
  int solved = solver();
  
  if(solved)
    print_solution();
  else
    printf("Sorry, a solution could not be found!\n");
  
  return(0);
}
