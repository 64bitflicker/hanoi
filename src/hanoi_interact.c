// (交互)汉诺塔
#include "hanoi.h"
#include <stdio.h>
#include <stdlib.h>

void hanoi_interact() {
	bool running = true;
	char ch[2] = { 0 };
	e_layer_t layer[2] = { e_layer_NUM };
	 while(running) {
		ch[0] = ch[1] = -1;
		layer[0] = layer[1] = e_layer_NUM;
		printf("\x1b[H\x1b[2J");
		display_hanoi();
		if (end_hanoi()) {
			break;
		}
		printf("enter your action (a->b/A->B):\n");
		scanf("%c->%c", &ch[0], &ch[1]);
		
		if(ch[0] == 'q' || ch[0] == 'Q') {
			break;
		}

		switch(ch[0]) {
			case 'A':
			case 'a':
				layer[0] = e_layer_A;
				break;
			case 'B':
			case 'b':
				layer[0] = e_layer_B;
				break;
			case 'C':
			case 'c':
				layer[0] = e_layer_C;
				break;
		}

		switch(ch[1]) {
			case 'A':
			case 'a':
				layer[1] = e_layer_A;
				break;
			case 'B':
			case 'b':
				layer[1] = e_layer_B;
				break;
			case 'C':
			case 'c':
				layer[1] = e_layer_C;
				break;
		}

		if (layer[0] != e_layer_NUM && layer[1] != e_layer_NUM) {
			layer_move(layer[0], layer[1]);
		}
	}
	return ;
}

#if 0
int main(int argc, char **argv) {
	int num = 3;
	if (argc > 1) {
		num = atoi(argv[1]);
	}
	bool success = false;
	init_hanoi(num);
	success = hanoi();
	delete_hanoi();
	printf("end, you game is %d\n", success);
	return 0;
}
#endif
