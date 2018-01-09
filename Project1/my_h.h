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

//速度选择
#define SPEED_NORMAL 150
#define SPEED_FAST 75
#define SPEED_SLOW 250

//地图大小
#define MAP_WIDTH 40     //x
#define MAP_LENGTH 30    //y
#define MAP_HEIGHT 10  
#define STATEBAR_WIDTH 15

//init snake head location
#define INIT_SNAKE_HEADX 10
#define INIT_SNAKE_HEADY 15


//init snake length
#define INIT_SNAKE_LENGTH 4

//键值
#define W 119
#define A 97
#define S 115
#define D 100
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

//地图内容
#define SNAKE 1001
#define BASE_FOOD 1002
#define LAND_MINE 1003
#define POISON_WEED 1004
#define WALL 1005
#define NEW_GAME 1006
#define CONTINUE_PLAY 1007
#define MENU 1008
#define FLOOR_ONE 1009
#define FLOOR_TWO 1010
#define FLOOR_THREE 1011
#define FLOOR_FOUR 1012
#define FLOOR_FIVE 1013
#define USER_CHOOSE 1014
#define RANKING_LIST 1015
#define SMART_WEED 1016
#define SHOW_MODE 1017



//蛇的结构体
typedef struct snake_body {
	int x;
	int y;
	struct snake_body *next;
	struct snake_body *previous;
}snake;

//蛇头
snake *snake_head;

//蛇尾
snake *snake_tail;


//毒草链表
typedef struct poison_weed_list{
	int x; 
	int y;
	struct poison_weed_list *next;
}poison_weed;

poison_weed *ps_head;

extern int ps_time;

//结构体大小
#define SIZEOF_SNAKE sizeof(snake)

//地图
extern int map_data[MAP_HEIGHT][MAP_LENGTH][MAP_WIDTH];

//记分板
extern int statebar_data[MAP_LENGTH + 10][STATEBAR_WIDTH + 10];
extern int score;

extern int now_state;

//键盘检测缓存
int key_temp[4];

//函数作用域拓展
void init_core(int h);
void main_printer(int type, int x, int y);
void gotoxy(int x, int y);
void move(int h);
int base_item_judger(int x, int y, int h);
void make_base_item(int choose, int h);
int move_judger(int x, int y, int h, int *p_direct);
void aoto_make_wall(int h, int leval);
void jump_to(int floor);
void SetColor(unsigned short ForeColor, unsigned short BackGroundColor);
void fresh_score();
int length_of_snake();
int search_main(int h);
int go_on_the_way(int h);
void init_new_user();
void user_info_save(int mode, int choose_id);
int map_data_save();
int map_data_read();
void init_map(int floor);
void poison_weed_delete(int h, int mode);

//全局速度
extern int speed;

//节点结构体
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

//用户信息
typedef struct user_information {
	int state;
	int score;
	char name[20];
	int id;
	struct user_information *next;
}user;

extern user *user1;

//路径信息
typedef struct path_node {
	int x;
	int y;
	struct path_node *next;
	struct path_node *previous;
}path;

extern path *find_ending;


#endif // MY_H_H_INCLUDED