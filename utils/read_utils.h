#ifndef READ_UTILS_H
#define READ_UTILS_H

#include <bit_buffer.h>

typedef enum { OK, INVALID_SIZE } RESULT;

RESULT readU16(const BitBuffer* buf, size_t off, uint16_t* ret);
RESULT readI32(const BitBuffer* buf, size_t off, int32_t* ret);
RESULT getSW(const BitBuffer* buf, uint16_t* sw);

#endif