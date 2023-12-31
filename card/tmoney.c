#include "tmoney.h"
#include "utils/read_utils.h"
#include <lib/nfc/helpers/iso14443_crc.h>

int32_t tmoney(App* app) {
    int32_t balanceRet;

    uint16_t sw;

    static uint8_t select_apdu[] = {
        0x00, 0xa4, 0x04, 0x00, 0x07, 0xd4, 0x10, 0x00, 0x00, 0x03, 0x00, 0x01};
    static uint8_t balance_apdu[] = {0x90, 0x4C, 0x00, 0x00, 0x04};

    bit_buffer_reset(app->tx);
    bit_buffer_reset(app->rx);

    bit_buffer_append_byte(app->tx, 0x2);
    bit_buffer_append_bytes(app->tx, select_apdu, sizeof(select_apdu));
    iso14443_crc_append(Iso14443CrcTypeA, app->tx);

    NfcError err = nfc_poller_trx(app->nfc, app->tx, app->rx, 600000);
    bool valid = iso14443_crc_check(Iso14443CrcTypeA, app->rx);

    if(err != NfcErrorNone) {
        FURI_LOG_E("TC", "select trx error %d", err);
        return -1;
    }
    if(!valid) {
        FURI_LOG_E("TC", "select valid error");
        return -1;
    }

    getSW(app->rx, &sw);
    if(sw != 0x9000) {
        FURI_LOG_E("TC", "select sw error sw=%04X", sw);
        return -1;
    }

    bit_buffer_reset(app->tx);
    bit_buffer_reset(app->rx);

    bit_buffer_append_byte(app->tx, 0x3);
    bit_buffer_append_bytes(app->tx, balance_apdu, sizeof(balance_apdu));
    iso14443_crc_append(Iso14443CrcTypeA, app->tx);

    err = nfc_poller_trx(app->nfc, app->tx, app->rx, 600000);
    valid = iso14443_crc_check(Iso14443CrcTypeA, app->rx);

    if(err != NfcErrorNone) {
        FURI_LOG_E("TC", "balance trx error %d", err);
        return -1;
    }
    if(!valid) {
        return -1;
    }

    getSW(app->rx, &sw);
    if(sw != 0x9000) {
        FURI_LOG_E("TC", "balance sw error sw=%04X", sw);
        return -1;
    }

    readI32(app->rx, 1, &balanceRet);

    return balanceRet;
}
