#include "my_h.h"

FILE *fp;

//用户信息保存
void user_info_save(int mode) {
	user1->state = now_state;
	if (fopen_s(&fp, "user_info.xst", "a")) {
		fopen_s(&fp, "user_info.xst", "w");
	}
	switch (mode) {
	case 1:    //添加新用户
		fwrite(user1, sizeof(user), 1, fp);
		break;
	case 2:    //用户信息修改(涉及随机读取，稍后再议)
		break;
	}
	fclose(fp);
}

//用户信息读取
user* user_info_read() {
	user *p_temp;
	if (!fopen_s(&fp, "user_info.xst", "r")) {
		user *p1 = NULL;
		p1 = (user*)malloc(sizeof(user));
		p_temp = p1;
		fread(p1, sizeof(user), 1, fp);
		p1->next = NULL;
		while (!feof(fp)){
			user *p2 = (user*)malloc(sizeof(user));
			fread(p2, sizeof(user), 1, fp);
			p2->next = NULL;
			p1->next = p2;
			p1 = p2;
		}
		fclose(fp);
		return p_temp;
	}
	else return NULL;
}

//地图保存(游戏进度保存)
int map_data_save() {
	fopen_s(&fp, "temp_map_data.xst", "w");
	int i = fwrite(map_data, sizeof(map_data), 1, fp);
	fprintf(fp, "%d", now_state);
	fclose(fp);
	fopen_s(&fp, "temp_snake_data.xst", "w");
	fprintf(fp, "%d ", length_of_snake());
	snake *p1 = snake_head;
	while (p1){
		fprintf(fp, " %d %d ", p1->x, p1->y);
		p1 = p1->next;
	}
	fclose(fp);
	return i;
}

//地图读取（游戏进度读取）
int map_data_read() {
	if (!fopen_s(&fp, "temp_map_data.xst", "r")) {
		int i = fread(map_data, sizeof(map_data), 1, fp);
		fscanf_s(fp, "%d", &now_state);
		fclose(fp);
		fopen_s(&fp, "temp_snake_data.xst", "r");
		int length_of_snake = 0;
		fscanf_s(fp, "%d ", &length_of_snake);
		snake *p1 = (snake*)malloc(SIZEOF_SNAKE);
		while (snake_head) {
			snake *p3 = snake_head;
			snake_head = snake_head->next;
			free(p3);
		}
		snake_head = p1;
		snake *p2 = NULL;
		p1->previous = NULL;
		for (int i = 0; i < length_of_snake; i++) {
			p2 = (snake*)malloc(sizeof(snake));
			fscanf_s(fp, " %d %d ", &p1->x, &p1->y);
			p1->next = p2;
			p2->previous = p1;
			p1 = p2;
			
		}
		p2->previous->next = NULL;
		snake_tail = p2->previous;
		free(p2);
		fclose(fp);
		return i;
	}
	else return -1;
}

//游戏结果统计
void end_game() {

}
