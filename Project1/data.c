#include "my_h.h"

//��ͼ����
int map_data[MAP_HEIGHT][MAP_LENGTH][MAP_WIDTH] = { 0 };

//״̬��
int statebar_data[MAP_LENGTH + 10][STATEBAR_WIDTH + 10] = { 0 };

//��ǰ��������
int now_state = 0;

//���ݼ�ʱ
long int ps_time = 0;

//�Ʒ�
int score = 0;

//�ٶ�
int speed = SPEED_NORMAL;

//���̼�⻺��
int key_temp[4] = {0};

user *user1 = NULL;

