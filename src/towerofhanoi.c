// (非递归)汉诺塔
#include "towerofhanoi.h"
#include <stdio.h>
#include <stdlib.h>

tower_t g_tower;

void init_hanoi(int layer_num) {
	layer_t *tlayer = g_tower.tower[e_layer_A];
	for (int i = 0; i < layer_num; i++) {
		tlayer = (layer_t*)malloc(sizeof(layer_t));
		tlayer->layer_id = layer_num - i;
		tlayer->up = NULL;
		tlayer->down = g_tower.tower[e_layer_A];
		if (g_tower.tower[e_layer_A]) {
			g_tower.tower[e_layer_A]->up = tlayer;
		}
		g_tower.tower[e_layer_A] = tlayer;
	}

	g_tower.tower[e_layer_B] = NULL;
	g_tower.tower[e_layer_C] = NULL;
	g_tower.layer_num = layer_num;
	return ;
}

void delete_hanoi() {
	layer_t *del = NULL;

	while(g_tower.tower[e_layer_A] != NULL) {
		del = g_tower.tower[e_layer_A];
		g_tower.tower[e_layer_A] = del->down;
		free(del);
	}
	
	while(g_tower.tower[e_layer_B] != NULL) {
		del = g_tower.tower[e_layer_B];
		g_tower.tower[e_layer_B] = del->down;
		free(del);
	}

	while(g_tower.tower[e_layer_C] != NULL) {
		del = g_tower.tower[e_layer_C];
		g_tower.tower[e_layer_C] = del->down;
		free(del);
	}

	return ;
}

bool end_hanoi() {
	bool ret = false;

	if (!g_tower.tower[e_layer_C] ||  g_tower.tower[e_layer_A] || g_tower.tower[e_layer_B]) {
		// 失败
		goto ERR;
	}

	layer_t *tlayer = g_tower.tower[e_layer_C];
	for (int i = 1; tlayer != NULL; i++) {
		if (tlayer->layer_id != i) goto ERR;
		tlayer = tlayer->down;
	}
	
	ret = true;

ERR:
//	delete_hanoi();

	return ret;
}

bool layer_move(e_layer_t src, e_layer_t dest) {
	if (g_tower.tower[src] == NULL || src == dest) return false;

	layer_t *src_layer = g_tower.tower[src];
	layer_t *dest_layer = g_tower.tower[dest];
	
	// 判断是否可以移动
	if (dest_layer != NULL && src_layer->layer_id > dest_layer->layer_id) {
		return false;
	}

	// 取出
	g_tower.tower[src] = src_layer->down;
	if (g_tower.tower[src] != NULL)	g_tower.tower[src]->up = NULL;
	// 放入
	src_layer->down = dest_layer;
	if (dest_layer != NULL) dest_layer->up = src_layer;
	g_tower.tower[dest] = src_layer;
	
	return true;
}

void display_hanoi() {
	layer_t *tmp_layer = NULL;

	printf("**************** A ****************\n");
	tmp_layer = g_tower.tower[e_layer_A];
	while (tmp_layer != NULL) {
		printf (" %d ", tmp_layer->layer_id);
		for(int i = 0; i < g_tower.layer_num - tmp_layer->layer_id; i++) {
			printf ("%s", "   ");
		}
		for(int i = 0; i < tmp_layer->layer_id; i++) {
			printf ("%s", "▇▇▇");
			printf ("%s", "▇▇▇");
		}
		printf ("\n");
		tmp_layer = tmp_layer->down;
	}

	printf("**************** B ****************\n");
	tmp_layer = g_tower.tower[e_layer_B];
	while (tmp_layer != NULL) {
		printf (" %d ", tmp_layer->layer_id);
		for(int i = 0; i < g_tower.layer_num - tmp_layer->layer_id; i++) {
			printf ("%s", "   ");
		}
		for(int i = 0; i < tmp_layer->layer_id; i++) {
			printf ("%s", "▇▇▇");
			printf ("%s", "▇▇▇");
		}
		printf ("\n");
		tmp_layer = tmp_layer->down;
	}

	printf("**************** C ****************\n");
	tmp_layer = g_tower.tower[e_layer_C];
	while (tmp_layer != NULL) {
		printf (" %d ", tmp_layer->layer_id);
		for(int i = 0; i < g_tower.layer_num - tmp_layer->layer_id; i++) {
			printf ("%s", "   ");
		}
		for(int i = 0; i < tmp_layer->layer_id; i++) {
			printf ("%s", "▇▇▇");
			printf ("%s", "▇▇▇");
		}
		printf ("\n");
		tmp_layer = tmp_layer->down;
	}
	return ;
}

bool hanoi() {
#if 0
	display_hanoi();
	printf("=======================> move A->C %d \n", layer_move(e_layer_A, e_layer_C));
	display_hanoi();
	printf("=======================> move A->B %d \n", layer_move(e_layer_A, e_layer_B));
	display_hanoi();
	printf("=======================> move C->B %d \n", layer_move(e_layer_C, e_layer_B));
	display_hanoi();
	printf("=======================> move A->C %d \n", layer_move(e_layer_A, e_layer_C));
	display_hanoi();
	printf("=======================> move B->A %d \n", layer_move(e_layer_B, e_layer_A));
	display_hanoi();
	printf("=======================> move B->C %d \n", layer_move(e_layer_B, e_layer_C));
	display_hanoi();
	printf("=======================> move A->C %d \n", layer_move(e_layer_A, e_layer_C));
	display_hanoi();
#endif
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
	//g_tower.tower[e_layer_C] = g_tower.tower[e_layer_A];
	//g_tower.tower[e_layer_A] = NULL;
	//display_hanoi();

	return end_hanoi();
}

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
