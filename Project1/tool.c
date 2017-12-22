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

void printer_base_food(int x, int y) {
	gotoxy(x, y);
	printf("☉");
}
/*
1 普通蛇身体   2 基础食物
*/
void main_printer(int type, int x, int y) {
	switch (type){
	case 1:
		printer_snake_body_1(x, y);
		break;
	case 2:
		printer_base_food(x, y);
		break;
	default:
		break;
	}
}

//随机数生成
int random_num() {
	srand(time(NULL));
	srand(rand());
	return rand();
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
	if (num != 0) {
		for (int i = 0; i < num; i++) {
			p2 = p1->previous;
			map_data[h][p1->y][p1->x] = 0;
			gotoxy(p1->x, p1->y);
			printf("  ");
			free(p1);
			p1 = p2;
		}
	}
	p1->next = NULL;
	snake_tail = p1;
}



/*
direct 持续走的方向
h  第几层地图
*/
void keep_move(int direct, int h) {
	int d_s;  //  删除的身体节数
	switch (direct) {
	case UP:
	case W:
		d_s = move_judger(snake_head->x, snake_head->y - 1, h);
		insert_head(snake_head->x, snake_head->y - 1, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		delete_tail(d_s, 0);
		break;
	case LEFT:
	case A:
		d_s = move_judger(snake_head->x - 1, snake_head->y, h);
		insert_head(snake_head->x - 1, snake_head->y, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		delete_tail(d_s, 0);
		break;
	case DOWN:
	case S:
		d_s = move_judger(snake_head->x, snake_head->y + 1, h);
		insert_head(snake_head->x, snake_head->y + 1, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		delete_tail(d_s, 0);
		break;
	case RIGHT:
	case D:
		d_s = move_judger(snake_head->x + 1, snake_head->y, h);
		insert_head(snake_head->x + 1, snake_head->y, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		delete_tail(d_s, 0);
		break;
	default:
		break;
	}
}


void move() {
	do {
		char direct = D;
		while(kbhit()) direct = getch();
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

