// 汉诺塔
#include "hanoi.h"
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
