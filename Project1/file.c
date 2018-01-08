#include "my_h.h"

FILE *fp;

//用户信息保存
/*
mode 添加模式   1  新用户注册  2  用户信息修改，如分数更新等等
choose_id    mode2 时使用，要修改的用户的id
*/
void user_info_save(int mode, int choose_id) {
	user1->state = now_state;
	FILE *fp2;
	int all_users = 1;
	if (fopen_s(&fp, "user_info.xst", "r")) {
		fopen_s(&fp, "user_info.xst", "ab");
		fopen_s(&fp2, "user_info_s.xst", "wb+");
		fprintf(fp2, "%d ", all_users);
	}
	else {
		fclose(fp);
		fopen_s(&fp, "user_info.xst", "ab");
		fopen_s(&fp2, "user_info_s.xst", "rb");
	}
	fscanf_s(fp2, "%d ", &all_users);
	fclose(fp2);
	switch (mode) {
	case 1:    //添加新用户
		user1->id = all_users;
		int temp = fwrite(user1, sizeof(user), 1, fp);
		all_users++;
		fopen_s(&fp2, "user_info_s.xst", "wb");
		fprintf(fp2, "%d ", all_users);
		fclose(fp2);
		break;
	case 2:    //用户信息修改
		fclose(fp);
		fopen_s(&fp, "user_info.xst", "rb+");
		fseek(fp, (choose_id - 1) * sizeof(user), 1);
		fwrite(user1, sizeof(user), 1, fp);
		break;
	}
	fclose(fp);
}

//用户信息读取
user* user_info_read() {
	user *p_temp;
	if (!fopen_s(&fp, "user_info.xst", "rb")) {
		user *p1 = NULL, *p3 = NULL;
		p1 = (user*)malloc(sizeof(user));
		p_temp = p1;
		p1->score = 10000;
		p1->next = NULL;
		while (!feof(fp)) {
			user *p2 = (user*)malloc(sizeof(user));
			fread(p2, sizeof(user), 1, fp);
			while (p2->score <= p_temp->score) {
				if (p_temp->next == NULL) break;
				if(p2->score < p_temp->next->score) p_temp = p_temp->next;
				else break;
			}
			p2->next = p_temp->next;
			p_temp->next = p2;
			p_temp = p1;
		}
		fclose(fp);
		return p_temp->next;
	}
	else return NULL;
}

//地图保存(游戏进度保存)
int map_data_save() {
	fopen_s(&fp, "temp_map_data.xst", "wb");
	int i = fwrite(map_data, sizeof(map_data), 1, fp);
	fprintf(fp, "%d ", now_state);
	fclose(fp);
	fopen_s(&fp, "temp_snake_data.xst", "wb");
	fprintf(fp, "%d ", length_of_snake());
	snake *p1 = snake_head;
	while (p1) {
		fprintf(fp, " %d %d ", p1->x, p1->y);
		p1 = p1->next;
	}
	fclose(fp);
	return i;
}

//地图读取（游戏进度读取）
int map_data_read() {
	if (!fopen_s(&fp, "temp_map_data.xst", "rb")) {
		int i = fread(map_data, sizeof(map_data), 1, fp);
		fscanf_s(fp, "%d ", &now_state);
		fclose(fp);
		fopen_s(&fp, "temp_snake_data.xst", "rb");
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


