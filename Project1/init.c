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

void init_statebar();
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
			case POISON_WEED:
				main_printer(POISON_WEED, j, i);
				break;
			case LAND_MINE:
				main_printer(LAND_MINE, j, i);
				break;
			default:
				break;
			}
		}
	init_statebar();
}

//ˢ�·��� and user info
void fresh_score() {
	SetColor(6, 4);
	gotoxy(MAP_WIDTH + 5, 5);
	printf("�÷֣�%d", score);
	gotoxy(MAP_WIDTH + 5, 3);
	if(user1)
		printf("��ǰ��ң�%s", user1->name);
	SetColor(7, 0);
}

//��ʼ��״̬��
void init_statebar() {
	SetColor(7, 7);
	for(int i = 0; i < STATEBAR_WIDTH; i++)
		for (int j = 0; j < MAP_LENGTH; j++) {
			gotoxy(MAP_WIDTH + 1 + i, j);
			printf("  ");
		}
	SetColor(6, 7);
	gotoxy(MAP_WIDTH + 1, 0);
	for (int i = 0; i < STATEBAR_WIDTH; i++) {
		printf("��");
	}
	gotoxy(MAP_WIDTH + 1, MAP_LENGTH - 1);
	for (int i = 0; i < STATEBAR_WIDTH; i++) {
		printf("��");
	}
	for (int i = 0; i < MAP_LENGTH; i++) {
		gotoxy(MAP_WIDTH + 1, i);
		printf("||");
		gotoxy(MAP_WIDTH + 1 + STATEBAR_WIDTH, i);
		printf("||");
	}
	SetColor(7, 0);
	fresh_score();
}

//��ʼ�������
void init_new_user() {
	user1 = (user*)malloc(sizeof(user));
	system("cls");
	gotoxy((2 * MAP_WIDTH / 5) + 1, MAP_LENGTH / 5);
	printf("�����������ǳƣ�");
	scanf_s("%s", &user1->name, 20);
	//user_info_save(1);    //�洢�û���Ϣ���ļ�
}

//clean map
void clean_map(int h) {
	for (int i = 0; i < MAP_LENGTH; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map_data[h][i][j] = 0;
}

//��ʼ��ѡ��˵�
void init_menu() {
	score = 0;
	clean_map(0);
	//init_statebar();  //״̬��
	init_snake();
	for (int i = 0; i < 8; i++) {
		main_printer(WALL, (2 * MAP_WIDTH / 5) + i, MAP_LENGTH / 5 - 1);     //����Ϸ
		main_printer(WALL, (2 * MAP_WIDTH / 5) + i, MAP_LENGTH / 5 + 1);
		map_data[0][MAP_LENGTH / 5 - 1][(2 * MAP_WIDTH / 5) + i] = WALL;
		map_data[0][MAP_LENGTH / 5 + 1][(2 * MAP_WIDTH / 5) + i] = WALL;

		main_printer(WALL, (2 * MAP_WIDTH / 5) + i, 2 * MAP_LENGTH / 5 - 1);    //������Ϸ
		main_printer(WALL, (2 * MAP_WIDTH / 5) + i, 2 * MAP_LENGTH / 5 + 1);
		map_data[0][2 * MAP_LENGTH / 5 - 1][(2 * MAP_WIDTH / 5) + i] = WALL;
		map_data[0][2 * MAP_LENGTH / 5 + 1][(2 * MAP_WIDTH / 5) + i] = WALL;

		main_printer(WALL, (2 * MAP_WIDTH / 5) + i, 3 * MAP_LENGTH / 5 - 1);    //���а�
		main_printer(WALL, (2 * MAP_WIDTH / 5) + i, 3 * MAP_LENGTH / 5 + 1);
		map_data[0][3 * MAP_LENGTH / 5 - 1][(2 * MAP_WIDTH / 5) + i] = WALL;
		map_data[0][3 * MAP_LENGTH / 5 + 1][(2 * MAP_WIDTH / 5) + i] = WALL;
	}
	init_sna_tomap(0);
	init_map(0);

	main_printer(NEW_GAME, (2 * MAP_WIDTH / 5) - 1, MAP_LENGTH / 5);       //����Ϸ
	map_data[0][MAP_LENGTH / 5][(2 * MAP_WIDTH / 5) - 1] = NEW_GAME;
	gotoxy((2 * MAP_WIDTH / 5) + 1, MAP_LENGTH / 5);
	printf("����Ϸ");

	main_printer(CONTINUE_PLAY, (2 * MAP_WIDTH / 5) - 1, 2 * MAP_LENGTH / 5);       //������Ϸ
	map_data[0][2 * MAP_LENGTH / 5][(2 * MAP_WIDTH / 5) - 1] = CONTINUE_PLAY;
	gotoxy((2 * MAP_WIDTH / 5) + 1, 2 * MAP_LENGTH / 5);
	printf("������Ϸ");

	main_printer(RANKING_LIST, (2 * MAP_WIDTH / 5) - 1, 3 * MAP_LENGTH / 5);       //���а�
	map_data[0][3 * MAP_LENGTH / 5][(2 * MAP_WIDTH / 5) - 1] = RANKING_LIST;
	gotoxy((2 * MAP_WIDTH / 5) + 1, 3 * MAP_LENGTH / 5);
	printf("���а�");

	move(0);
}

//ѡ���û�����
user* user_info_read();
void init_ranking_list() {
	user *p1 = user_info_read();
	int i = 5;
	system("cls");
	gotoxy(2 * MAP_WIDTH / 5, 4);
	printf("����ǳ�");
	gotoxy(3 * MAP_WIDTH / 5, 4);
	printf("��ҵ÷�");
	gotoxy(4 * MAP_WIDTH / 5, 4);
	printf("��ҹؿ�");
	do{
		if (p1 != NULL) {
			gotoxy(2 * MAP_WIDTH / 5, i);
			printf("%s", p1->name);
			gotoxy(3 * MAP_WIDTH / 5, i);
			printf("%d", p1->score);
			gotoxy(4 * MAP_WIDTH / 5, i);
			printf("%d", p1->state);
		}
		p1 = p1->next;
		i++;
	} while (p1);
	gotoxy(3 * MAP_WIDTH / 5, i + 3);
	printf("�û����������������");
	_getch();
	jump_to(MENU);
}

//��ʼ���ؿ�
void init_mission(int h) {
	if(h == 1)score = 0;
	clean_map(h);
	init_snake();
	init_sna_tomap(h);
	aoto_make_wall(h, h);
	init_map(h);
	item_choose(BASE_FOOD, h);
	Sleep(2000);
	move(h);
}


//��ͼ��ת����
void jump_to(int floor) {
	switch (floor){
	case MENU:
		now_state = 0;
		system("cls");
		init_menu();
		break;
	case FLOOR_ONE:
		now_state = 1;
		system("cls");
		init_mission(1);
	case FLOOR_TWO:
		now_state = 2;
		system("cls");
		init_mission(2);
	case FLOOR_THREE:
		now_state = 3;
		system("cls");
		init_mission(3);
	case FLOOR_FOUR:
		now_state = 4;
		system("cls");
		init_mission(4);
	case FLOOR_FIVE:
		now_state = 5;
		system("cls");
		init_mission(5);
	default:
		break;
	}
}

//  h   ��ͼ����
void init_core(int h) {
	init_statebar();
	init_menu();
}