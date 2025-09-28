#include "print.h"

void print_all(struct device *devices) {
        for(int i = 0; i < PCS; i++) {
                printf("%04d, %-10s, %s\n", devices[i].id, devices[i].name, devices[i].status);
        }
}

