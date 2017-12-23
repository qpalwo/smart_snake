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
				main_printer(SNAKE, j, i);
				break;
			case 0:
				gotoxy(j, i);
				printf("  ");
				break;
			case BASE_FOOD:
				main_printer(BASE_FOOD, j, i);
			default:
				break;
			}
		}
}

//  h   µØÍ¼²ãÊý
void init_core(int h) {
	init_snake();
	init_sna_tomap(h);
	init_map(h);
	item_choose(BASE_FOOD, h);
	//item_choose(POISON_WEED, h);
}