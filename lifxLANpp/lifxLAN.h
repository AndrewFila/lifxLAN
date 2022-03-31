#include <cstdint>

#ifndef LIFXLAN_H
#define LIFXLAN_H

////header struct
struct header_t {
    //frame header
    uint16_t size;
    uint16_t protocol:12;
    uint8_t  addressable:1;
    uint8_t  tagged:1;
    uint8_t  origin:2;
    uint32_t source;

    //frame address
    uint8_t target[8];
    uint8_t reserved1[6];
    uint8_t res_required:1;
    uint8_t ack_required:1;
    uint8_t reserved2:6;
    uint8_t sequence;

    //protocol header
    uint64_t reserved3:64;
    uint16_t type;
    uint16_t reserved4:16;

} __attribute__((packed));




////payload structs
struct pwrpl_t {
    uint16_t    power;
    uint32_t    duration;
} __attribute__((packed));

struct colpl_t {
    uint8_t     reserved;
    uint16_t    hue;
    uint16_t    saturation;
    uint16_t    brightness;
    uint16_t    kelvin;
    uint32_t    duration;
} __attribute__((packed));

struct wfpl_t {
    uint8_t     reserved;
    uint8_t     transient;
    uint16_t    hue;
    uint16_t    saturation;
    uint16_t    brightness;
    uint16_t    kelvin;
    uint32_t    period;
    float       cycles;
    int16_t     skew_ratio;
    uint8_t     waveform;
} __attribute__((packed));

struct wfopl_t {
    uint8_t     reserved;
    uint8_t     transient;
    uint16_t    hue;
    uint16_t    saturation;
    uint16_t    brightness;
    uint16_t    kelvin;
    uint32_t    period;
    float       cycles;
    int16_t     skew_ratio;
    uint8_t     waveform;
    uint8_t     set_hue;
    uint8_t     set_saturation;
    uint8_t     set_brightness;
    uint8_t     set_kelvin;
} __attribute__((packed));

////message structs

/* no payload message */


struct stdmsg_t {
    struct header_t header;
} __attribute__((packed));

/* set color payload message*/
struct colmsg_t {
    struct header_t header;
    struct colpl_t payload;
} __attribute__((packed));

/* set power payload message*/
struct pwrmsg_t {
    struct header_t header;
    struct pwrpl_t payload;
} __attribute__((packed));

/*set waveform payload message*/
struct wfmsg_t {
    struct header_t header;
    struct wfpl_t payload;
} __attribute__((packed));

/* set waveform optional message*/
struct wfomsg_t {
    struct header_t header;
    struct wfopl_t payload;
} __attribute__((packed));



class lifxLight
{
public:
    void setPower(struct pwrpl_t *, bool, uint32_t);
    void setColor(struct colpl_t *, uint16_t, float, float, uint16_t, uint32_t);
    void setWaveform(struct wfpl_t *);
    void setWaveformOptional(struct wfomsg_t *);
    void sendMsg();
    void encodeHeader(struct header_t *, uint16_t, bool, bool, uint32_t, uint8_t[8], bool, bool, uint8_t, uint16_t);

private:



};

#endif /*LIFXLAN_H*/
