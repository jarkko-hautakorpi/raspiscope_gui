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
    Revision Info:  $Id: hdlc.c 1 2007-06-11 17:30:21Z Pieter $

============================================================================= */

#include "hdlc.h"

/* _____LOCAL DEFINITIONS____________________________________________________ */
// Significant octet values
#define HDLC_FLAG_SEQUENCE  0x7e   // Flag Sequence
#define HDLC_CONTROL_ESCAPE 0x7d   // Asynchronous Control Escape
#define HDLC_ESCAPE_BIT     0x20   // Asynchronous transparency modifier

// Values for FCS calculations.
#define HDLC_INITFCS        0xffff // Initial FCS value
#define HDLC_GOODFCS        0xf0b8 // Good final FCS value
#define HDLC_FCS_POLYNOMIAL 0x8408 // The FCS-16 generator polynomial x^16 + x^12 + x^5 + x^0

/// Macro to extract the high 8 bits of a 16-bit value (Most Significant Byte)
#define U16_HI(u16Data) ((unsigned char)((u16Data>>8)&0xff))

/// Macro to extract the low 8 bits of a 16-bit value (Least Significant Byte)
#define U16_LO(u16Data) ((unsigned char)(u16Data&0xff))

/* _____LOCAL VARIABLES______________________________________________________ */
static unsigned char  HDLC_au8RxFrame[HDLC_MRU];
static unsigned char  HDLC_u8RxFrameIndex;
static unsigned short int HDLC_u16RxFrameFCS;
static bool   HDLC_bRxCharEscape;

/// Pointer to the function that will be called to handle a received HDLC frame
static HDLC_tvOnRxFrame HDLC_pfOnRxFrame;
unsigned short int HDLC_au16FcsTable[256] =
{
      0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
      0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
      0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
      0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
      0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
      0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
      0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
      0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
      0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
      0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
      0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
      0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
      0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
      0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
      0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
      0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
      0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
      0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
      0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
      0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
      0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
      0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
      0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
      0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
      0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
      0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
      0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
      0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
      0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
      0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
      0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
      0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};


/// Update 16-bit CRC macro
#define UPDATE_FCS(u16Fcs, u8Data) u16Fcs = (u16Fcs >> 8) ^ (&HDLC_au16FcsTable[(u16Fcs ^ u8Data) & 0xff]);
unsigned int UPDATE_FCS_FUNCTION(unsigned short int u16Fcs, unsigned char u8Data);

/// Function to send a byte
static void HDLC_vTxByte(unsigned char u8Data)
{

    while(!serialDataLink::USART_TXBuffer_PutByte(serialDataLink::USART_data_t * , &u8Data)) // = USART_TXBuffer_PutByte(&USART_data, sendArray[i]);
    {
        ;
    }
}
unsigned int UPDATE_FCS_FUNCTION(unsigned short int u16Fcs, unsigned char u8Data) {

    unsigned int first;
    short unsigned int second;
    first = (u16Fcs >> 8);
    second = HDLC_au16FcsTable[(u16Fcs ^ u8Data) & 0xff];
    u16Fcs =  first ^ second;
    return u16Fcs;
}

/**
 *  Initialise HDLC encapsulation layer.
 * 
 * @param[in] pfOnRxFrame Pointer to handler that is called when a correct frame is received.
 */
void HDLC_vInit(HDLC_tvOnRxFrame pfOnRxFrame)
{
    HDLC_u8RxFrameIndex = 0;
    HDLC_u16RxFrameFCS  = HDLC_INITFCS;
    HDLC_bRxCharEscape  = false;

    HDLC_pfOnRxFrame    = pfOnRxFrame;
}

/**
 *  Function handler that is fed all raw received data.
 * 
 *  @param[in] u8Data   received 8-bit data
 * 
 */
void HDLC_vOnRxByte(unsigned char u8Data)
{
    // Start/End sequence
    if(u8Data == HDLC_FLAG_SEQUENCE)
    {
        // If Escape sequence + End sequence is received then this packet must be silently discarded
        if(HDLC_bRxCharEscape == true)
        {
            HDLC_bRxCharEscape = false;
        }
        //  Minimum requirement for a valid frame is reception of good FCS
        else if((HDLC_u8RxFrameIndex>=sizeof(HDLC_u16RxFrameFCS))&&(HDLC_u16RxFrameFCS == HDLC_GOODFCS))
        {
            // Pass on frame with FCS field removed
            (*HDLC_pfOnRxFrame)(HDLC_au8RxFrame,(unsigned char)(HDLC_u8RxFrameIndex-2));
        }
        // Reset for next packet
        HDLC_u8RxFrameIndex = 0;
        HDLC_u16RxFrameFCS   = HDLC_INITFCS;
        return;
    }

    // Escape sequence processing
    if(HDLC_bRxCharEscape)
    {
        HDLC_bRxCharEscape  = false;
        u8Data             ^= HDLC_ESCAPE_BIT;
    }
    else if(u8Data == HDLC_CONTROL_ESCAPE)
    {
        HDLC_bRxCharEscape = true;
        return;
    }

    // Store received data
    HDLC_au8RxFrame[HDLC_u8RxFrameIndex] = u8Data;

    // Calculate checksum
    UPDATE_FCS_FUNCTION(HDLC_u16RxFrameFCS,u8Data);

    // Go to next position in buffer
    HDLC_u8RxFrameIndex++;

    // Check for buffer overflow
    if(HDLC_u8RxFrameIndex == HDLC_MRU)
    {
        // Wrap index
        HDLC_u8RxFrameIndex  = 0;

        // Invalidate FCS so that packet will be rejected
        HDLC_u16RxFrameFCS  ^= 0xFFFF;
    }
}

/**
 *  Encapsulate and send an HDLC frame.
 * 
 *  @param[in] pu8Buffer        Buffer containing data for transmission
 *  @param[in] u8BytesToSend    Number of bytes in buffer to be transmitted
 *
 */
void HDLC_vTxFrame(const unsigned char* pu8Buffer, unsigned char u8BytesToSend)
{
    unsigned char  u8Data;
    unsigned short int u16Fcs = HDLC_INITFCS;

    // Start marker
    HDLC_vTxByte(HDLC_FLAG_SEQUENCE);

    // Send escaped data
    while(u8BytesToSend)
    {
        // Get next data
        u8Data = *pu8Buffer++;
        
        // Update checksum
        UPDATE_FCS_FUNCTION(u16Fcs,u8Data);
        
        // See if data should be escaped
        if((u8Data == HDLC_CONTROL_ESCAPE) || (u8Data == HDLC_FLAG_SEQUENCE))
        {
            HDLC_vTxByte(HDLC_CONTROL_ESCAPE);
            u8Data ^= HDLC_ESCAPE_BIT;
        }
        
        // Send data
        HDLC_vTxByte(u8Data);
        
        // decrement counter
        u8BytesToSend--;
    }

    // Invert checksum
    u16Fcs ^= 0xffff;

    // Low byte of inverted FCS
    u8Data = U16_LO(u16Fcs);
    if((u8Data == HDLC_CONTROL_ESCAPE) || (u8Data == HDLC_FLAG_SEQUENCE))
    {
        HDLC_vTxByte(HDLC_CONTROL_ESCAPE);
        u8Data ^= HDLC_ESCAPE_BIT;
    }
    HDLC_vTxByte(u8Data);

    // High byte of inverted FCS
    u8Data = U16_HI(u16Fcs);
    if((u8Data == HDLC_CONTROL_ESCAPE) || (u8Data == HDLC_FLAG_SEQUENCE))
    {
        HDLC_vTxByte(HDLC_CONTROL_ESCAPE);
        u8Data ^= HDLC_ESCAPE_BIT;
    }
    HDLC_vTxByte(u8Data);

    // End marker
    HDLC_vTxByte(HDLC_FLAG_SEQUENCE);    
}
