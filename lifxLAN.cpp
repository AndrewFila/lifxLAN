/******************************************************************************
 *  Author - Andrew Fila                                                      *
 *  Last Updated - 4-3-22                                                     *
 *  Description - lifxLan is a library of functions that enable setting and   *
 *  reciving information from lifx lights.                                    *
 *****************************************************************************/


#include "lifxLAN.h"
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <unistd.h>


//=========================//
// Setters                 //
//=========================//
/**** Possible future updates
 *  -- DEVICE
 *  setPower                    - Packet 21  //TODO
 *  setLabel                    - Packet 24  //TODO
 *  setReboot                   - Packet 38  //TODO
 *  setLocation                 - Packet 40  //TODO
 *  setGroup                    - Packet 52  //TODO
 *  -- LIGHT
 *  setInfared                  - Packet 122 //TODO
 *  setHevCycle                 - Packet 143 //TODO
 *  setHevCycleConfiguration    - Packet 146 //TODO
 *  -- MUTIZONE
 *  setColorZones               - Packet 501 //TODO
 *  setMultiZoneEffect          - Packet 508 //TODO
 *  setExtendedColorZones       - packet 510 //TODO
 *  -- RELAY
 *  setRPower                   - Packet 817 //TODO
 *  -- TILE
 *  setUserPosition             - Packet 703 //TODO
 *  set64                       - Packet 715 //TODO
 *  setTileEffect               - Packet 719 //TODO
 */
///////////////////////////
//   DEVICE              //
///////////////////////////


///////////////////////////
//   LIGHT               //
///////////////////////////

//setLightPower - packet 117
void lifxLight::setPower(struct pwrpl_t * payload, bool onOff, uint32_t dur){
    if (onOff){
        payload->power      = 0xFF;
        payload->duration   = dur;
    } else {
        payload->power      = 0x00;
        payload->duration   = dur;
    }
}

//setColor - packet 102
void lifxLight::setColor(struct colpl_t * payload, uint16_t hue, float sat, float bri, uint16_t kel, uint32_t dur){
    payload->reserved   = 0;
    payload->hue        = ((0x10000 * hue) / 360) % 0x10000;
    payload->saturation = (sat * 0xFFFF);
    payload->brightness = (bri * 0xFFFF);
    payload->kelvin     = kel;
    payload->duration   = dur;
}

//setWaveform - packet 103
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

//setWaveformOptional - packet 119
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


//=========================//
// Getters                 //
//=========================//
/** NEED TO IMPLEMENT
 * -- DISCOVERY
 * GetService               - Packet 2    //TODO
 * -- DEVICE
 * GetHostFirmware          - Packet 14   //TODO
 * GetWifiInfo              - Packet 16   //TODO
 * GetWifiFirmware          - Packet 18   //TODO
 * GetPower                 - Packet 20   //TODO
 * GetLabel                 - Packet 23   //TODO
 * GetVersion               - Packet 32   //TODO
 * GetInfo                  - Packet 34   //TODO
 * GetLocation              - Packet 48   //TODO
 * GetGroup                 - Packet 51   //TODO
 * EchoRequest              - Packet 58   //TODO
 * -- LIGHT
 * GetColor                 - Packet 101  //TODO
 * GetLightPower            - Packet 116  //TODO
 ** POSSIBLE FUTURE IMPLEMENTATION
 * GetInfrared              - Packet 120  //TODO
 * GetHevCycle              - Packet 142  //TODO
 * GetHevCycleConfiguration - Packet 145  //TODO
 * GetLastHevCycleResult    - Packet 148  //TODO
 * GetColorZones            - Packet 502  //TODO
 * GetMultiZoneEffect       - Packet 507  //TODO
 * GetExtendedColorZones    - Packet 511  //TODO
 * GetRPower                - Packet 816  //TODO
 * GetDeviceChain           - Packet 701  //TODO
 * Get64                    - Packet 707  //TODO
 * GetTileEffect            - Packet 718  //TODO
 */
///////////////////////////
//   DISCOVERY           //
///////////////////////////
void getService(){

}

///////////////////////////
//   DEVICE              //
///////////////////////////




//=========================//
// Extra Utils             //
//=========================//

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


void lifxLight::decodeMessage(){

}

