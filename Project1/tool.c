#include "my_h.h"

void gotoxy(int x, int y) {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	COORD c;
	c.X = x * 2;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void printer_snake_body_1(int x, int y) {
	gotoxy(x, y);
	printf("■");
}

//判断出墙需要从另一侧返回
void judge_outu(int *x, int *y) {
	if (*x == MAP_WIDTH) *x -= MAP_WIDTH;
	else if (*x == -1) *x += MAP_WIDTH;
	else if (*y == MAP_LENGTH) *y -= MAP_LENGTH;
	else if (*y == -1) *y += MAP_LENGTH;
}

/*
x 插入蛇头的x
y 插入蛇头的y
h 第几层地图
*/
void insert_head(int x, int y, int h) {
	snake *p1;
	int *p_x = &x;
	int *p_y = &y;
	judge_outu(p_x, p_y);
	map_data[h][y][x] = SNAKE;
	p1 = (snake*)malloc(SIZEOF_SNAKE);
	p1->next = snake_head;
	p1->previous = NULL;
	snake_head->previous = p1;
	p1->x = x;
	p1->y = y;
	snake_head = p1;
}

/*
num 要删除的尾巴节数
h 第几层地图
*/
void delete_tail(int num, int h) {
	snake *p1 = NULL, *p2 = NULL;
	p1 = snake_tail;
	for (int i = 0; i < num; i++) {
		p2 = p1->previous;
		map_data[h][p1->y][p1->x] = 0;
		gotoxy(p1->x, p1->y);
		printf("  ");
		free(p1);
		p1 = p2;
	}
	p1->next = NULL;
	snake_tail = p1;
}



/*
direct 持续走的方向
h  第几层地图
*/
void keep_move(int direct, int h) {
	switch (direct) {
	case UP:
	case W:
		insert_head(snake_head->x, snake_head->y - 1, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		delete_tail(1, 0);
		break;
	case LEFT:
	case A:
		insert_head(snake_head->x - 1, snake_head->y, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		delete_tail(1, 0);
		break;
	case DOWN:
	case S:
		insert_head(snake_head->x, snake_head->y + 1, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		delete_tail(1, 0);
		break;
	case RIGHT:
	case D:
		insert_head(snake_head->x + 1, snake_head->y, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		delete_tail(1, 0);
		break;
	default:
		break;
	}
}


void move() {
	do {
		char direct = D;
		direct = getch();
		if (direct == 224) {
			direct == getch();
			while (!kbhit()) {
				keep_move(direct, 0);
				Sleep(SPEED_NORMAL);
			}
		}
		else {
			while (!kbhit()) {
				keep_move(direct, 0);
				Sleep(SPEED_NORMAL);
			}
		}
	} while (kbhit());



}

