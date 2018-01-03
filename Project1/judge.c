#include"my_h.h"
/* 判断基础item是否可以生成
h  地图层数
*/
int base_item_judger(int x, int y, int h) {
	if (map_data[h][y][x] == 0) return 0;
	else return 1;
}

//继续游戏

void continue_game() {
	if (user1 == NULL) {

	}
	else {
		map_data_read();
		init_map(now_state);
		move(now_state);
	}
}


//关卡跳转
void mission_jump() {
	if (length_of_snake() >= now_state * 5) {
		system("cls");
		gotoxy(MAP_WIDTH / 2, MAP_LENGTH / 2);
		SetColor(1, 5);
		printf("恭喜过关！！！");
		SetColor(7, 0);
		Sleep(2000);
		jump_to(now_state + 1009);  //跳转到下一关；
	}
}

void init_ranking_list();
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
			mission_jump();
			item_choose(BASE_FOOD, h);
			return 0;
		case LAND_MINE:
			//score /= 2;
			return (length_of_snake() / 2 + 2);
		case POISON_WEED:
			speed -= 5;
			return 2;
		case WALL:
			gotoxy(20, 15);
			printf("你，你输了！！！");
			score = 0;
			Sleep(3000);
			jump_to(MENU);
			break;
		case NEW_GAME:
			init_new_user();
			jump_to(FLOOR_ONE);
			break;
		case CONTINUE_PLAY:  //该功能暂时留待完善  先做好关卡
			continue_game();
			break;
		case RANKING_LIST:
			init_ranking_list();
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
int food_x = 15; food_y = 15;

//寻找食物位置
int find_food(int h) {
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_LENGTH; j++) {
			if (map_data[h][j][i] == BASE_FOOD) {
				food_x = i;
				food_y = j;
				return 1;
			}
		}
	}
}

//计算 H
int cacl_h(int h, int x, int y) {
	int sum = 0;
	//if (find_food(h)) {
		sum = abs(x - food_x) + abs(y - food_y);
		return sum;
	//}
	//else return -1;
}

//方向向量
int direct[4][2] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };



//记录f的地图
int f_map[MAP_LENGTH][MAP_WIDTH];

//初始化open表和f_map
queue *queue_head = NULL;
void init_queue(int h) {
	find_food(h);                               //初始化目标
	for (int i = 0; i < MAP_LENGTH; i++)        //初始化h地图
		for (int j = 0; j < MAP_WIDTH; j++) {
			f_map[i][j] = -1;
		}
	queue_head = (queue*)malloc(sizeof(queue));
	queue_head->node = (node*)malloc(sizeof(node));
	queue_head->node->father = NULL;
	//queue_head->node->x = snake_head->x;
	//queue_head->node->y = snake_head->y;
	//queue_head->node->h = cacl_h(h, snake_head->x, snake_head->y);
	//queue_head->node->g = 0;
	queue_head->f = -2;
	//f_map[snake_head->y][snake_head->x] = queue_head->f;
	queue_head->next = (queue*)malloc(sizeof(queue));
	queue_head->next->next = NULL;
	queue_head->next->node = NULL;
	queue_head->next->f = 10000;
}

//初始化close表
queue *close_list_head = NULL;
void init_close_lise() {
	close_list_head = (queue*)malloc(sizeof(queue));
	close_list_head->node = queue_head->node;
	close_list_head->next = NULL;
}

//添加当前节点到close表
void add_to_close(node *node) {
	queue *p1 = (queue*)malloc(sizeof(queue));
	p1->node = node;
	p1->next = close_list_head;
	close_list_head = p1;
}

//添加当前节点到open表
void add_to_open(node *node) {
	int f = 0;
	queue *p1 = queue_head, *p2 = NULL, *p3 = NULL;
	f = (node->h + node->g);
	while (f > p1->f){
		p2 = p1;
		p1 = p1->next;
	}
	assert(p2);
	p3 = (queue*)malloc(sizeof(queue));
	p3->f = f;
	p3->node = node;
	p3->next = p1;
	p2->next = p3;
}

//释放所有内存
void free_all() {
	queue *p1;
	node *p2;
	while (queue_head) {
		p1 = queue_head;
		p2 = queue_head->node;
		queue_head = queue_head->next;
		free(p1);
		free(p2);
	}
	while (close_list_head) {
		p1 = close_list_head;
		p2 = close_list_head->node;
		close_list_head = close_list_head->next;
		free(p1);
		free(p2);
	}
}

//尝试路径
int try_go(int h, int x, int y, node *father) {
	if (x >= 0 && x <= MAP_WIDTH && y >= 0 && y <= MAP_LENGTH) {
		if (map_data[h][y][x] != 0) return 1;    //如果是墙，out
		queue *p1 = close_list_head;
		while (p1) {
			if (x == p1->node->x && y == p1->node->y) {   //如果已经搜索过，out
				father = p1->node->father;
				return 1;
			}
			else p1 = p1->next;
		}
		node *p2 = (node*)malloc(sizeof(node));
		p2->x = x;
		p2->y = y;
		p2->h = cacl_h(h, x, y);
		p2->g = father->g + 1;
		p2->father = father;
		if (f_map[y][x] != -1 && (p2->h + p2->g) >= f_map[y][x]) return 1;   //如果有更好的路径，out
		f_map[y][x] = (p2->h + p2->g);
		Sleep(50);
		add_to_open(p2);
		main_printer(461, x, y);
		return 0;
	}
}

//寻路主函数
int search_main(int h, int(*path)[2]) {
	init_queue(h);
	init_close_lise();
	node *p1;
	p1 = (node*)malloc(sizeof(node));
	p1->x = snake_head->x;
	p1->y = snake_head->y;
	p1->h = cacl_h(h, p1->x, p1->y);
	p1->g = 0;
	p1->father = NULL;
	f_map[p1->y][p1->x] = p1->h;
	add_to_open(p1);
	while (1) {
		int search = 0;
		p1 = queue_head->next->node;
		add_to_close(p1);
		if (p1->x == food_x && p1->y == food_y) {
			int i = 0;
			while (p1) {
				path[i][0] = p1->x;
				path[i][1] = p1->y;
				i++;
				p1 = p1->father;
			}
			free_all();
			return 0;
		}
		search = try_go(h, p1->x, p1->y + 1, p1);
		search = try_go(h, p1->x, p1->y - 1, p1);
		search = try_go(h, p1->x + 1, p1->y, p1);
		search = try_go(h, p1->x - 1, p1->y, p1);
		if (search != 0) {
			//add_to_close(p1);
			queue *p2 = queue_head->next;
			queue_head->next = queue_head->next->next;
			free(p2);
		}
	}
	return 1;
}

