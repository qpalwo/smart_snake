#pragma once
#ifndef MY_H_H_INCLUDED
#define MY_H_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <time.h>
#include <conio.h>

//速度选择
#define SPEED_NORMAL 150
#define SPEED_FAST 75
#define SPEED_SLOW 250

//地图大小
#define MAP_WIDTH 40     //x
#define MAP_LENGTH 30    //y
#define MAP_HEIGHT 1  

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

//结构体大小
#define SIZEOF_SNAKE sizeof(snake)

//地图
extern int map_data[MAP_HEIGHT][MAP_LENGTH][MAP_WIDTH];

//食物优先级
extern int food_order_data[MAP_HEIGHT][MAP_LENGTH][MAP_WIDTH];

//记分板
extern int score;

//键盘检测缓存
int key_temp[4];

//函数作用域拓展
void init_core(int h);
void main_printer(int type, int x, int y);
void gotoxy(int x, int y);
void move();
int random_num();
int base_food_judger(int x, int y, int h);
void init_base_food(int h);
int move_judger(int x, int y, int h);

//全局速度
extern int speed;

#endif // MY_H_H_INCLUDED