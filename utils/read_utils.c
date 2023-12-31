#include "read_utils.h"
#include <machine/endian.h>

RESULT readU16(const BitBuffer* buf, size_t off, uint16_t* ret) {
    size_t size = bit_buffer_get_size_bytes(buf);
    if(off + 2 > size) return INVALID_SIZE;

    bit_buffer_write_bytes_mid(buf, ret, off, 2);
    *ret = __bswap16(*ret);

    return OK;
}

RESULT readI32(const BitBuffer* buf, size_t off, int32_t* ret) {
    size_t size = bit_buffer_get_size_bytes(buf);
    if(off + 4 > size) return INVALID_SIZE;

    bit_buffer_write_bytes_mid(buf, ret, off, 4);
    *ret = __bswap32(*ret);

    return OK;
}

RESULT getSW(const BitBuffer* buf, uint16_t* sw) {
    size_t size = bit_buffer_get_size_bytes(buf);
    if(size < 4) return INVALID_SIZE;

    return readU16(buf, size - 4, sw);
}
