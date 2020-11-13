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
 * $Header: //depot/main/Embedded/Applications/P236_CHIP/vlatest/comps/qvCHIP/src/qvCHIP.c#12 $
 * $Change: 160145 $
 * $DateTime: 2020/11/04 09:21:00 $
 */

/** @file "trng.c"
 *  
 *  True random number generator for Qorvo chips
*/

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "qvCHIP.h"

#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT) && defined(MBEDTLS_ENTROPY_C)

#include "mbedtls/entropy.h"

int mbedtls_hardware_poll( void *data,
                           unsigned char *output,
                           size_t len,
                           size_t *olen ) {
    int ret = 0;
    (void) data;

    qvCHIP_RandomGet(len, output);
    *olen = len;

    return ret;
}

#endif /* MBEDTLS_ENTROPY_HARDWARE_ALT && MBEDTLS_ENTROPY_C */
