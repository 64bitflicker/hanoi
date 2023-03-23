#include "hanoi.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define call(...) ({ *(++top) = (Frame) { .pc = 0, __VA_ARGS__ }; })
#define ret() ({ top--; })
#define goto(loc) ({ f->pc = (loc) - 1; })

// 定义调用栈
typedef struct {
	int pc, n;
	e_layer_t from, to, via;
} Frame;

void hanoi_unrecursion_calc(int n, e_layer_t from, e_layer_t to, e_layer_t via, void (*move)(e_layer_t, e_layer_t)) {
	// 定义调用栈
	Frame stk[64], *top = stk - 1;

	call(n , from, to, via);
	for (Frame *f; (f = top) >= stk; f->pc++) {
		n = f->n;
		from = f->from;
		to = f->to;
		via = f->via;
		switch (f->pc) {
			case 0:
				if(n == 1) {
					move(from, to);
					goto(4);
				} break;
			case 1:
				call(n - 1, from, via, to);
				break;
			case 2:
				call(1, from, to, via);
				break;
			case 3:
				call(n - 1, via, to, from);
				break;
			case 4:
				ret();
				break;
			default: assert(0);
		}
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
