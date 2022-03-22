#include "util.h"
#include "message.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define PROTOCOL 1024


void encodeHeader(struct header_t * head, uint16_t sz, bool tgd, bool addr, uint32_t src, uint8_t tgt[8], bool res, bool ack, uint8_t seq, uint16_t type){
    //frame header
    head->size = toLittleEndian16(sz);
    head->protocol = 1024;
    head->tagged = tgd;
    head->addressable = addr;
    head->origin = 0b00;
    head->source = src;
    //head->target[0] = 0xD0;
    //head->target[1] = 0x73;
    //head->target[2] = 0xD5;
    //head->target[3] = 0x3E;
    //head->target[4] = 0x4D;
    //head->target[5] = 0x47;
    //head->target[6] = 0x00;
    //head->target[7] = 0x00;
    for (int i = 0; i < 8; i++){
        head->target[i] = tgt[i];
    }
    for (int i = 0; i < 6; i++){
        head->reserved[i] = 0x00;
    }
    head->res_required = res;
    head->ack_required = ack;
    head->sequence = seq;
    head->reserved2 = 0;
    head->type = type;
    head->reserved3 = 0;
}
void decode(){}
