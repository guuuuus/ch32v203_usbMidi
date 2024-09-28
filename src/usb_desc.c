/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_desc.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : USB Descriptors.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include "usb_lib.h"
#include "usb_desc.h"

/* USB Device Descriptors */
const uint8_t USBD_DeviceDescriptor[] = {
    0x12,               // bLength
    0x01,               // bDescriptorType (Device)
    0x10, 0x01,         // bcdUSB 1.10
    0x00,               // bDeviceClass
    0x00,               // bDeviceSubClass
    0x00,               // bDeviceProtocol
    DEF_USBD_UEP0_SIZE, // bMaxPacketSize0 64
    0x86, 0x1A,         // idVendor
    0x0C, 0xFE,         // idProduct
    0x01, 0x00,         // bcdDevice 0.01
    0x01,               // iManufacturer (String Index)
    0x02,               // iProduct (String Index)
    0x00,               // iSerialNumber (String Index)
    0x01,               // bNumConfigurations 1
};

#define DEF_USBD_ENDP2_SIZE 64
#define DEF_USBD_ENDP1_SIZE 64
/* USB Configration Descriptors */
const uint8_t USBD_ConfigDescriptor[] = {
    // Configure descriptor
    0x09,
    0x02,
    101, 0x00,
    // 83, 0x00,
    0x02,
    0x01,
    0x00,
    0x80,
    0x32,
    ////////////^^^^

    // Interface 0 (AudioClass) descriptor
    0x09,
    0x04,
    0x00,
    0x00,
    0x00,
    0x01,
    0x01,
    0x00,
    0x00,

    // Class-specific AC Interface Descriptor (9)
    0x09,
    0x24,
    0x01,
    0x00,
    0x01,
    0x09,
    0x00,
    0x01,
    0x01,

    // MIDIStreaming Interface Descriptors
    // Standard MS Interface Descriptor (9)
    0x09,
    0x04,
    0x01,
    0x00,
    0x02,
    0x01,
    0x03,
    0x00,
    0x00,

    // Class-specific MS Interface Descriptor (7)
    0x07,
    0x24,
    0x01,
    0x00,
    0x01,
    0x41,
    0x00,
    //////////////////////////////^^^^ or 0x25 ~ 7+9+9+6+6

    // MIDI IN Jack Descriptor Embedded (6)
    0x06,
    0x24,
    0x02,
    0x01,
    0x01,
    0x00,

    // MIDI IN Jack Descriptor (6)
    0x06,
    0x24,
    0x02,
    0x02,
    0x02,
    0x00,

    // MIDI OUT Jack Descriptor Embedded(9)
    0x09,
    0x24,
    0x03,
    0x01,
    0x03,
    0x01,
    0x02,
    0x01,
    0x00,

    // MIDI OUT Jack Descriptor (9)
    0x09,
    0x24,
    0x03,
    0x02,
    0x04,
    0x01,
    0x01,
    0x01,
    0x00,

    // Standard Bulk OUT (9)
    //        0x09, 0x05, 0x01, 0x02, (uint8_t) DEF_USBD_ENDP1_SIZE,
    //        (uint8_t) ( DEF_USBD_ENDP1_SIZE >> 8), 0x00, 0x00, 0x00,

    0x09,
    0x05,
    0x02,
    0x02,
    (uint8_t)DEF_USBD_ENDP2_SIZE,
    (uint8_t)(DEF_USBD_ENDP2_SIZE >> 8),
    0x00,
    0x00,
    0x00,

    // Class MS Bulk OUT (5)
    0x05,
    0x25,
    0x01,
    0x01,
    //     0x01,
    0x03,

    // Standard Bulk IN (9)
    0x09,
    0x05,
    0x83,
    //     0x03,
    0x02,
    //     (uint8_t)DEF_USBD_ENDP3_SIZE,
    //     (uint8_t)(DEF_USBD_ENDP3_SIZE >> 8),
    0x40, 0x00, // wMaxPacketSize 64
    0x0A,
    0x00,
    0x00,

    // Class MS Bulk IN (5)
    0x05,
    0x25,
    0x01,
    0x01,
    0x03
    //     0x01

};

/* USB String Descriptors */
const uint8_t USBD_StringLangID[USBD_SIZE_STRING_LANGID] = {
    USBD_SIZE_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04};

/* USB Device String Vendor */
const uint8_t USBD_StringVendor[USBD_SIZE_STRING_VENDOR] = {
    USBD_SIZE_STRING_VENDOR,
    USB_STRING_DESCRIPTOR_TYPE,
    'G', 0, 'U', 0, 'U', 0, 'U', 0, 'U', 0, 'S', 0};

/* USB Device String Product */
const uint8_t USBD_StringProduct[USBD_SIZE_STRING_PRODUCT] = {
    USBD_SIZE_STRING_PRODUCT,
    USB_STRING_DESCRIPTOR_TYPE,
    'M', 0, 'I', 0, 'D', 0, 'I', 0, '-', 0, 'P', 0, 'A', 0, 'W', 0};

/* USB Device String Serial */
uint8_t USBD_StringSerial[USBD_SIZE_STRING_SERIAL] = {
    USBD_SIZE_STRING_SERIAL,
    USB_STRING_DESCRIPTOR_TYPE,
    '0', 0, '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0, '9', 0};
