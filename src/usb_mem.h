/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_mem.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : This file contains all the functions prototypes for the  
 *                      USB Initialization firmware library.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/ 
#ifndef __USB_MEM_H
#define __USB_MEM_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(CH32V203)
#include "ch32v20x.h"
#elif defined(CH32X035)
#include "ch32x035.h"
#endif

void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);


#ifdef __cplusplus
}
#endif

#endif  /*__USB_MEM_H*/






