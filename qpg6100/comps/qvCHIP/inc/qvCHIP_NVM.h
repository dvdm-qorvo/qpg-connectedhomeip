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
 * $Change: 159735 $
 * $DateTime: 2020/10/29 21:54:42 $
 */

/** @file "qvCHIP.h"
 *
 *  CHIP wrapper API
 *
 *  Declarations of the NVM specific public functions and enumerations of qvCHIP.
*/

#ifndef _QVCHIP_NVM_H_
#define _QVCHIP_NVM_H_

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*****************************************************************************
 *                    Enum Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Functional Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Public Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *                    NVM API
 *****************************************************************************/

/** @brief Initialization of NVM memory used for CHIP
*/
void qvCHIP_Nvm_Init(void);

/** @brief Get maximum length of data identified by keyId
 *
 *  @param key NVM identifier to fetch maximum length for.
 *  @param maxLength Maximum length for given key.
*/
uint16_t qvCHIP_Nvm_GetMaxKeyLen(uint16_t key);

/** @brief Backup data to NVM for a given key.
 *
 *  @param key             Identifier for NVM area to backup.
 *  @param pRamLocation    Pointer to data to backup.
 *  @param length          Length of data to backup. Cannot exceed maximum length for the key.
*/
void qvCHIP_Nvm_Backup(uint16_t key, uint8_t* pRamLocation, uint16_t length);

/** @brief Restore data from NVM for a given key.
 *
 *  @param key            Identifier for NVM area to restore.
 *  @param pRamLocation   Pointer to the RAM location to restore data to.
 *  @param length         Length of data to restore. Cannot exceed maximum length for the key.
                          If smaller then the maximum length a partial restore will be executed.
*/
bool qvCHIP_Nvm_Restore(uint16_t key, uint8_t* pRamLocation, uint16_t* length);

/** @brief Remove data from NVM for a given key.
 *
 *  @param key             Identifier for NVM data to remove.
*/
void qvCHIP_Nvm_ClearValue(uint16_t key);

/** @brief Returns true if data for a given key exists in NVM.
 *
 *  @param key             Identifier for NVM data to check for existence.
 *  @param length          Returns length of the data stored for the key.
 *  @return exists         Returns true if data exists for given key.
*/
bool qvCHIP_Nvm_ValueExists(uint16_t key, uint16_t* length);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_QVCHIP_NVM_H_
