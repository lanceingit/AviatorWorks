#pragma once

typedef struct {
    uint8_t* buf;
    uint16_t size;    //Must be an integral power of two
    uint16_t write;
    uint16_t read;
} CircularBuf;

void circularbuf_init(CircularBuf* self, uint8_t* buf, uint16_t size);

int8_t circularbuf_write(CircularBuf* self, uint8_t c);
void circularbuf_write_force(CircularBuf* self, uint8_t c);
int8_t circularbuf_read(CircularBuf* self, uint8_t* c);

uint16_t circularbuf_get_count(CircularBuf* self);
bool circularbuf_is_empty(CircularBuf* self);

void circularbuf_print(CircularBuf* self);

