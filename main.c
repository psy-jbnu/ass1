#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PCS 20

struct sensor {
    int id;
    char name[10];
    char status[8];
};

struct sensor **read_txt(char *path);
int save_dat(char *path, struct sensor **sensors_ptr);
int main(int argc, char *argv[]) {
    struct sensor **sensors_ptr = NULL;
    int result = 0;
    if (strcmp(argv[1], "init") == 0){

        if(argc != 4) {
            printf("잘못된 사용");
            result = -1;
            free(sensors_ptr);
            return result;
        }
        sensors_ptr = read_txt(strcat(argv[0], argv[2]));
        if(sensors_ptr == NULL) {
            printf("로딩이 제대로 안되었습니다.");
            result = -2;
            free(sensors_ptr);
            return result;
        }
        if(save_dat(strcat(argv[0], argv[3]),sensors_ptr)==PCS) {
            printf("저장이 제대로 안되었습니다.");
            result = -2;
            free(sensors_ptr);
            return result;
        }

    }
    free(sensors_ptr);
    return result;
}

struct sensor **read_txt(char *path){
    FILE *file_ptr = fopen(path,"r");;
    struct sensor temp;
    struct sensor **sensors_ptr =(struct sensor **)malloc(sizeof(struct sensor)*PCS);
    int i = 0;

    if(file_ptr == NULL) {
        printf("파일이 없음.");
        free(sensors_ptr);
        sensors_ptr = NULL;
        return sensors_ptr;
    }


    while(fscanf(file_ptr, "%d %s %s", &temp.id, temp.name, temp.status)) {
        *sensors_ptr[i++] = temp;
    }

    fclose(file_ptr);
    return sensors_ptr;
}

int save_dat(char *path, struct sensor **sensors_ptr) {
    FILE *file_ptr = fopen(path, "wb");;
    int result = 0;

    result = fwrite(*sensors_ptr, sizeof(struct sensor), PCS, file_ptr);

    fclose(file_ptr);
    return result;
}
