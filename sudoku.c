#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RANGE 987654321
#define MIN_RANGE 123456789

char *places;
char *new_places;
char *potential;
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

int offset(int line) {
  int i, offset = 0;

  for(i = 0; i < line; i++) {
    offset += num_of_solutions[i];
  }
  
  return(offset);
}

void print_num_of_solutions() {
  int i;

  for(i = 0; i < 9; i++) {
    printf("%d\n", num_of_solutions[i]);
  }
}

void print_potentials() {
  int line, comb, off;

  for(line = 0; line < 9; line++) {
    off = offset(line);
    for(comb = 0; comb < num_of_solutions[line]; comb++) {
      printf("%s\n", &potential[comb*10 + (off*10)]);
    }
  }
}

/* void find_possible_lines() { */
/*   int line, j, k, off; */
/*   char str[10]; */
  
/*   for(line = 0; line < 9; line++) { // one for each sudoku line */
/*     k = 0; */
/*     off = offset(line); */
/*     for(j = MIN_RANGE; j <= MAX_RANGE; j++) { */
/*       sprintf(str, "%d", j); */
/*       if(string_ok(line, str)) { */
/*       	strcpy(&potential[k*10 + off], str); */
/* 	k++; */
/*       } */
/*     } */
/*     num_of_solutions[line] = k; */
/*   } */
/* } */

void print_possible_lines() {
  int line, j, k, off;
  char str[10];
  
  for(line = 0; line < 9; line++) { // one for each sudoku line
    k = 0;
    off = offset(line);
    for(j = MIN_RANGE; j <= MAX_RANGE; j++) {
      sprintf(str, "%d", j);
      if(string_ok(line, str)) {
	strcpy(&potential[k*10 + (off*10)], str);
	k++;
      }
    }
    num_of_solutions[line] = k;
  }
  
  /* print_num_of_solutions(); */
  /* print_potentials(); */
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

void copy_line(int line, char *combination) {
  int i;

  for(i = 0; i < 9; i++) {
    new_places[i + (line*9)] = combination[i];
  }
}

void load_possible_lines() {
  int i, j, comb, off;

  for(i = 0; i < 9; i++) {
    scanf("%d\n", &num_of_solutions[i]);
  }
  
  for(j = 0; j < 9; j++) {
    off = offset(j);
    for(comb = 0; comb < num_of_solutions[j]; comb++) {
      scanf("%s\n", &potential[comb * 10 + (off*10)]);
    }
  }
}

void print_time() {
  char buff[100];
  time_t now = time(0);
  strftime(buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime(&now));
  printf ("%s\n", buff);
}

int solver() {
  int i, j, k, l, m, n, o, p, q;
  
  potential = malloc(9 * 362880 * 10 * sizeof(char));
  new_places = malloc(9 * 9 * sizeof(char));
  
  //print_possible_lines();
  load_possible_lines();
  
  copy_puzzle();
  
  for(i = 0; i < num_of_solutions[0]; i++) { // one for each line
    print_time();
    printf("i: %d\n", i);
    copy_line(0, &potential[i * 10 + (offset(0)*10)]);
    for(j = 0; j < num_of_solutions[1]; j++) {
      copy_line(1, &potential[j * 10 + (offset(1)*10)]);
      for(k = 0; k < num_of_solutions[2]; k++) {
	copy_line(2, &potential[k * 10 + (offset(2)*10)]);
  	for(l = 0; l < num_of_solutions[3]; l++) {
	  copy_line(3, &potential[l * 10 + (offset(3)*10)]);
  	  for(m = 0; m < num_of_solutions[4]; m++) {
	    copy_line(4, &potential[m * 10 + (offset(4)*10)]);
  	    for(n = 0; n < num_of_solutions[5]; n++) {
	      copy_line(5, &potential[n * 10 + (offset(5)*10)]);
  	      for(o = 0; o < num_of_solutions[6]; o++) {
		copy_line(6, &potential[o * 10 + (offset(6)*10)]);
  		for(p = 0; p < num_of_solutions[7]; p++) {
		  copy_line(7, &potential[p * 10 + (offset(7)*10)]);
  		  for(q = 0; q < num_of_solutions[8]; q++) {
		    copy_line(8, &potential[q * 10 + (offset(8)*10)]);
  		    if(lines_valid() && columns_valid() && squares_valid()) {
  		      return(1);
  		    }
  		  }
  		}
  	      }
  	    }
  	  }
  	}
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
