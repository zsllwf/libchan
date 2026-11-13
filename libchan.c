// Copyright (C) Ilkan Altikulac 2026 | Licensed under MIT
#include "channels.h"
#include <memory.h>
#include <stdint.h>
#include <sys/mman.h>

channel mkchan(size_t elementsize, CHFLAGS flags) {
    _channel ch = {0};

    ch.elementsize = elementsize;
    ch.flags = flags;

    channel chan = mmap(
        NULL,
        sizeof(_channel),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    if (chan == MAP_FAILED)
        return NULL;

    *chan = ch;
    return chan;
}

void chan_write(channel ch, void* ptr) {
    while (ch->flags & CHF_BLOCKING && ch->blocked); // wait
    if (ch->count < 256) {
        ch->blocked = 1;
        ch->ptrs[ch->head++] = ptr;
        ch->head %= 256;
        ch->count++;
        ch->blocked = 0;
    }
}

void* chan_read(channel ch) {
    void* ptr;
    while (ch->flags & CHF_BLOCKING && ch->blocked); // wait
    if (ch->count > 0) {
        ch->blocked = 1;
        ptr = ch->ptrs[ch->tail++];
        ch->tail %= 256;
        ch->count--;
        ch->blocked = 0;
        return ptr;
    }
}

int chan_isempty(channel ch) {
    return ch->count == 0;
}

int chan_isfull(channel ch) {
    return ch->count == 256;
}

void chan_destroy(channel ch) {
    munmap(ch, sizeof(_channel));
}
