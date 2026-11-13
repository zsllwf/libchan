# libchan / channels.h 
### is a very *"small"*, *"implementation agnostic"* concurrent channel system inspired by Go, you could just also call this a **blockable shared circular buffer**, if you so badly want to.
## Differences between Go's chan and this:
Since this is a C library, it doesn't introduce new syntax, instead you use regular library functions to write to the channel
### Go example:
```Go
// NO COPYRIGHT, THIS IS REFERENCE CODE
package main

import "fmt"

func test(a chan int) {
    fmt.println("Value: ", <-a)
}

func main() {
    a := make(chan int)
    a <- 0
    test(a)
}
```
### libchan C example (example.c):
```C
// NO COPYRIGHT, THIS IS REFERENCE CODE
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
```
