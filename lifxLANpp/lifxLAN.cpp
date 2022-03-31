#include "lifxLAN.h"
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <unistd.h>


void lifxLight::setPower(struct pwrpl_t * payload, bool onOff, uint32_t dur){
    if (onOff){
        payload->power      = 0xFF;
        payload->duration   = dur;
    } else {
        payload->power      = 0x00;
        payload->duration   = dur;
    }
}
void lifxLight::setColor(struct colpl_t * payload, uint16_t hue, float sat, float bri, uint16_t kel, uint32_t dur){
    payload->reserved   = 0;
    payload->hue        = ((0x10000 * hue) / 360) % 0x10000;
    payload->saturation = (sat * 0xFFFF);
    payload->brightness = (bri * 0xFFFF);
    payload->kelvin     = kel;
    payload->duration   = dur;
}
void lifxLight::setWaveform(struct wfpl_t * payload){
    payload->reserved   = 0;
   // payload->transient  = tran;
   // payload->hue        = (int) ((0x10000 * hue) / 360) % 0x10000;
   // payload->saturation = (int) (sat * 0xFFFF);
   // payload->brightness = (int) (bri * 0xFFFF);
   // payload->kelvin     = kel;
   // payload->period     = per;
   // payload->

}
void lifxLight::setWaveformOptional(struct wfomsg_t * msg){
    msg->payload.reserved   = 0;
//    msg->payload.transient  = tran;
//    msg->payload.hue        = (int) ((0x10000 * hue) / 360) % 0x10000;
//    msg->payload.saturation = (int) (sat * 0xFFFF);
//    msg->payload.brightness = (int) (bri * 0xFFFF);
//    msg->payload.kelvin     = kel;
//    msg->payload.period     = per;
//    msg->payload.

}
void lifxLight::encodeHeader(struct header_t * head, uint16_t sz, bool tgd, bool addr, uint32_t src, uint8_t tgt[8], bool res, bool ack, uint8_t seq, uint16_t type){
    //frame header
    head->size = (sz >> 8) | (sz << 8);
    head->protocol = 1024;
    head->tagged = tgd;
    head->addressable = addr;
    head->origin = 0b00;
    head->source = src;
    for (int i = 0; i < 8; i++){
        head->target[i] = tgt[i];
    }
    for (int i = 0; i < 6; i++){
        head->reserved1[i] = 0x00;
    }
    head->res_required = res;
    head->ack_required = ack;
    head->sequence = seq;
    head->reserved2 = 0;
    head->type = type;
    head->reserved3 = 0;
}

