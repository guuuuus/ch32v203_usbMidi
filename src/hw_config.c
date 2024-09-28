/********************************** (C) COPYRIGHT *******************************
 * File Name          : hw_config.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/08/08
 * Description        : USB configuration file.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_istr.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"

#if defined(CH32V203)
// void USBWakeUp_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USB_LP_CAN1_RX0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#elif defined(CH32X035)
void USBFS_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif

/*******************************************************************************
 * @fn        USBWakeUp_IRQHandler
 *
 * @brief     This function handles USB wake up exception.
 *
 * @return    None
 */
// void USBWakeUp_IRQHandler(void)
// {
// 	EXTI_ClearITPendingBit(EXTI_Line18);
// }

/*******************************************************************************
 * @fn           USB_LP_CAN1_RX0_IRQHandler
 *
 * @brief        This function handles USB exception.
 *
 * @return None
 */
#if defined(CH32V203)

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	USB_Istr();
}
#elif defined(CH32X035)

void USBFS_IRQHandler(void)
{
	USB_Istr();
}
#endif

/*******************************************************************************
 * @fn        Set_USBConfig
 *
 * @brief     Set_USBConfig .
 *
 * @return    None
 */
#if defined(CH32V203)
void Set_USBConfig()
{
	if (SystemCoreClock == 144000000)
	{
		RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div3);
	}
	else if (SystemCoreClock == 96000000)
	{
		RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div2);
	}
	else if (SystemCoreClock == 48000000)
	{
		RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}
#elif defined(CH32X035)
void Set_USBConfig()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBFS, ENABLE);
}
#endif

/*******************************************************************************
 * @fn        Enter_LowPowerMode
 *
 * @brief     Enter low power mode.
 *
 * @return    None
 */
void Enter_LowPowerMode(void)
{
	// printf("usb enter low power mode\r\n");
	bDeviceState = SUSPENDED;
}

/*******************************************************************************
 * @fn         Leave_LowPowerMode
 *
 * @brief      Leave low power mode.
 *
 * @return     None
 */
void Leave_LowPowerMode(void)
{
	DEVICE_INFO *pInfo = &Device_Info;
	// printf("usb leave low power mode\r\n");
	if (pInfo->Current_Configuration != 0)
		bDeviceState = CONFIGURED;
	else
		bDeviceState = ATTACHED;
}

/*******************************************************************************
 * @fn         USB_Interrupts_Config
 *
 * @brief      Configrate USB interrupt.
 *
 * @return     None
 */
#define USBFSD_UEP_RX_EN 0x08
#define USBFSD_UEP_TX_EN 0x04
#define USBFSD_UEP_BUF_MOD 0x01
#define DEF_UEP_DMA_LOAD 0 /* Direct the DMA address to the data to be processed */
#define DEF_UEP_CPY_LOAD 1 /* Use memcpy to move data to a buffer */

#define USB_IOEN 0x00000080
#define USB_PHY_V33 0x00000040
#define UDP_PUE_MASK 0x0000000C
#define UDP_PUE_DISABLE 0x00000000
#define UDP_PUE_35UA 0x00000004
#define UDP_PUE_10K 0x00000008
#define UDP_PUE_1K5 0x0000000C

#define UDM_PUE_MASK 0x00000003
#define UDM_PUE_DISABLE 0x00000000
#define UDM_PUE_35UA 0x00000001
#define UDM_PUE_10K 0x00000002
#define UDM_PUE_1K5 0x00000003
void USB_Interrupts_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// EXTI_InitTypeDef EXTI_InitStructure;

	// EXTI_ClearITPendingBit(EXTI_Line18);
	// EXTI_InitStructure.EXTI_Line = EXTI_Line18;
	// EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	// EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	// EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	// EXTI_Init(&EXTI_InitStructure);
#if defined(CH32V203)
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
#elif defined(CH32X035)
	NVIC_InitStructure.NVIC_IRQChannel = USBFS_IRQn;
	AFIO->CTLR = (AFIO->CTLR & ~(UDP_PUE_MASK | UDM_PUE_MASK | USB_PHY_V33)) | UDP_PUE_10K | USB_IOEN;
	USBFSD->BASE_CTRL = 0x00;
	USBFSD->DEV_ADDR = 0x00;
	USBFSD->INT_FG = 0xff;
	USBFSD->BASE_CTRL = 0x20 | 0x08;
	USBFSD->INT_FG = 0xff;
	USBFSD->UDEV_CTRL = 0x80 | 0x01;
	USBFSD->INT_EN = 0x04 | 0x02 | 0x01;
#endif
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

#if defined(CH32V203)
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
#elif defined(CH32X035)
	NVIC_InitStructure.NVIC_IRQChannel = USBFSWakeUp_IRQn;
#endif
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
 * @fn         USB_Port_Set
 *
 * @brief      Set USB IO port.
 *
 * @param      NewState: DISABLE or ENABLE.
 *             Pin_In_IPU: Enables or Disables intenal pull-up resistance.
 *
 * @return     None
 */
#if defined(CH32V203)

void USB_Port_Set(FunctionalState NewState, FunctionalState Pin_In_IPU)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	if (NewState)
	{
		_SetCNTR(_GetCNTR() & (~(1 << 1)));
		GPIOA->CFGHR &= 0XFFF00FFF;
		GPIOA->OUTDR &= ~(3 << 11); // PA11/12=0
		GPIOA->CFGHR |= 0X00044000; // float
	}
	else
	{
		_SetCNTR(_GetCNTR() | (1 << 1));
		GPIOA->CFGHR &= 0XFFF00FFF;
		GPIOA->OUTDR &= ~(3 << 11); // PA11/12=0
		GPIOA->CFGHR |= 0X00033000; // LOW
	}

	if (Pin_In_IPU)
		(EXTEN->EXTEN_CTR) |= EXTEN_USBD_PU_EN;
	else
		(EXTEN->EXTEN_CTR) &= ~EXTEN_USBD_PU_EN;
}

#elif defined(CH32X035)
void USB_Port_Set(FunctionalState NewState, FunctionalState Pin_In_IPU)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_16;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_17;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

#endif
