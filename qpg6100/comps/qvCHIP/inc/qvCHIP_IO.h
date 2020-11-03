/*
 * Copyright (c) 2020, Qorvo Inc
 *
 * This software is owned by Qorvo Inc
 * and protected under applicable copyright laws.
 * It is delivered under the terms of the license
 * and is intended and supplied for use solely and
 * exclusively with products manufactured by
 * Qorvo Inc.
 *
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS"
 * CONDITION. NO WARRANTIES, WHETHER EXPRESS,
 * IMPLIED OR STATUTORY, INCLUDING, BUT NOT
 * LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * QORVO INC. SHALL NOT, IN ANY
 * CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES,
 * FOR ANY REASON WHATSOEVER.
 *
 * $Change: 159842 $
 * $DateTime: 2020/10/30 14:04:59 $
 */

/** @file "qvCHIP.h"
 *
 *  CHIP wrapper API
 *
 *  Declarations of the IO specific public functions and enumerations of qvCHIP.
*/

#ifndef _QVCHIP_IO_H_
#define _QVCHIP_IO_H_

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*****************************************************************************
 *                    Enum Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*! LED indexes */
#define LED_RED   0
#define LED_GREEN 1
#define LED_WHITE 2

/*! Button indexes */
#define BTN_LOCK     0
#define BTN_FUNCTION 1

/*****************************************************************************
 *                    Functional Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/** @brief Callback type for button press callback */
typedef void (*pBtnCback)(uint8_t btnIdx, bool btnPressed);

/*****************************************************************************
 *                    Public Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *                    LED/BTN API
 *****************************************************************************/

/** @brief Set LED ON or OFF.
*
*   @param ledNr                     The index of the LED that is controlled.
*   @param state                     LED on (true) or off (false).
*/
void qvCHIP_LedSet(uint8_t ledNr, bool state);

/** @brief Blink a LED with specified on and off period.
*
*   @param ledNr                     The index of the LED that is controlled.
*   @param onMs                      How many msec should the ON state last.
*   @param offMs                     How many msec should the OFF state last.
*/
void qvCHIP_LedBlink(uint8_t ledNr, uint16_t onMs, uint16_t offMs);

/** @brief Store internally an upper layer callback for signaling button presses.
*
*   @param btnCback                  Pointer to the button handler to be stored internally.
*/
void qvCHIP_SetBtnCallback(pBtnCback btnCback);

/** @brief Initialize UART for use.
 *
*/

void qvCHIP_UartInit(void);

/** @brief Transmit data over the UART
 *
 *  @param length         Length of data to send
 *  @param txBuffer       Pointer to a buffer to transmit
*/
void qvCHIP_UartTxData(uint8_t length, const char* txBuffer);

/** @brief Get received UART data
 *
 *  @param length          Max length of data to retrieve
 *  @param txBuffer        Pointer to a buffer to received the data in. 
 *                         It is assumed to be large enough to hold 'length' bytes
 *
 *  @return receivedLength Amount of bytes returned in the buffer.
 *                         If more data was pending, only 'length' bytes are returned.
*/
uint8_t qvCHIP_UartReadRxData(uint8_t length, char* rxBuffer);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_QVCHIP_IO_H_
