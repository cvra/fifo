#ifndef FIFO8_H
#define FIFO8_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    char *buffer;
    uint16_t size;
    uint16_t elem;
    uint16_t read;
    uint16_t write;
} fifo8_t;

#ifdef __cplusplus
extern "C" {
#endif

void fifo8_init(fifo8_t *f, char *buffer, uint16_t size);
bool fifo8_put(fifo8_t *f, char c);
bool fifo8_get(fifo8_t *f, char *c);
bool fifo8_isempty(fifo8_t *f);
bool fifo8_isfull(fifo8_t *f);

#ifdef __cplusplus
}
#endif

#endif // FIFO8_H
