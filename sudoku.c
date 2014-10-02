#include <stdio.h>
#include <stdlib.h>

//#define RAND
#define TRYALL

int* places;
int* new_places;

void read_input() {
  
  places = malloc(9 * 9 * sizeof(int));
  
  for(int i = 0; i < 9 * 9; i++) {
    scanf("%d", &places[i]);
  }
}

void print_solution() {
  for(int i = 0; i < 9 * 9; i++) {
    printf("%d ", new_places[i]);
    if((i + 1) % 9 == 0 && i != 0) 
      printf("\n");
  }
}

void copy_puzzle() {
  for(int i = 0; i < 9 * 9; i++) {
    new_places[i] = places[i];
  }
}

void generate() {
  for(int i = 0; i < 9 * 9; i++) {
    if(new_places[i] == 0) {
      new_places [i] = rand() % 9 + 1;
    }
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
      numbers[new_places[i * 9 + j]]++;
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
      numbers[new_places[i + 9 * j]]++;
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
	  numbers[new_places[(h * 9 * 3) + i * 3 + j * 9 + k]]++;
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

void rand_solver() {
  int solved = 0;
  new_places = malloc(9 * 9 * sizeof(int));
  
  while(!solved) {
    copy_puzzle();
    generate();
    
    if(lines_valid() && columns_valid() && squares_valid())
      solved = 1;
    else
      solved = 0;
  }
}

int complete(int* new_places) {
  int i;

  for(i = 0; i < 9*9; i++) {
    if(new_places[i] == 0)
      return(0);
  }
  return(1);
}

void fill_hole(int* new_places, int n) {
  int i;

  for(i = 0; i < 9*9; i++) {
    if(new_places[i] == 0) {
      new_places[i] = n;
      break;
    }
  }
}

int tryall_solver() {
  int i;
  
  new_places = malloc(9 * 9 * sizeof(int));
  copy_puzzle();
  
  if(complete(new_places)) {
    if(!lines_valid() || !columns_valid() || !squares_valid()) {
      return(0);
    }
    if(lines_valid() || columns_valid() || squares_valid()) {
      return(1);
    }
  }
  
  else {
    for(i = 1; i < 10; i++) {
      fill_hole(new_places, i);
      if(tryall_solver())
	return(1);
    }
  }
  return(0);
}

int main(void) {
  read_input();
  
  #ifdef RAND
  rand_solver();
  print_solution();
  #endif
  
  #ifdef TRYALL
  if(tryall_solver()) {
    printf("Solved!\n");
    print_solution();
  }
  else
    printf("Unsolvable, sorry!\n");
  #endif

  return(0);
}
