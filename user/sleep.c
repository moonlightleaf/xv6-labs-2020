#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(2, "Please input argument after \"sleep\"\n");
        exit(1);
    }
    uint ticks = atoi(argv[1]);
    sleep(ticks);
    exit(0);
}