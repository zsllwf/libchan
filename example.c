#include "channels.h"
#include <stdio.h>
#include <unistd.h>

void test(channel c) {
    int b = *(int*)chan_read(c);
    printf("read value: %d\n", b);
    int v = 1;
    chan_write(c, &v); // done
} 

int main(int argc, char** argv) {
    channel c = mkchan(sizeof(int), CHF_DEFAULT);
    if (c == NULL) {
        fprintf(stderr, "Could not create a channel!");
        return 1;
    }

    printf("pushing value: 20\n");
    int v = 20;
    chan_write(c, &v);
    
    pid_t pid = fork();
    if (pid == 0) {
        printf("FORKED");
        test(c);
    } else {
        int b;

        do {
            b = *(int*)chan_read(c);
        } while (b != 1);
        chan_destroy(c);
    }
}