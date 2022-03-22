#ifndef SETTERS_H
#define SETTERS_H


//device
void setPower();
void setLabel();
void setReboot();
void setLocation();
void setGroup();

//light
void setColor(struct message_setcolor_t * message, uint16_t hue, uint16_t saturation, uint16_t brightness, uint16_t kelvin, uint32_t duration);
void setWaveform();
void setLightPower();
void setWaveformOptional();


#endif
