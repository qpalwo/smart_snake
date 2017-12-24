#include "my_h.h"

/*
h  地图层数
choose 输出种类
*/
void make_base_item(int h, int choose) {
	int item_x, item_y;

	do {
		item_x = rand() % MAP_WIDTH;
		item_y = rand() % MAP_LENGTH;
	} while (base_item_judger(item_x, item_y, h));

	switch (choose){
	case BASE_FOOD:
		map_data[h][item_y][item_x] = BASE_FOOD;
		main_printer(BASE_FOOD, item_x, item_y);
		break;
	case LAND_MINE:
		map_data[h][item_y][item_x] = LAND_MINE;
		main_printer(LAND_MINE, item_x, item_y);
		break;
	case POISON_WEED:
		map_data[h][item_y][item_x] = POISON_WEED;
		main_printer(POISON_WEED, item_x, item_y);
		break;
	default:
		break;
	}
	
}

/* 
输出item
*/
void item_choose(int choose, int h) {
	switch (choose)	{
	case BASE_FOOD:
		make_base_item(h, BASE_FOOD);
		break;
	case LAND_MINE:
		make_base_item(h, LAND_MINE);
		break;
	case POISON_WEED:
		make_base_item(h, POISON_WEED);
		break;
	default:
		break;
	}
}