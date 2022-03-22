#include "message.h"
#include "util.h"
#include <stdint.h>

//device
void setPower(bool onOff){
    if (onOff){

    } else {

    }
}
void setLabel(char label[32]){}
void setReboot(){}
void setLocation(char location[16], char label[32], uint64_t updated_at){}
void setGroup(char group[16], char label[32], uint64_t updated_at){}

//light
void setColor(struct message_setcolor_t * message, uint16_t hue, uint16_t saturation, uint16_t brightness, uint16_t kelvin, uint32_t duration){
    message->payload.reserved    = 0;
    message->payload.hue         = (int)((0x10000 * hue) /360) % 0x10000;
    message->payload.saturation  = (0xFFFF * saturation);
    message->payload.brightness  = brightness;
    message->payload.kelvin      = kelvin;
    message->payload.duration    = duration;
}
void setWaveform(){}
void setLightPower(){}
void setWaveformOptional(){}
