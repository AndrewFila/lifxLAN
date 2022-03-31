#include <stdint.h>


#ifndef SETTERS_H
#define SETTERS_H

//header structure
struct header_t {
    // frame header
    uint16_t size;
    uint16_t protocol:12;
    uint8_t  addressable:1;
    uint8_t  tagged:1;
    uint8_t  origin:2;
    uint32_t source;
    // frame address
    uint8_t  target[8];
    uint8_t  reserved[6];
    uint8_t  res_required:1;
    uint8_t  ack_required:1;
    uint8_t  :6;
    uint8_t  sequence;
    // protocol header
    uint64_t reserved2;
    uint16_t type;
    uint16_t reserved3;
} __attribute__((packed));

//payload structures
struct set_col_p_t {
    uint8_t  reserved;
    uint16_t hue;
    uint16_t saturation;
    uint16_t brightness;
    uint16_t kelvin;
    uint32_t duration;
} __attribute__((packed));


struct set_pwr_p_t {
    uint16_t power;
} __attribute__((packed));

struct set_wf_p_t {
    uint8_t  reserved;
    uint8_t  transient;
    uint16_t hue;
    uint16_t saturation;
    uint16_t brightness;
    uint16_t kelvin;
    uint32_t period;
    float    cycles;
    int16_t  skew_ratio;
    uint8_t  waveform;
} __attribute__((packed));

struct set_wfo_p_t {
    uint8_t  reserved;
    uint8_t  transient;
    uint16_t hue;
    uint16_t saturation;
    uint16_t brightness;
    uint16_t kelvin;
    uint32_t period;
    float    cycles;
    int16_t  skew_ratio;
    uint8_t  waveform;
} __attribute__((packed));

//message structures
typedef struct msg_nopl_t{
    struct header_t header;
} __attribute__((packed));
typedef struct msg_setcol_t {
    struct header_t header;
    struct set_col_p_t payload;
} __attribute__((packed));

typedef struct msg_setpwr_t {
    struct header_t header;
    struct set_pwr_p_t payload;
} __attribute__((packed));

typedef struct msg_setwf_t {
    struct header_t header;
    struct set_wf_p_t payload;
} __attribute__((packed));

typedef struct msg_setwfo_t {
    struct header_t header;
    struct set_wfo_p_t;
} __attribute__((packed));






// header
void encodeHeader(struct header_t * head, uint16_t size, bool tagged, bool addressable, uint32_t source, uint8_t target[8], bool res, bool ack, uint8_t sequence, uint16_t type);

//device
void setPower(msg_setpwr_t * message, bool onOff);
void setLabel();
void setReboot();
void setLocation();
void setGroup();

//light
void setColor(msg_setcol_t * message, uint16_t hue, float saturation, float brightness, uint16_t kelvin, uint32_t duration);
void setWaveform();
void setLightPower();
void setWaveformOptional();

//decoder
void decode();

#endif
