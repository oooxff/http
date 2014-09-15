#ifndef _MEDIA_CACHE_LIST_H_
#define _MEDIA_CACHE_LIST_H_

#include <stdint.h>
#include <stdlib.h>

class media_cache_list {
    public:
        media_cache_list();
        ~media_cache_list();

        void    enqueue(uint8_t *data, int size);
        uint8_t *dequeue(uint8_t **data, int *size);
    private:
        bool is_empty(void) { return mHead == NULL; };
        bool is_full(void) { return false; };
        struct node *make_node(uint8_t *data, int size);
    private:
        struct node {
            int size;
            uint8_t *data;
            struct node *next;
        };

        struct node *mHead;
        struct node *mTail;
};

#endif //_MEDIA_CACHE_LIST_H_
