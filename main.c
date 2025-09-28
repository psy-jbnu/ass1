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
void print_sensors(struct sensor *sensors);
int save_sensors(char *path, struct sensor *sensors);

int main(int argc, char *argv[]) {
	int result = 0;
	struct sensor sensors[PCS];
	load_sensors_from_txt("/home/ubuntu/ass1/data.txt", sensors);
	print_sensors(sensors);
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

void print_sensors(struct sensor *sensors) {
	for(int i = 0; i < PCS; i++) {
		printf("%04d, %-10s, %s\n", sensors[i].id, sensors[i].name, sensors[i].status);
	}
}
		
