#include "message.h"
#include "util.h"
#include <stdint.h>

void encodeHeader(struct header_t * head, uint16_t sz, bool tgd, bool addr, uint32_t src, uint8_t tgt[8], bool res, bool ack, uint8_t seq, uint16_t type){
    //frame header
    head->size = (sz << 8) | (sz >> 8);
    head->protocol = 1024;
    head->tagged = tgd;
    head->addressable = addr;
    head->origin = 0b00;
    head->source = src;
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

//device
void setPower(struct message_setPow_t * message, bool onOff){
    if (onOff){
        message->payload.power = 0xFFFF;
    } else {
        message->payload.power = 0x0000;
    }
}
void setLabel(char label[32]){}
void setReboot(){}
void setLocation(char location[16], char label[32], uint64_t updated_at){}
void setGroup(char group[16], char label[32], uint64_t updated_at){}

//light
void setColor(struct message_setcolor_t * message, uint16_t hue, float saturation, float brightness, uint16_t kelvin, uint32_t duration){
    message->payload.reserved    = 0;
    message->payload.hue         = (int)((0x10000 * hue) /360) % 0x10000;
    message->payload.saturation  = (int)(saturation * 0xFFFF);
    message->payload.brightness  = (int)(brightness * 0xFFFF);
    message->payload.kelvin      = kelvin;
    message->payload.duration    = duration;
}
void setWaveform(){}
void setLightPower(){}
void setWaveformOptional(){}




void decode(){}
