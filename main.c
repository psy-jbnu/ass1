#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PCS 20

struct sensor {
    int id;
    char name[11];
    char status[9];
};
//txt파일에서 data를 loading하는 함수. sensor 몇개를 가져왔는지 반환하고 못읽으면 -1 반환
int load_sensors_from_txt(char *path, struct sensor *sensors);
int load_sensors_from_bin(char *path, struct sensor *sensors);
void print_sensors(struct sensor *sensors);
int save_sensors(char *path, struct sensor *sensors);
int find_sensor(int id, struct sensor *sensors);
int edit_sensor(int idx, struct sensor *sensors, int id, char * name, char *status);
int main(int argc, char *argv[]) {
	int result = 0;
	struct sensor sensors[PCS];
	if (strcmp(argv[1], "init") == 0){

        	if(argc != 4) {
            		printf("잘못된 사용");
            		result = -1;
            		return result;
		}
	
		if(load_sensors_from_txt(argv[2], sensors) == -1) {
			printf("파일 입력 에러");
			result = -1;
			return result;
		}


		if(save_sensors(argv[3], sensors) < PCS) {	
			printf("파일 출력 에러");
			result = -1;
			return result;
		}

        }
	else if (strcmp(argv[1], "print") == 0){
		if(argc != 3) {
                        printf("잘못된 사용");
                        result = -1;
                        return result;
                }
		if(load_sensors_from_bin(argv[2], sensors) < PCS) {
                        printf("파일 입력 에러");
                        result = -1;
                        return result;
                }
		print_sensors(sensors);

	}
	else if (strcmp(argv[1], "update") == 0){
                if(argc != 6) {
                        printf("잘못된 사용");
                        result = -1;
                        return result;
                }
		int idx = 0;
		if(load_sensors_from_bin(argv[2], sensors) < PCS) {
                        printf("파일 입력 에러");
                        result = -1;
                        return result;
                }
		idx = find_sensor(atoi(argv[3]), sensors);
		if(idx < 0) {
			printf("센서 없음.");
			result = -1;
			return result;
		}
		print_sensors(sensors);
		edit_sensor(idx, sensors, atoi(argv[3]), argv[4], argv[5]);
		print_sensors(sensors);
		if(save_sensors(argv[2], sensors) < PCS) {
                        printf("파일 출력 에러");
                        result = -1;
                        return result;
                }
	}
	return result;
	
}

int load_sensors_from_txt(char path[], struct sensor sensors[]) {
	FILE *fptr;
	int result = 0;
	fptr = fopen(path,"r");
	if(fptr == NULL) { 
		result = -1;
		printf("%s \n",path);
		return result;
	}
	for(int i = 0; i < PCS; i++) {
		fscanf(fptr, "%d %s %s", &sensors[i].id, sensors[i].name, sensors[i].status);
		result++;
	}
    	fclose(fptr);
	return result;
}
int load_sensors_from_bin(char *path, struct sensor *sensors) {
	FILE *fptr;
        int result = 0;
        fptr = fopen(path,"rb");
        if(fptr == NULL) {
                result = -1;
                return result;
        }
        result = fread(sensors, sizeof(struct sensor), PCS, fptr);
        fclose(fptr);
        return result;

}
void print_sensors(struct sensor *sensors) {
	for(int i = 0; i < PCS; i++) {
		printf("%04d, %-10s, %s\n", sensors[i].id, sensors[i].name, sensors[i].status);
	}
}
		
int save_sensors(char *path, struct sensor *sensors) {
	FILE *fptr = fopen(path, "wb");
	int result = 0;
	result = fwrite(sensors, sizeof(struct sensor), PCS, fptr);
	fclose(fptr);
	return result;
}
int find_sensor(int id, struct sensor *sensors) {
	int idx = -1;
	for(int i = 0; i < PCS; i++) {
                if(sensors[i].id == id) idx = i;	
        }
	return idx;
}

int edit_sensor(int idx, struct sensor *sensors, int id, char * name, char *status) {
	if(sensors[idx].id != id) return -1;
	if(strcmp(name, "-") != 0) strcpy(sensors[idx].name, name);
	if(strcmp(status, "-") != 0) strcpy(sensors[idx].status, status);
	return 0;
}
