/**                                               _____           ,-.
 * _______       _____       _____                ___   _,.      /  /
 * ___    |__   ____(_)_____ __  /______________  __   ; \____,-==-._  )
 * __  /| |_ | / /_  /_  __ `/  __/  __ \_  ___/  _    //_    `----' {+>
 * _  ___ |_ |/ /_  / / /_/ // /_ / /_/ /  /      _    `  `'--/  /-'`(
 * /_/  |_|____/ /_/  \__,_/ \__/ \____//_/       _          /  /
 *                                                           `='
 *
 * circularbuf.c
 *
 * v1.0
 *
 * circular buffer funtion
 */
#include "board.h"

#include "circularbuf.h"
#include "debug.h"

uint16_t circularbuf_get_count(CircularBuf* self)
{
    return ((self->write-self->read)&(self->size-1));    
}

bool circularbuf_is_empty(CircularBuf* self)
{
    return (circularbuf_get_count(self) == 0);
}

int8_t circularbuf_write(CircularBuf* self, uint8_t c)
{
    if(circularbuf_get_count(self) == (self->size-1)) {
        return -1;
    }

    self->buf[self->write] = c;
    self->write = (self->write+1) & (self->size-1);

    return 0;
}

void circularbuf_write_force(CircularBuf* self, uint8_t c)
{
    self->buf[self->write] = c;
    self->write = (self->write+1) & (self->size-1);
}

int8_t circularbuf_read(CircularBuf* self, uint8_t* c)
{
    if(circularbuf_get_count(self) == 0) {
        return -1;
    }

    *c = self->buf[self->read];
    self->read = (self->read+1) & (self->size-1);

    return 0;
}

void circularbuf_init(CircularBuf* self, uint8_t* buf, uint16_t size)
{
    self->write = 0;
    self->read = 0;
    self->buf = buf;
    self->size = size;
}

void circularbuf_print(CircularBuf* self)
{
    PRINT("-------CircularBuf--------\n");
    PRINT("addr:%p\n", self);
    PRINT("write:%u\n", self->write);
    PRINT(" read:%u\n", self->read);
    PRINT("data:");
    for(uint8_t i=0; i<10; i++) {
        PRINT("%x ", self->buf[i]);
    }
    PRINT("\n");
    PRINT("size:%u\n", self->size);
    PRINT("cnt:%u\n", circularbuf_get_count(self));
    PRINT("-------------------\n");
}