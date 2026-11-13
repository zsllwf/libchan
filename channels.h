#include <stddef.h>
#include <stdint.h>

typedef enum {
    CHF_BLOCKING    = 1 << 0, // default
    CHF_NONBLOCKING = 1 << 1, // supported
    CHF_FIXED       = 1 << 2,
    CHF_GROWABLE    = 1 << 3,
    CHF_THREADSAFE  = 1 << 4,
    CHF_OVERWRITE   = 1 << 5
} CHFLAGS;

typedef struct {
    size_t count;
    size_t head;
    size_t tail;
    void* ptrs[256];
    size_t elementsize;
    int blocked;
    CHFLAGS flags;
} _channel;

typedef _channel* channel;

#define CHF_DEFAULT CHF_BLOCKING | CHF_FIXED | CHF_THREADSAFE

channel mkchan(size_t elementsize, CHFLAGS flags);

void chan_write(channel ch, void* ptr);

int chan_isempty(channel ch);

void* chan_read(channel ch);

int chan_isfull(channel ch);

void chan_destroy(channel ch);