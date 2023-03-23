#include "hanoi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {
	e_interact = 0,
	e_recursion = 1,
	e_unrecursion = 2,
};

void refresh_display() {
		printf("\x1b[H\x1b[2J");
		display_hanoi();
		sleep(1);
}

void move_callback(e_layer_t from, e_layer_t to) {
		layer_move(from, to);
		refresh_display();
}

bool hanoi_num_check(int hanoi_num, char * exe) {
		if (hanoi_num <= 0 || hanoi_num > 10) {
			printf("%s <layer> <mod>\n", exe);
			printf("args error: The number of layers is between 1 and 10!\n");
			return false;
		}
		return true;
}

bool hanoi_mod_check(int hanoi_num, char *exe) {
		if (hanoi_num >= 0 || hanoi_num <= 2) {
			return true;
		}
		printf("%s <layer> <mod>\n", exe);
		printf("args error: The mod (0 is interact) (1 recursion) (2 unrecursion)!\n");
		return false;
}

int main(int argc, char **argv) {
	int hanoi_num = 3;
	int hanoi_mod = 0;
	if (argc > 2) {
		if (!hanoi_num_check(hanoi_num = atoi(argv[1]), argv[0])) {
			return -1;
		}
		if (!hanoi_mod_check(hanoi_mod = atoi(argv[2]), argv[0])) {
			return -2;
		}
		
	} else if (argc > 1) {
		if (!hanoi_mod_check(hanoi_mod = atoi(argv[2]), argv[0])) {
			return -1;
		} 
	}

	init_hanoi(hanoi_num);
	refresh_display();

	switch (hanoi_mod) {
		case e_interact:
			hanoi_interact();
			break;
		case e_recursion:
			hanoi_recursion_calc(hanoi_num, e_layer_A, e_layer_C, e_layer_B, move_callback);
			break;
		case e_unrecursion:
			hanoi_unrecursion_calc(hanoi_num, e_layer_A, e_layer_C, e_layer_B, move_callback);
			break;
	}

	if (end_hanoi()) {
		printf("success!!!\n");
	} else {
		printf("faild!!!\n");
	}
	delete_hanoi();
	return 0;
}

