#pragma once
#ifndef MY_H_H_INCLUDED
#define MY_H_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <time.h>
#include <conio.h>

//�ٶ�ѡ��
#define SPEED_NORMAL 150
#define SPEED_FAST 75
#define SPEED_SLOW 250

//��ͼ��С
#define MAP_WIDTH 40     //x
#define MAP_LENGTH 30    //y
#define MAP_HEIGHT 1  

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
extern int map_data[MAP_HEIGHT][MAP_LENGTH][MAP_WIDTH];

//ʳ�����ȼ�
extern int food_order_data[MAP_HEIGHT][MAP_LENGTH][MAP_WIDTH];

//�Ƿְ�
extern int score;

//���̼�⻺��
int key_temp[4];

//������������չ
void init_core(int h);
void main_printer(int type, int x, int y);
void gotoxy(int x, int y);
void move();
int random_num();
int base_food_judger(int x, int y, int h);
void init_base_food(int h);
int move_judger(int x, int y, int h);

//ȫ���ٶ�
extern int speed;

#endif // MY_H_H_INCLUDED