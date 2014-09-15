#include "media_cache_list.h"

media_cache_list::media_cache_list()
    : mHead(0),
    mTail(0) {
    }

media_cache_list::~media_cache_list()
{
    while(! is_empty()) {
        free(dequeue());
    }
}

struct node *media_cache_list::make_node(uint8_t *data, int size)
{
    struct node *n;

    n = malloc(sizeof(struct node));
    n->size = size;
    n->data = data;
    n->next = NULL;

    return n;
}

void media_cache_list::enqueue(uint8_t *data, int size)
{
    struct node *n;

    n = make_node(data, size);

    if (! mHead) {
        mHead = n;
        mTail = n;
    } else {
        mTail->next = n;
        mTail = n;
    }
}

uint8_t *media_cache_list::dequeue(uint8_t **data, int *size)
{
}
