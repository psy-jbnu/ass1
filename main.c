#include "print.h"
//txt파일에서 data를 loading하는 함수. device 몇개를 가져왔는지 반환하고 못읽으면 -1 반환
int load_devices_from_txt(char *path, struct device *devices);
int load_devices_from_bin(char *path, struct device *devices);
int save_devices(char *path, struct device *devices);
int find_device(int id, struct device *devices);
int edit_device(int idx, struct device *devices, int id, char * name, char *status);
int main(int argc, char *argv[]) {
	int result = 0;
	struct device devices[PCS];
	if (strcmp(argv[1], "init") == 0){

        	if(argc != 4) {
            		printf("잘못된 사용");
            		result = -1;
            		return result;
		}
	
		if(load_devices_from_txt(argv[2], devices) == -1) {
			printf("파일 입력 에러");
			result = -1;
			return result;
		}


		if(save_devices(argv[3], devices) < PCS) {	
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
		if(load_devices_from_bin(argv[2], devices) < PCS) {
                        printf("파일 입력 에러");
                        result = -1;
                        return result;
                }
		print_all(devices);

	}
	else if (strcmp(argv[1], "update") == 0){
                if(argc != 6) {
                        printf("잘못된 사용");
                        result = -1;
                        return result;
                }
		int idx = 0;
		if(load_devices_from_bin(argv[2], devices) < PCS) {
                        printf("파일 입력 에러");
                        result = -1;
                        return result;
                }
		idx = find_device(atoi(argv[3]), devices);
		if(idx < 0) {
			printf("센서 없음.");
			result = -1;
			return result;
		}
		print_all(devices);
		edit_device(idx, devices, atoi(argv[3]), argv[4], argv[5]);
		print_all(devices);
		if(save_devices(argv[2], devices) < PCS) {
                        printf("파일 출력 에러");
                        result = -1;
                        return result;
                }
	}
	return result;
	
}

int load_devices_from_txt(char path[], struct device devices[]) {
	FILE *fptr;
	int result = 0;
	fptr = fopen(path,"r");
	if(fptr == NULL) { 
		result = -1;
		printf("%s \n",path);
		return result;
	}
	for(int i = 0; i < PCS; i++) {
		fscanf(fptr, "%d %s %s", &devices[i].id, devices[i].name, devices[i].status);
		result++;
	}
    	fclose(fptr);
	return result;
}
int load_devices_from_bin(char *path, struct device *devices) {
	FILE *fptr;
        int result = 0;
        fptr = fopen(path,"rb");
        if(fptr == NULL) {
                result = -1;
                return result;
        }
        result = fread(devices, sizeof(struct device), PCS, fptr);
        fclose(fptr);
        return result;

}
void print_all(struct device *devices) {
	for(int i = 0; i < PCS; i++) {
		printf("%04d, %-10s, %s\n", devices[i].id, devices[i].name, devices[i].status);
	}
}
		
int save_devices(char *path, struct device *devices) {
	FILE *fptr = fopen(path, "wb");
	int result = 0;
	result = fwrite(devices, sizeof(struct device), PCS, fptr);
	fclose(fptr);
	return result;
}
int find_device(int id, struct device *devices) {
	int idx = -1;
	for(int i = 0; i < PCS; i++) {
                if(devices[i].id == id) idx = i;	
        }
	return idx;
}

int edit_device(int idx, struct device *devices, int id, char * name, char *status) {
	if(devices[idx].id != id) return -1;
	if(strcmp(name, "-") != 0) strcpy(devices[idx].name, name);
	if(strcmp(status, "-") != 0) strcpy(devices[idx].status, status);
	return 0;
}
