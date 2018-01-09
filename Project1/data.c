#include "my_h.h"

//地图数组
int map_data[MAP_HEIGHT][MAP_LENGTH][MAP_WIDTH] = { 0 };

//状态栏
int statebar_data[MAP_LENGTH + 10][STATEBAR_WIDTH + 10] = { 0 };

//当前所处层数
int now_state = 0;

//毒草记时
long int ps_time = 0;

//计分
int score = 0;

//速度
int speed = SPEED_NORMAL;

//键盘检测缓存
int key_temp[4] = {0};

user *user1 = NULL;

