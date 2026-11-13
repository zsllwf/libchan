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
#include <channels.h>
#include <stdio.h>

void test(channel a) {
    int b = (int)(chan_read(a));
    
} 

int main(int argc, char** argv) {

}