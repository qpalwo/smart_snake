#include "my_h.h"
void SetColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (ForeColor % 16) | (BackGroundColor % 16 * 16));
}

//光标移动函数
void gotoxy(int x, int y) {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	COORD c;
	c.X = x * 2;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//打印基本蛇的身体
void printer_snake_body_1(int x, int y) {
	gotoxy(x, y);
	SetColor(rand()% 50, rand() % 50);
	printf("■");
	SetColor(7, 0);
}

//测量蛇身长度
int length_of_snake() {
	snake *p1 = snake_head;
	int count = 1;
	while (p1->next != NULL){
		count++;
		p1 = p1->next;
	}
	return count;
}

/*  
输出函数，type 即输出的类型
*/
void main_printer(int type, int x, int y) {
	switch (type) {
	case SNAKE:
		printer_snake_body_1(x, y);
		break;
	case BASE_FOOD:
		gotoxy(x, y);
		printf("☉");
		break;
	case LAND_MINE:
		gotoxy(x, y);
		printf("⊕");
		break;
	case POISON_WEED:
		gotoxy(x, y);
		printf("※");
		break;
	case WALL:
		gotoxy(x, y);
		printf("◆");
		break;
	case 461:
		gotoxy(x, y);
		SetColor(100, 461);
		printf("88");
		break;
	case NEW_GAME:
	case CONTINUE_PLAY:
	case RANKING_LIST:
		gotoxy(x, y);
		printf("NN");
		break;
	default:
		break;
	}
}


//自动生成item
void auto_make_item(int h) {
	if (h != 0) {
		int key = rand() % 300;
		switch (key) {
		case 201:
			item_choose(LAND_MINE, h);
			break;
		case 78:
			item_choose(POISON_WEED, h);
			break;
		default:
			break;
		}
	}
}

/*随机地图生成
leval 复杂程度
*/
void aoto_make_wall(int h, int leval) {
	int count = 0;
	int sum = ((MAP_WIDTH * MAP_LENGTH) / 20) * leval;   //生成墙的总数
	int choose = 0;
	while (count <= sum)
	{
		choose = rand() % 4 + 1;
		for (int i = 0; i < leval; i++) {
			if (choose == 1) {                //生成障碍物为横向
				int temp = (rand() % (leval * 2 + 4));  //生成的单个障碍物的长度
				int x = rand() % MAP_WIDTH;
				int y = rand() % MAP_LENGTH;
				for (int j = 0; j < temp; j++) {
					if (x + j <= MAP_WIDTH) {
						map_data[h][y][x + j] = WALL;
						count++;
					}
					else break;
				}
			}
			else if (choose == 2) {           //生成障碍物为纵向
				int temp = (rand() % (leval * 2 + 4));  //生成的单个障碍物的长度
				int x = rand() % MAP_WIDTH;
				int y = rand() % MAP_LENGTH;
				for (int j = 0; j < temp; j++) {
					if (y + j <= MAP_LENGTH) {
						map_data[h][y + j][x] = WALL;
						count++;
					}
					else break;
				}
			}
			else if (choose == 3) {           //生成障碍物为斜右上
				int temp = (rand() % (leval * 2 + 4));  //生成的单个障碍物的长度
				int x = rand() % MAP_WIDTH;
				int y = rand() % MAP_LENGTH;
				for (int j = 0; j < temp; j++) {
					if (y + j <= MAP_LENGTH && x + j <= MAP_WIDTH) {
						map_data[h][y + j][x + j] = WALL;
						count++;
					}
					else break;
				}
			}
		}
	}
}

/*蛇头插入函数
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

/* 尾巴删除函数
num 要删除的尾巴节数
h 第几层地图
*/
void delete_tail(int num, int h) {
	snake *p1 = NULL, *p2 = NULL;
	p1 = snake_tail;
	if (num != 0) {
		for (int i = 0; i < num; i++) { 
			if (p1 == NULL) p1 = snake_tail;
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
	assert(snake_tail);
}

//键盘缓存数组复位函数
void init_key_temp() {
	for (int i = 0; i < 2; i++) {
		key_temp[i] = key_temp[i + 2];
		key_temp[i + 2] = 0;
	}
}

/*
键盘输入状态缓存判断
*/
char key_input_detec(int h) {
	//键盘输入内容输入缓存数组
	key_temp[2] = _getch();
	if (key_temp[2] == 224) key_temp[3] = _getch();
	//当使用功能键时的检测（包含回头和加速）
	if (key_temp[0] == 224 && key_temp[2] == 224) {
		if (key_temp[3] == LEFT) {
			if (key_temp[1] == RIGHT) {
				speed += 10;
				return RIGHT;
			}
			else if (key_temp[1] == LEFT) {
				speed -= 20;
				init_key_temp();
				return LEFT;
			}
			else {
				init_key_temp();
				return key_temp[1];
			}
		}
		else if (key_temp[3] == RIGHT) {
			if (key_temp[1] == LEFT) {
				speed += 10;
				return LEFT;
			}
			else if (key_temp[1] == RIGHT) {
				speed -= 20;
				init_key_temp();
				return RIGHT;
			}
			else {
				init_key_temp();
				return key_temp[1];
			}
		}
		else if (key_temp[3] == UP) {
			if (key_temp[1] == DOWN) {
				speed += 10;
				return DOWN;
			}
			else if (key_temp[1] == UP) {
				speed -= 20;
				init_key_temp();
				return UP;
			}
			else {
				init_key_temp();
				return key_temp[1];
			}
		}
		else if (key_temp[3] == DOWN) {
			if (key_temp[1] == UP) {
				speed += 10;
				return UP;
			}
			else if (key_temp[1] == DOWN) {
				speed -= 20;
				init_key_temp();
				return DOWN;
			}
			else {
				init_key_temp();
				return key_temp[1];
			}
		}
	}
	//使用非功能键时的加速检测
	/*else if (key_temp[0] != 224 && key_temp[2] != 224) {
		speed -= 20;
		init_key_temp();
		return key_temp[0];
	}*/   //  此功能严重不正常，先屏蔽
	//使用非功能键时的回头检测
	else if (key_temp[2] == A) {
		if (key_temp[0] == D) {
			return D;
		}
		else {
			init_key_temp();
			return key_temp[0];
		}
	}
	else if (key_temp[2] == D) {
		if (key_temp[0] == A) {
			return A;
		}
		else {
			init_key_temp();
			return key_temp[0];
		}
	}
	else if (key_temp[2] == W) {
		if (key_temp[0] == S) {
			return S;
		}
		else {
			init_key_temp();
			return key_temp[0];
		}
	}
	else if (key_temp[2] == S) {
		if (key_temp[0] == W) {
			return W;
		}
		else {
			init_key_temp();
			return key_temp[0];
		}
	}
	//功能键与WASD同时使用的情况……   emmmm，此处忽略
	//只做了由wasd换到上下左右的衔接，其它都没实现
	else if (key_temp[0] != 224 && key_temp[2] == 224) {
		init_key_temp();
		return key_temp[1];
	}
	//测试自动寻路
	else if (key_temp[2] == 102) {
		int path[100][2] = {0};
		search_main(h, path);
		for (int i = 0; i < 100; i++)
			printf("%d   %d  \t", path[i][0], path[i][1]);
		system("pause");
	}
	else if (key_temp[2] == 8) {
		system("cls");
		gotoxy(20, 20);
		printf("1. 保存 2. 返回游戏");
		int choose = 0;
		scanf_s("%d", &choose);
		switch (choose) {
		case 1:
			user1->score = score;
			user1->state = now_state;
			user_info_save(1, 0);
			map_data_save();
			jump_to(MENU);
			break;
		case 2:
			init_map(now_state);
			break;
		}
	}
	//P 118
}

//任意门
int* any_door(int x, int y, int h ) {
	int kb = _getch();
	if (kb == 224) kb = _getch();
	switch (kb){
	case UP:
	case W:
		
		break;
	case DOWN:
	case S:
		break;
	case LEFT:
	case A:
		break;
	case RIGHT:
	case D:
		break;
	default:
		break;
	}
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
		fresh_score();
		insert_head(snake_head->x, snake_head->y - 1, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		if(d_s < length_of_snake())
			delete_tail(d_s, h);
		break;
	case LEFT:
	case A:
		d_s = move_judger(snake_head->x - 1, snake_head->y, h);
		fresh_score();
		insert_head(snake_head->x - 1, snake_head->y, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		if (d_s < length_of_snake())
			delete_tail(d_s, h);
		break;
	case DOWN:
	case S:
		d_s = move_judger(snake_head->x, snake_head->y + 1, h);
		fresh_score();
		insert_head(snake_head->x, snake_head->y + 1, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		if (d_s < length_of_snake())
			delete_tail(d_s, h);
		break;
	case RIGHT:
	case D:
		d_s = move_judger(snake_head->x + 1, snake_head->y, h);
		fresh_score();
		insert_head(snake_head->x + 1, snake_head->y, h);
		printer_snake_body_1(snake_head->x, snake_head->y);
		if (d_s < length_of_snake())
			delete_tail(d_s, h);
		break;
	default:
		break;
	}
}

/*  蛇能移动的基础
h  地图层数

*/
void move(int h) {
	char direct = RIGHT;
	key_temp[0] = 224;
	key_temp[1] = RIGHT;
	while (1) {
		if (_kbhit()) direct = key_input_detec(h);
		while (!_kbhit()) {
			keep_move(direct, h);
			auto_make_item(h);
			if (speed <= 90) speed = 90;
			Sleep(speed);
		}
	}
}

