#ifndef BLOCKS_H
#define BLOCKS_H

#define MAX_BLOCKS 1024

typedef void (*block_fn_t)(void);

typedef struct {
    block_fn_t fns[MAX_BLOCKS];
    int count;
} block_list_t;

#endif