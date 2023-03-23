#include "hanoi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void hanoi_recursion_calc(int n, e_layer_t from, e_layer_t to, e_layer_t via, void (*move)(e_layer_t, e_layer_t)) {
 	if (n == 1) {  
		move(from, to);
	} else {
		hanoi_recursion_calc(n - 1, from, via, to, move);
		hanoi_recursion_calc(1, from, to, via, move);
		hanoi_recursion_calc(n - 1, via, to, from, move);
	}
}

#if 0
int main(int argc, char **argv) {
	int hanoi_num = 3;
	if (argc > 1) {
		hanoi_num = atoi(argv[1]);
	}
	init_hanoi(hanoi_num);
	hanoi_calc(hanoi_num, e_layer_A, e_layer_C, e_layer_B, move_callback);
	if (end_hanoi()) {
		printf("success!!!\n");
	} else {
		printf("faild!!!\n");
	}
	delete_hanoi();
	return 0;
}
#endif

