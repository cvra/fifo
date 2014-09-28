#include "fifo.h"

void fifo8_init(fifo8_t *f, char *buffer, uint16_t size)
{
    f->buffer = buffer;
    f->size = size;
    f->read = 0;
    f->write = 0;
    f->elem = 0;
}

bool fifo8_put(fifo8_t *f, char c)
{
    return false;
}

bool fifo8_get(fifo8_t *f, char *c)
{
    return false;
}

bool fifo8_isempty(fifo8_t *f)
{
    return f->elem == 0;
}

bool fifo8_isfull(fifo8_t *f)
{
    return f->elem == f->size;
}
