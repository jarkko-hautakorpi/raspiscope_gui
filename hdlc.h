#ifndef __HDLC_H__
#define __HDLC_H__
/* =============================================================================

    Copyright (c) 2006 Piconomic Design [www.piconomic.co.za]
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
    
    * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
    
    * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.

    Title:          HDLC encapsulation layer
    Author(s):      Pieter Conradie
    Creation Date:  2007-03-31
    Revision Info:  $Id: hdlc.h 1 2007-06-11 17:30:21Z Pieter $

============================================================================= */
/** 
 *  @ingroup GENERAL
 *  @defgroup HDLC hdlc.h : HDLC encapsulation layer
 *
 *  This component encapsulates packets in HDLC-like frames.
 *
 *  Files: hdlc.h & hdlc.c
 *
 *  @par
 *  The purpose of this module is to detect errors in received packets
 *  using a 16-bit CRC appended to the data and to synchronise to the start and
 *  end of a packet by adding a @b unique start and end marker (byte 0x7E or 
 *  ASCII character '~'). This allows a receiver to detect the start of a new packet, 
 *  without using a timeout mechanism (no timers). This is very useful when 
 *  communicating with a non real-time operating system, e.g. Windows.
 *
 *  @par
 *  To make sure that 0x7E only occurs to mark the valid start and end of a packet, 
 *  any 0x7E bytes in the data is replaced with a 0x7D, @b 0x5E sequence (known as 
 *  "escaping"). @b 0x5E = 0x7E xor 0x20. Any data byte 0x7D must also 
 *  be "escaped", meaning it must be replaced with a 0x7D, @b 0x5D sequence. 
 *  @b 0x5D = 0x7D xor 0x20.
 *
 *  @par
 *  In general any data byte can be escaped by replacing it with 0x7D and the original 
 *  data byte xor'd with 0x20 (toggling bit 5). This is useful if software flow control 
 *  is used with XON and XOFF characters and these characters should not occur accidently
 *  in the data.
 *
 *  @par Reference:
 *  RFC 1662 "PPP in HDLC-like Framing"
 *
 *  @note The overhead with escaping may mean that a packet will be more than doubled in 
 *        size if all of the data bytes is 0x7D or 0x7E, but the probability of this
 *        sequency occuring is low.
 *
 *  @note Linking dependency on the higher communication layer is avoided by passing a 
 *        pointer to the function HDLC_vInit(HDLC_tvOnRxFrame pfOnRxFrame). The pointer 
 *        function call overhead can be avoided by replacing a direct call to the function 
 *        handler if it is known at compile time. This means that hdlc.c must be modifed 
 *        to avoid a small processing overhead.
 *
 * @note  This module is dependant on @ref UART1. This is very easy to change in hdlc.c
 *  
 *  @par Example:
 *  @include hdlc_test.c
 *
 *  @{
 */
#include <stdio.h>
#include <stdbool.h>
#include "serialdatalink.h"
/* _____DEFINITIONS _________________________________________________________ */
/// Receive Packet size (Maximum Receive Unit)
#define HDLC_MRU    64  

/* _____TYPE DEFINITIONS_____________________________________________________ */
/// Definition for a pointer to a function that will be called once a frame has been received
typedef void (*HDLC_tvOnRxFrame)(const unsigned char* pU8Buffer, unsigned short int u16BytesReceived);

/* _____PUBLIC FUNCTION DECLARATIONS_________________________________________ */
extern void HDLC_vInit    (HDLC_tvOnRxFrame pfOnRxFrame);

extern void HDLC_vOnRxByte(unsigned char u8Data);
extern void HDLC_vTxFrame (const unsigned char* pu8Buffer, unsigned char u8BytesToSend);

/**
 *  @}
 */
#endif
