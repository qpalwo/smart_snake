#include"my_h.h"
/* 判断基础食物是否可以生成
h  地图层数
*/
int base_item_judger(int x, int y, int h) {
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
		snake *p1 = snake_tail, *p2 = NULL;
		while (1){
			if (p1->y == y) {
				if (p1->x == x) {
					count += 3;
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
		item_choose(BASE_FOOD, h);
		return 0;
	case LAND_MINE:
		score /= 2;
		int snake_length = 4;
		p1 = snake_head;
		p2 = NULL;
		while (p1->next != NULL) {
			snake_length++;
			p2 = p1->next;
			p1 = p2;
		}
		return (snake_length / 2);
	case POISON_WEED:
		return 2;
	}
}

//判断出墙需要从另一侧返回
void judge_outu(int *x, int *y) {
	if (*x == MAP_WIDTH) *x -= MAP_WIDTH;
	else if (*x == -1) *x += MAP_WIDTH;
	else if (*y == MAP_LENGTH) *y -= MAP_LENGTH;
	else if (*y == -1) *y += MAP_LENGTH;
}