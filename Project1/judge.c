#include"my_h.h"
/* 判断基础item是否可以生成
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
	if (x >= 0 && y >= 0) {
		switch (map_data[h][y][x]) {
		case 0:
			return 1;
		case SNAKE:
			int count = 1;
			snake *p1, *p2 = NULL;
			p1 = snake_tail;
			assert(p1);
			while (1) {
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
			speed -= 5;
			return 2;
		case WALL:
			gotoxy(20, 15);
			printf("你，你输了！！！");
			Sleep(3000);
			jump_to(MENU);
			break;
		case NEW_GAME:
			jump_to(FLOOR_ONE);
			break;
		}
	}
	else return 1;
}

//判断出墙需要从另一侧返回
void judge_outu(int *x, int *y) {
	if (*x == MAP_WIDTH) *x -= MAP_WIDTH;
	else if (*x == -1) *x += MAP_WIDTH;
	else if (*y == MAP_LENGTH) *y -= MAP_LENGTH;
	else if (*y == -1) *y += MAP_LENGTH;
}


//以下部分为自动寻路智慧草的算法



int food_x = 0; food_y = 0;
snake *virtual_h = NULL, *virtual_t = NULL;
snake v_h;

//生成虚拟蛇
void copy_snake() {
	snake *p0, *p1, *p2;
	v_h.x = snake_head->x;
	v_h.y = snake_head->y;
	v_h.previous = NULL;

	virtual_h = &v_h;
	p0 = snake_head->next;
	p2 = &v_h;
	while (p0->next != NULL){
		p1 = (snake*)malloc(SIZEOF_SNAKE);
		p1->x = p0->x;
		p1->y = p0->y;
		p1->previous = p2;
		p2->next = p1;
		p2 = p0->next;
		p0 = p2;
		p2 = p1;
	}
	p2->next = NULL;
	virtual_t = p2;
}

//寻找食物位置
int find_food(int h) {
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_LENGTH; j++) {
			if (map_data[h][j][i] == BASE_FOOD) {
				food_x = i;
				food_y = j;
				return 1;
			}
			else return 0;
		}
	}
}

//计算 H
int cacl_h(int h, int x, int y) {
	int sum = 0;
	if (find_food(h)) {
		sum = abs(x - food_x) + abs(y - food_y);
		return sum;
	}
	else return -1;
}




