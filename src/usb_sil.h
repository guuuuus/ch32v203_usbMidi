/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_sil.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : This file contains all the functions prototypes for the  
 *                      USB Simplified Interface Layer firmware library.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/ 
#ifndef __USB_SIL_H
#define __USB_SIL_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(CH32V203)
#include "ch32v20x.h"
#elif defined(CH32X035)
#include "ch32x035.h"
#endif

uint32_t USB_SIL_Init(void);
uint32_t USB_SIL_Write(uint8_t bEpAddr, uint8_t* pBufferPointer, uint32_t wBufferSize);
uint32_t USB_SIL_Read(uint8_t bEpAddr, uint8_t* pBufferPointer);
	 
#ifdef __cplusplus
}

#endif

#endif /* __USB_SIL_H */





