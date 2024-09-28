#include "usb_midi.h"

void usbMidi_sendNoteOn(unsigned char note, unsigned char velocity, unsigned char channel)
{
	if (!usbMidi_connected())
		return;
	unsigned char data[4] = {0x09, (channel & 0x0f) | 0x90, note & 0x7f, velocity & 0x7f};
	usbMidi_writeP(data, 4);
}
void usbMidi_sendNoteOff(unsigned char note, unsigned char velocity, unsigned char channel)
{
	if (!usbMidi_connected())
		return;
	unsigned char data[4] = {0x08, (channel & 0x0f) | 0x80, note & 0x7f, velocity & 0x7f};
	usbMidi_writeP(data, 4);
}

void usbMidi_sendPoly(unsigned char note, unsigned char velocity, unsigned char channel)
{
	if (!usbMidi_connected())
		return;
	unsigned char data[4] = {0x0a, (channel & 0x0f) | 0xa0, note & 0x7f, velocity & 0x7f};
	usbMidi_writeP(data, 4);
		
}

void usbMidi_sendCC(unsigned char control, unsigned char value, unsigned char channel)
{
	if (!usbMidi_connected())
		return;
	unsigned char data[4] = {0x0b, (channel & 0x0f) | 0xb0, control & 0x7f, value & 0x7f};
	usbMidi_writeP(data, 4);
}

void usbMidi_sendPC(unsigned char prog, unsigned char channel)
{
	if (!usbMidi_connected())
		return;
	unsigned char data[3] = {0x0c, (channel & 0x0f) | 0xc0, prog & 0x7f};
	usbMidi_writeP(data, 3);
}