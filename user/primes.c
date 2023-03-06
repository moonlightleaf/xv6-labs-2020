#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NUMBER_SIZE 34

int main(int argc, char* argv[]) {
    int buff[NUMBER_SIZE];
    for (int i = 0; i < NUMBER_SIZE; ++i) buff[i] = i + 2;
    int little_pipe[2];
    pipe(little_pipe);
    int left_number = NUMBER_SIZE;
    int is_first_process = 1;

    while (1) {
        if (is_first_process) is_first_process = 0;
        else read(little_pipe[0], buff, sizeof(int) * left_number);
        
        printf("prime %d\n", buff[0]);
        left_number--;

        //处理余下的数字
        int next_left_number = 0;
        for (int i = 0; i < left_number; ++i) {
            if (buff[1 + i] % buff[0]) {
                write(little_pipe[1], buff + 1 + i, sizeof(int));
                next_left_number++;
            }
        }
        left_number = next_left_number;

        if (left_number == 0) exit(0);
        if (fork() != 0) {
            close(little_pipe[0]);
            close(little_pipe[1]);
            wait(0);
            exit(0);
        }
    }
}