/*
2024 guus
modification of the WCH usb-cdc example found here: https://github.com/openwch/ch32v20x/tree/main/EVT/EXAM/USB/USBD/SimulateCDC
for use with platformIO platform: platform = https://github.com/Community-PIO-CH32V/platform-ch32v.git
removed alle the forwarding stuff to uart port, making the incomming data avail in a 256b buffer, outgoing in a 64 byte buffer.
tested with board: board = genericCH32V203K8T6
read and write functions: usb_endp.c
print functions: usb_serial.c
sort of arduino-like interface
*/

#ifndef usb_midi_h
#define usb_midi_h
#include "usb_lib.h"

void usbMidi_begin(); // inits pins and itc

unsigned char usbSerial_available(); // returen bytes in buffer
unsigned char usbSerial_read();      // returns first unread byte from buffer

unsigned char usbMidi_connected(); // check ep0, 1 connected
signed char usbMidi_writeReady();  // -1 not connected, 0 connected but not write ready, 1 connected and writeready

// writes multiple bytes
void usbMidi_writeP(unsigned char *P, unsigned short len);
// write out the tx buffer, called if txbuffer is at 64 bytes
// print stuff

void usbMidi_sendNoteOn(unsigned char note, unsigned char velocity, unsigned char channel);
void usbMidi_sendNoteOff(unsigned char note, unsigned char velocity, unsigned char channel);
void usbMidi_sendPoly(unsigned char note, unsigned char velocity, unsigned char channel);
void usbMidi_sendCC(unsigned char control, unsigned char value, unsigned char channel);
void usbMidi_sendPC(unsigned char prog, unsigned char channel);
void usbMidi_sendSE(unsigned char *buff, unsigned char len);


#endif