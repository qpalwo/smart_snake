#include "my_h.h"

//地图数组
int map_data[MAP_HEIGHT][MAP_LENGTH][MAP_WIDTH] = { 0 };

//计分
int score = 0;

//速度
int speed = SPEED_NORMAL;

//键盘检测缓存
int key_temp[4] = {0};
