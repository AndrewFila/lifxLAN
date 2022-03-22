#ifndef MESSAGEMAKER_H
#define MESSAGEMAKER_H
#include "util.h"
#include <stdbool.h>
#include <stdint.h>
struct message_setcolor_t {
    struct header_t header;
    struct set_color_p_t payload;
} __attribute__((packed));

struct message_setPow_t {
    struct header_t header;
    struct set_power_p_t payload;
} __attribute__((packed));

struct message_setwf_t {
    struct header_t header;
    struct set_waveform_p_t payload;
} __attribute__((packed));









void encodeHeader(struct header_t * head, uint16_t size, bool tagged, bool addressable, uint32_t source, uint8_t target[8], bool res, bool ack, uint8_t sequence, uint16_t type);

void decode();



#endif
