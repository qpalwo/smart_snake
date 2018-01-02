#pragma once
#ifndef MY_H_H_INCLUDED
#define MY_H_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <assert.h>

//�ٶ�ѡ��
#define SPEED_NORMAL 150
#define SPEED_FAST 75
#define SPEED_SLOW 250

//��ͼ��С
#define MAP_WIDTH 40     //x
#define MAP_LENGTH 30    //y
#define MAP_HEIGHT 2  
#define STATEBAR_WIDTH 15

//init snake head location
#define INIT_SNAKE_HEADX 10
#define INIT_SNAKE_HEADY 15


//init snake length
#define INIT_SNAKE_LENGTH 4

//��ֵ
#define W 119
#define A 97
#define S 115
#define D 100
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

//��ͼ����
#define SNAKE 1001
#define BASE_FOOD 1002
#define LAND_MINE 1003
#define POISON_WEED 1004
#define WALL 1005
#define NEW_GAME 1006
#define FLOOR_ONE 1007
#define MENU 1008


//�ߵĽṹ��
typedef struct snake_body {
	int x;
	int y;
	struct snake_body *next;
	struct snake_body *previous;
}snake;

//��ͷ
snake *snake_head;

//��β
snake *snake_tail;

//�ṹ���С
#define SIZEOF_SNAKE sizeof(snake)

//��ͼ
extern int map_data[MAP_HEIGHT + 20][MAP_LENGTH + 20][MAP_WIDTH + 20];

//�Ƿְ�
extern int statebar_data[MAP_LENGTH + 10][STATEBAR_WIDTH + 10];
extern int score;

extern int now_state;

//���̼�⻺��
int key_temp[4];

//������������չ
void init_core(int h);
void main_printer(int type, int x, int y);
void gotoxy(int x, int y);
void move(int h);
int base_item_judger(int x, int y, int h);
void item_choose(int choose, int h);
int move_judger(int x, int y, int h);
void aoto_make_wall(int h, int leval);
void jump_to(int floor);
void SetColor(unsigned short ForeColor, unsigned short BackGroundColor);
void fresh_score();
int length_of_snake();
int search_main(int h, int(*path)[2]);
void init_new_user();
void user_info_save(int mode);
int map_data_save();
int map_data_read();
void init_map(int floor);

//ȫ���ٶ�
extern int speed;

//�ڵ�ṹ��
typedef struct search_node {
	int x;
	int y;
	int h;
	int g;
	struct search_node *father;
}node;

typedef struct queue_node {
	node *node;
	struct queue_node *next;
	int f;
}queue;

//�û���Ϣ
typedef struct user_information {
	int state;
	int score;
	char name[20];
	struct user_information *next;
}user;

user *user1;

#endif // MY_H_H_INCLUDED