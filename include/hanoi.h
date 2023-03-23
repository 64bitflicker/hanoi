#ifndef __HANOI_H__
#define __HANOI_H__

#define false 0
#define true  1
typedef int bool;

typedef enum {
	e_layer_A = 0,
	e_layer_B = 1,
	e_layer_C = 2,
	e_layer_NUM = 3,
} e_layer_t;

// layer
typedef struct _layer_t {
	int layer_id;
	struct _layer_t *up;
	struct _layer_t *down;
} layer_t;

// tower
typedef struct {
	int layer_num;
	layer_t *tower[e_layer_NUM];
 } tower_t;

extern tower_t g_tower;

// function
void init_hanoi(int layer_num);
void delete_hanoi();
bool end_hanoi();
bool layer_move(e_layer_t src, e_layer_t dest);
void display_hanoi();

void hanoi_interact();
void hanoi_recursion_calc(int n, e_layer_t from, e_layer_t to, e_layer_t via, void (*move)(e_layer_t, e_layer_t));
void hanoi_unrecursion_calc(int n, e_layer_t from, e_layer_t to, e_layer_t via, void (*move)(e_layer_t, e_layer_t));


#endif //__HANOI_H__
