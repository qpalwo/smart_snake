#include "my_h.h"

void init_snake() {
	snake *p1, *p2;
	p2 = (snake*)malloc(SIZEOF_SNAKE);
	p2->x = INIT_SNAKE_HEADX - 1;
	p2->y = INIT_SNAKE_HEADY - 1;
	snake_head = p2;
	for (int i = 0; i < INIT_SNAKE_LENGTH - 1; i++) {
		p1 = (snake*)malloc(SIZEOF_SNAKE);
		p1->previous = p2;
		p2->next = p1;
		p1->x = p2->x - 1;
		p1->y = p2->y;
		p2 = p1;
	}
	snake_tail = p2;
	snake_head->previous = NULL;
	snake_tail->next = NULL;
}

void init_sna_tomap() {
	snake *p1 = snake_head;
	snake *p2 = NULL;
	do {
		map_data[0][p1->y][p1->x] = SNAKE;
		p2 = p1->next;
		p1 = p2;
	} while (p1 != NULL);
}

void init_map(int floor) {
	for (int i = 0; i < MAP_LENGTH; i++)
		for (int j = 0; j < MAP_WIDTH; j++) {
			switch (map_data[0][i][j]) {
			case SNAKE:
				main_printer(1, j, i);
				break;
			case 0:
				gotoxy(j, i);
				printf("  ");
				break;
			case BASE_FOOD:
				main_printer(2, j, i);
			default:
				break;
			}
		}
}

//h  地图层数
void init_base_food(int h) {
	int food_x, food_y;

	do {
		food_x = random_num() % MAP_WIDTH;
		food_y = random_num() % MAP_LENGTH;
	} while (base_food_judger(food_x, food_y, h));

	food_order_data[h][food_y][food_x] = 1;
	map_data[h][food_y][food_x] = BASE_FOOD;
	main_printer(2, food_x, food_y);
}

//  h   地图层数
void init_core(int h) {
	init_snake();
	init_sna_tomap(h);
	init_map(h);
	init_base_food(h);
}