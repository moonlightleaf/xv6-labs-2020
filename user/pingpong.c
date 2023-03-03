#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int father2son[2];
    int son2father[2];
    pipe(father2son);
    pipe(son2father);
    if (fork() == 0) {
        close(son2father[0]);
        close(father2son[1]);
        char buff[10];
        read(father2son[0], buff, 1);
        close(father2son[0]);
        printf("%d: received ping\n", getpid());
        write(son2father[1], "1\n", 1);
        close(son2father[1]);
        exit(0);
    }
    else {
        close(father2son[0]);
        close(son2father[1]);
        char buff[10];
        write(father2son[1], "1\n", 1);
        close(father2son[1]);
        read(son2father[0], buff, 1);
        close(son2father[0]);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}