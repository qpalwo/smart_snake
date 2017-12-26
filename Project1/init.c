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

void init_sna_tomap(int h) {
	snake *p1 = snake_head;
	snake *p2 = NULL;
	do {
		map_data[h][p1->y][p1->x] = SNAKE;
		p2 = p1->next;
		p1 = p2;
	} while (p1 != NULL);
}

void init_map(int floor) {
	for (int i = 0; i < MAP_LENGTH; i++)
		for (int j = 0; j < MAP_WIDTH; j++) {
			switch (map_data[floor][i][j]) {
			case SNAKE:
				main_printer(SNAKE, j, i);
				break;
			case 0:
				gotoxy(j, i);
				printf("  ");
				break;
			case BASE_FOOD:
				main_printer(BASE_FOOD, j, i);
				break;
			case WALL:
				main_printer(WALL, j, i);
				break;
			default:
				break;
			}
		}
}

//clean map
void clean_map(int h) {
	for (int i = 0; i < MAP_LENGTH; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map_data[h][i][j] = 0;
}

//初始化选择菜单
void init_menu() {
	clean_map(0);
	init_snake();
	for (int i = 0; i < 8; i++) {
		main_printer(WALL, (2 * MAP_WIDTH / 5) + i, MAP_LENGTH / 5 - 1);
		main_printer(WALL, (2 * MAP_WIDTH / 5) + i, MAP_LENGTH / 5 + 1);
		map_data[0][MAP_LENGTH / 5 - 1][(2 * MAP_WIDTH / 5) + i] = WALL;
		map_data[0][MAP_LENGTH / 5 + 1][(2 * MAP_WIDTH / 5) + i] = WALL;
	}
	init_sna_tomap(0);
	init_map(0);
	main_printer(NEW_GAME, (2 * MAP_WIDTH / 5) - 1, MAP_LENGTH / 5);
	map_data[0][MAP_LENGTH / 5][(2 * MAP_WIDTH / 5) - 1] = NEW_GAME;
	gotoxy((2 * MAP_WIDTH / 5) + 1, MAP_LENGTH / 5);
	printf("新游戏");
	move(0);
}

//初始化关卡一
void init_one() {
	clean_map(1);
	init_snake();
	init_sna_tomap(1);
	aoto_make_wall(1, 1);
	init_map(1);
	item_choose(BASE_FOOD, 1);
	Sleep(2000);
	move(1);
}

//地图跳转函数
void jump_to(int floor) {
	switch (floor){
	case MENU:
		system("cls");
		init_menu();
		break;
	case FLOOR_ONE:
		system("cls");
		init_one();
	default:
		break;
	}
}

//  h   地图层数
void init_core(int h) {
	/*init_snake();
	init_sna_tomap(h);
	aoto_make_wall(h, 1);
	init_map(h);
	item_choose(BASE_FOOD, h);
	Sleep(2000);*/
	init_menu();
}