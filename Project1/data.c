#include "my_h.h"

//��ͼ����
int map_data[MAP_HEIGHT + 20][MAP_LENGTH+ 20][MAP_WIDTH + 20] = { 0 };

//״̬��
int statebar_data[MAP_LENGTH + 10][STATEBAR_WIDTH + 10] = { 0 };

//��ǰ��������
int now_state = 0;


//�Ʒ�
int score = 0;

//�ٶ�
int speed = SPEED_NORMAL;

//���̼�⻺��
int key_temp[4] = {0};
