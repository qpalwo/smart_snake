#include"my_h.h"
/* 判断基础食物是否可以生成
h  地图层数
*/
int base_food_judger(int x, int y, int h) {
	if (map_data[h][y][x] == 0) return 0;
	else return 1;
}

/*判断蛇前方是什么
   h   地图层数

*/
int move_judger(int x, int y, int h) {
	switch (map_data[h][y][x]){
	case 0:
		return 1;
	case SNAKE:
		int count = 1;
		snake *p1, *p2;
		p1 = snake_tail;
		while (1){
			if (p1->y == y) {
				if (p1->x == x) {
					count++;
					return count;
				}
				else {
					p2 = p1->previous;
					p1 = p2;
					count++;
				}
			}
			else {
				p2 = p1->previous;
				p1 = p2;
				count++;
			}
		}
	case BASE_FOOD:
		score++;
		food_order_data[h][y][x] = 0;
		init_base_food(h);
		return 0;
	}
}


////判断操作是否可以进行
//int judge(int x, int y, int type) {
//	switch (type) {
//	case SNAKE:
//		break;
//	case BASE_FOOD:
//		break;
//	default:
//		break;
//	}
//}

//判断出墙需要从另一侧返回
void judge_outu(int *x, int *y) {
	if (*x == MAP_WIDTH) *x -= MAP_WIDTH;
	else if (*x == -1) *x += MAP_WIDTH;
	else if (*y == MAP_LENGTH) *y -= MAP_LENGTH;
	else if (*y == -1) *y += MAP_LENGTH;
}