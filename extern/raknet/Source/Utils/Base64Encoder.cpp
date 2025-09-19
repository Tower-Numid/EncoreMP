/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  Copyright (c) 2016-2018, TES3MP Team
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "Base64Encoder.h"
#include <cstdlib>

const char *base64Map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char *Base64Map(void)
{
    return base64Map;
}

// 3/17/2013 must be unsigned char or else it will use negative indices
int Base64Encoding(const unsigned char *inputData, int dataLength, char *outputData)
{
    // http://en.wikipedia.org/wiki/Base64

    auto fnWriteBase64 = [](char *output, char base64, int &offset)
    {
        static int charCount = 0;
        output[offset++] = base64;
        if ((++charCount % 76) == 0)
        {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }
    };

    int outputOffset = 0;
    int write3Count = dataLength / 3;
    int j = 0;
    for (; j < write3Count; ++j)
    {
        // 6 leftmost bits from first byte, shifted to bits 7,8 are 0
        fnWriteBase64(outputData, base64Map[inputData[j * 3 + 0] >> 2], outputOffset);

        // Remaining 2 bits from first byte, placed in position, and 4 high bits from the second byte, masked to ignore bits 7,8
        fnWriteBase64(outputData, base64Map[((inputData[j * 3 + 0] << 4) | (inputData[j * 3 + 1] >> 4)) & 63], outputOffset);

        // 4 low bits from the second byte and the two high bits from the third byte, masked to ignore bits 7,8
        fnWriteBase64(outputData, base64Map[((inputData[j * 3 + 1] << 2) | (inputData[j * 3 + 2] >> 6)) & 63],  outputOffset); // Third 6 bits

        // Last 6 bits from the third byte, masked to ignore bits 7,8
        fnWriteBase64(outputData, base64Map[inputData[j * 3 + 2] & 63], outputOffset);
    }

    if (dataLength % 3 == 1)
    {
        // One input byte remaining
        fnWriteBase64(outputData, base64Map[inputData[j * 3 + 0] >> 2], outputOffset);

        // Remaining 2 bits from first byte, placed in position, and 4 high bits from the second byte, masked to ignore bits 7,8
        fnWriteBase64(outputData, base64Map[((inputData[j * 3 + 0] << 4) | (inputData[j * 3 + 1] >> 4)) & 63], outputOffset);

        // Pad with two equals
        outputData[outputOffset++] = '=';
        outputData[outputOffset++] = '=';
    }
    else if (dataLength % 3 == 2)
    {
        // Two input bytes remaining

        // 6 leftmost bits from first byte, shifted to bits 7,8 are 0
        fnWriteBase64(outputData, base64Map[inputData[j * 3 + 0] >> 2], outputOffset);

        // Remaining 2 bits from first byte, placed in position, and 4 high bits from the second byte, masked to ignore bits 7,8
        fnWriteBase64(outputData, base64Map[((inputData[j * 3 + 0] << 4) | (inputData[j * 3 + 1] >> 4)) & 63], outputOffset);

        // 4 low bits from the second byte, followed by 00
        fnWriteBase64(outputData, base64Map[(inputData[j * 3 + 1] << 2) & 63], outputOffset);

        // Pad with one equal
        outputData[outputOffset++] = '=';
    }

    // Append \r\n
    outputData[outputOffset++] = '\r';
    outputData[outputOffset++] = '\n';
    outputData[outputOffset] = 0;

    return outputOffset;
}