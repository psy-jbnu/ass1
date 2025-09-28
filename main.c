#include <stdio.h>
#include <string.h>
#define PCS 20

struct sensor {
	int id;
	char name[10];
	char status[8];
}

sensor **read_txt(char *path);
int save_dat(char *path, struct sensor **sensors_ptr);
int main(int argc, char *argv[]) {
	struct sensor *sensors_ptr;
	int result = 0;
	switch (&argv[1]) {
		case "init":
			if(argc != 4) {
				printf("잘못된 사용");
				result = -1;
				break;
			}
			sensors_ptr = read_txt(strcat(argv[0], argv[2]));
			if(sensors_ptr == NULL) {
				printf("로딩이 제대로 안되었습니다.");
				result = -2;
				break;
			}
			if(save_dat(strcat(argv[0], argv[3]))==PCS) {
				printf("저장이 제대로 안되었습니다.");
				result = -2;
			}
			break;

	}
	free(sensors_ptr);
	return result;
}

sensor **read_txt(char *path){
	File *file_ptr;
	struct sensor temp = NULL;
	struct sensor *sensors_ptr[PCS] =(sensor **)malloc(sizeof(sensor)*PCS);
	int i = 0;
	file_ptr = fopen(path,"r");
	
	if(file_ptr == NULL) {
		printf("파일이 없음.");
		free(sensors_ptr);
		sensors_ptr = NULL;
		return sensors_ptr;
	}
	
	
	while(fscanf(file_ptr, “%d, %s, %s”, &temp.id, &temp.name, &temp.status)) {
		*sensors_ptr[i++] = temp;	
	}

	fclose(file_pointer);
	return sensors_ptr;
}

int save_dat(char *path, struct sensor **sensors_ptr) {
	File *file_ptr;
	int result = 0;
	file_ptr = fopen(path, "wb");

	result = fwrite(*sensors_ptr, sizeof(sensor), PCS, file_ptr);
	
	fclose(file_ptr);
	return result;
}
