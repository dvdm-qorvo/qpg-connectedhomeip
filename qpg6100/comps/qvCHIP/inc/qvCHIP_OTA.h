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
 * $Change: 186475 $
 * $DateTime: 2021/12/01 14:14:42 $
 */

/** @file "qvCHIP_OTA.h"
 *
 *  CHIP wrapper OTA Upgrade API
 *
 *  Declarations of the OTA specific public functions and enumerations of qvCHIP.
*/

#ifndef _QVCHIP_OTA_H_
#define _QVCHIP_OTA_H_

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*****************************************************************************
 *                    Enum Definitions
 *****************************************************************************/

/** @enum qvCHIP_OtaStatus_t */
//@{
#define qvCHIP_OtaStatusSuccess                                0x00
#define qvCHIP_OtaStatusFailedChecksumError                    0x01
#define qvCHIP_OtaStatusFailedVerify                           0x02
#define qvCHIP_OtaStatusFailedVersionError                     0x03
#define qvCHIP_OtaStatusFailedProgramError                     0x04
#define qvCHIP_OtaStatusFailedRescueInstalled                  0x05
#define qvCHIP_OtaStatusWriteError                             0x06
#define qvCHIP_OtaStatusInvalidAddress                         0x07
#define qvCHIP_OtaStatusOutOfRange                             0x08
#define qvCHIP_OtaStatusStoreImageFailed                       0x09
#define qvCHIP_OtaStatusLoadImageFailed                        0x0A
#define qvCHIP_OtaStatusParseFailed                            0x0B
#define qvCHIP_OtaStatusInvalidImage                           0x0C
#define qvCHIP_OtaStatusPreCheckFailed                         0x0D
#define qvCHIP_OtaStatusInvalidParam                            0x0E
/** @typedef qvCHIP_OtaStatus_t
    @brief General return status for all functions of this API

    @li @c qvCHIP_OtaStatusSuccess               The requested operation was completed successfully.
    @li @c qvCHIP_OtaStatusFailedChecksumError   The requested operation failed due to checksum error.
    @li @c qvCHIP_OtaStatusFailedVerify          The image verification failed.
    @li @c qvCHIP_OtaStatusFailedVersionError    Version is not newer then currently running.
    @li @c qvCHIP_OtaStatusFailedProgramError    The requested operation failed due to program error.
    @li @c qvCHIP_OtaStatusFailedRescueInstalled Failed rescue image installment.
    @li @c qvCHIP_OtaStatusWriteError            Failed to write to ota area.
    @li @c qvCHIP_OtaStatusInvalidAddress        Unexpected Address.
    @li @c qvCHIP_OtaStatusOutOfRange            Trying to access an address that is outside the range.
    @li @c qvCHIP_OtaStatusStoreImageFailed      Failure in storing the image.
    @li @c qvCHIP_OtaStatusLoadImageFailed       Failure in loading the image.
    @li @c qvCHIP_OtaStatusParseFailed           Failure in parsing the image.
    @li @c qvCHIP_OtaStatusInvalidImage          Invalid image.
    @li @c qvCHIP_OtaStatusPreCheckFaild         Upgrade image pre-wipe check failed.
    @li @c qvCHIP_OtaStatusInvalidParam           Pointer passed as an argument is NULL.
*/
typedef uint8_t                             qvCHIP_OtaStatus_t;
//@}
/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Functional Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/** @pointer to function qvCHIP_OtaUpgradeHandledCback_t
 *  @brief Application API: Pointer to callback for upgrade complete.
*/
typedef void (*qvCHIP_OtaUpgradeHandledCback_t)(bool upgradeHandled, qvCHIP_OtaStatus_t upgradeStatus); 

/** @pointer to function qvCHIP_OtaEraseCompleteCback_t
 *  @brief Application API: Pointer to callback for erase complete.
*/
typedef void (*qvCHIP_OtaEraseCompleteCback_t) (void);

/*****************************************************************************
 *                    Public Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *                    Flash API
 *****************************************************************************/

/** @brief Application API: erase the OTA area (blocking).
*/
void qvCHIP_OtaEraseArea(void);

/** @brief Application API: start non-blocking erase of the OTA area.
*
*   @param cb                        Pointer to erase complete callback
*/
void qvCHIP_OtaStartEraseArea(qvCHIP_OtaEraseCompleteCback_t cb);

/** @brief Application API: get total size of the OTA upgrade area.
*
*   @return size Number of bytes in the OTA upgrade area.
*/
uint32_t qvCHIP_OtaGetAreaSize(void);

/** @brief Application API: get start address of the OTA upgrade area.
*
*   @return address
*/
uint32_t qvCHIP_OtaGetAreaStartAddress(void);

/** @brief Application API: initialize CRC so a writing operation can start.
*/
void qvCHIP_OtaStartWrite(void);

/** @brief Application API: write chunk of data to external or internal storage device and update CRC.
*
*   @param address                   Address location of where to write the data.
*   @param length                    Number of bytes to write.
*   @param dataChunk                 Pointer to the data to write.
*   @return result
*/
qvCHIP_OtaStatus_t qvCHIP_OtaWriteChunk(uint32_t address, uint16_t length, uint8_t* dataChunk);

/** @brief Application API: read chunk of data from external or internal storage device.
*
*   @param address                   Address location of data to read.
*   @param length                    Number of bytes to read.
*   @param dataChunk                 Pointer to the buffer to store read data.
*   @return result
*/
qvCHIP_OtaStatus_t qvCHIP_OtaReadChunk(uint32_t address, uint16_t length, uint8_t* dataChunk);

/** @brief Application API: get current value of CRC.
*
*   @return crcValue
*/
uint32_t qvCHIP_OtaGetCrc(void);

/** @brief Application API: set the value of CRC.
*
*   @param crcValue
*/
void qvCHIP_OtaSetCrc(uint32_t crcValue);

/** @brief Application API: set the new pending image information for the User Mode Bootloader.
*
*   This writes the properties of the new update image to the software upgrade table in flash. The User Mode Bootloader
*   inspects this information to determine whether to carry out an update, and if so where to find the update image.
*
*   @param swVer                     Software version of the new image.
*   @param hwVer                     Hardware version of the new image.
*   @param startAddr                 Image base address.
*   @param imgSz                     Image size (in bytes).
*   @return status                   qvCHIP_OtaStatusSuccess if the pending image set is successful,
*                                    qvCHIP_OtaStatusFailedVersionError if the pending image set failed
*                                    (version incompatibility)
*/
qvCHIP_OtaStatus_t qvCHIP_OtaSetPendingImage(uint32_t swVer, uint32_t hwVer, uint32_t startAddr, uint32_t imgSz);

/** @brief Application API: this function stores an application callback to be 
 *  invoked when the initialisation is done if an upgrade is handled.
*
*   The callback informs the application of the result of the update.
*
*   @param upgradeHandled         Parameter that indicates if an upgrade was handled
*   @param upgradeStatus          Parameter that indicates the status of the handled upgrade
*/
void qvCHIP_OtaSetUpgradeHandledCb(qvCHIP_OtaUpgradeHandledCback_t upgradeHandledCb);


/** @brief Application API: trigger a hardware reset that will jump to the bootloader (to execute update).
*/
void qvCHIP_OtaReset(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_QVCHIP_OTA_H_
