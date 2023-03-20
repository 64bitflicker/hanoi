#ifndef __TOWEROFHANOI_H__
#define __TOWEROFHANOI_H__
// (非递归)汉诺塔

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


#endif //__TOWEROFHANOI_H__
