#include"my_h.h"
/* �жϻ���item�Ƿ��������
h  ��ͼ����
*/
int base_item_judger(int x, int y, int h) {
	if (map_data[h][y][x] == 0) return 0;
	else return 1;
}

//������Ϸ

void continue_game() {
	if (user1 == NULL) {
		system("cls");
		gotoxy(17, 15);
		printf("��ǰ�޼�¼");
		Sleep(2000);
		jump_to(MENU);
	}
	else {
		map_data_read();
		init_map(now_state);
		move(now_state);
	}
}


//�ؿ���ת
extern path *find_ending;
void mission_jump() {
	if (find_ending == NULL) {
		if ((length_of_snake() >= now_state * 6 && now_state != 1)
			|| (now_state == 1 && length_of_snake() >= 8)) {
			system("cls");
			gotoxy(MAP_WIDTH / 2, MAP_LENGTH / 2);
			SetColor(1, 5);
			printf("��ϲ���أ�����");
			SetColor(7, 0);
			Sleep(2000);
			jump_to(now_state + 1009);  //��ת����һ�أ�
		}
	}
}

void init_ranking_list();
/*�ж���ǰ����ʲô
   h   ��ͼ����

*/
int move_judger(int x, int y, int h, int *p_direct) {
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
			make_base_item(BASE_FOOD, h);
			return 0;
		case LAND_MINE:
			return (length_of_snake() / 2 + 2);
		case POISON_WEED:
			speed -= 5;
			poison_weed *p_temp = ps_head;
			poison_weed *p_temp2 = NULL;
			while (p_temp->x != x || p_temp->y != y){
				p_temp2 = p_temp;
				p_temp = p_temp->next;
			}
			p_temp2->next = p_temp->next;
			free(p_temp);
			return 2;
		case WALL:
			if (user1) {
				user1->score = score;                 //���ѡ�����ײ��ǽҲ�����
				user1->state = now_state;
			}
			if (now_state != 0) {
				user_info_save(1, 0);
				score = 0;
				gotoxy(20, 15);
				printf("�㣬�����ˣ�����");
				Sleep(3000);
			}
			poison_weed_delete(h, 2);
			jump_to(MENU);
			break;
		case NEW_GAME:
			init_new_user();
			jump_to(FLOOR_ONE);
			break;
		case CONTINUE_PLAY:  //�ù�����ʱ��������  �����ùؿ�
			continue_game();
			break;
		case RANKING_LIST:
			init_ranking_list();
			break;
		case SMART_WEED:
			gotoxy(x, y);
			printf("  ");
			map_data[h][y][x] == 0;
			int temp;
			for(int i = 0; i < 3; i++)
				temp = go_on_the_way(h);
			*p_direct = temp;
			key_temp[1] = temp;
			return SMART_WEED;
		case SHOW_MODE:
			jump_to(SHOW_MODE);
			break;
		}
	}
	else return 1;
}

//�жϳ�ǽ��Ҫ����һ�෵��
void judge_outu(int *x, int *y) {
	if (*x == MAP_WIDTH) *x -= MAP_WIDTH;
	else if (*x == -1) *x += MAP_WIDTH;
	else if (*y == MAP_LENGTH) *y -= MAP_LENGTH;
	else if (*y == -1) *y += MAP_LENGTH;
}


//���²���Ϊ�Զ�Ѱ·�ǻ۲ݵ��㷨
int food_x = 15; food_y = 15;

//Ѱ��ʳ��λ��
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

//���� H
int cacl_h(int h, int x, int y) {
	int sum = 0;
	sum = abs(x - food_x) + abs(y - food_y);
	return sum;
}

//��������
int direct[4][2] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };

//��¼f�ĵ�ͼ
int f_map[MAP_LENGTH][MAP_WIDTH];

//Ѱ·���
path *find_ending = NULL;

//��ʼ��open���f_map
queue *queue_head = NULL;
void init_queue(int h) {
	find_food(h);                               //��ʼ��Ŀ��
	for (int i = 0; i < MAP_LENGTH; i++)        //��ʼ��h��ͼ
		for (int j = 0; j < MAP_WIDTH; j++) {
			f_map[i][j] = -1;
		}
	queue_head = (queue*)malloc(sizeof(queue));
	queue_head->node = (node*)malloc(sizeof(node));
	queue_head->node->father = NULL;
	queue_head->f = -2;
	queue_head->next = (queue*)malloc(sizeof(queue));
	queue_head->next->next = NULL;
	queue_head->next->node = NULL;
	queue_head->next->f = 10000;
}

//��ʼ��close��
queue *close_list_head = NULL;
void init_close_lise() {
	close_list_head = (queue*)malloc(sizeof(queue));
	close_list_head->node = queue_head->node;
	close_list_head->next = NULL;
}

//��ӵ�ǰ�ڵ㵽close��
void add_to_close(node *node) {
	queue *p1 = (queue*)malloc(sizeof(queue));
	p1->node = node;
	p1->next = close_list_head;
	close_list_head = p1;

	queue *p3 = queue_head, *p2 = NULL;

	//ceshi
	p2 = p3->next;
	if (p3->next->next != NULL) {
		p3->next = p3->next->next;
		free(p2);
	}
}

//��ӵ�ǰ�ڵ㵽open��
void add_to_open(node *node) {
	int f = 0;
	queue *p1 = queue_head, *p2 = NULL, *p3 = NULL;
	f = (node->h + node->g);
	while (f > p1->f) {
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

//�ͷ������ڴ�
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
		if(p1 != NULL)
			free(p1);
		if (p2 != NULL);
			//free(p2);
	}  //    �˴�����ʵ�ֵĲ��Ǻܺã������ڴ�й©�����⡣
}

//����·��
int try_go(int h, int x, int y, node *father) {
	if (x >= 0 && x <= MAP_WIDTH && y >= 0 && y <= MAP_LENGTH) {
		node *p2 = (node*)malloc(sizeof(node));
		if (x == food_x && y == food_y) {            //����ҵ�·��
			p2->x = x;
			p2->y = y;
			p2->h = cacl_h(h, x, y);
			p2->g = father->g + 1;
			p2->father = father;
			path *p_path = (path*)malloc(sizeof(path));
			p_path->previous = NULL;
			path *p_temp = NULL;
			while (p2) {
				p_path->x = p2->x;
				p_path->y = p2->y;
				p_temp = p_path;
				p_path = (path*)malloc(sizeof(path));
				p_temp->next = p_path;
				p_path->previous = p_temp;
				p2 = p2->father;
			}
			p_path->next = NULL;
			p_path->previous->next = NULL;
			find_ending = p_path->previous;
			free(p_path);
			free_all();
			return -1;
		}
		int *p_x = &x;
		int *p_y = &y;
		judge_outu(p_x, p_y);

		if (map_data[h][y][x] != 0) return 1;    //�����ǽ��out
		queue *p1 = close_list_head;
		while (p1) {
			if (x == p1->node->x && y == p1->node->y) {   //����Ѿ���������out
				father = p1->node->father;
				return 1;
			}
			else p1 = p1->next;
		}
		p2->x = x;
		p2->y = y;
		p2->h = cacl_h(h, x, y);
		p2->g = father->g + 1;
		p2->father = father;
		if (f_map[y][x] != -1 && (p2->h + p2->g) >= f_map[y][x]) return 1;   //����и��õ�·����out
		f_map[y][x] = (p2->h + p2->g);
		//Sleep(50);
		add_to_open(p2);
		//main_printer(461, x, y);
		return 0;
	}
}

//Ѱ·������
int search_main(int h) {
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
		//if (queue_head->next == NULL) return -1;
		if (queue_head->next == NULL) {
			node *p_1 = close_list_head->next->node;
			queue *p1 = close_list_head->next;
			close_list_head->next = close_list_head->next->next;
			free(p1);
			add_to_open(p_1);
			for (int i = 0; i < MAP_LENGTH; i++)        //��ʼ��h��ͼ
				for (int j = 0; j < MAP_WIDTH; j++) {
					f_map[i][j] = -1;
				}
		}
		p1 = queue_head->next->node;
		if (queue_head->next->next == NULL) return -1;
		add_to_close(p1);
		int temp = 0;
		search = temp = try_go(h, p1->x, p1->y + 1, p1);
		if (temp == -1) return 0;
		search &= temp = try_go(h, p1->x, p1->y - 1, p1);
		if (temp == -1) return 0;
		search &= temp = try_go(h, p1->x + 1, p1->y, p1);
		if (temp == -1) return 0;
		search &= temp = try_go(h, p1->x - 1, p1->y, p1);
		if (temp == -1) return 0;
		if (search != 0) {
			queue *p2 = queue_head->next;
			queue_head->next = queue_head->next->next;
			free(p2);
		}
	}
	return 1;
}



