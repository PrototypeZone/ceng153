/** @brief Constants, structures, function prototypes for tcs3400
 *  @file tcs3400.h
 *  @since 2024-03-15
 */
#ifndef TCS3400_H
#define TCS3400_H

// Includes
#include <fcntl.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Constants
#ifndef DEV_PATH
#define DEV_PATH "/dev/i2c-1"
#endif // DEV_PATH
#define TCS3400_I2C_ADDR 0x39
#define TCS3400_WHO_AM_I 0x92
#define TCS3400_DEV_ID 0x90 //TCS34001 & TCS34005
#define TCS3400_ENABLE 0x80 //7:0,6,5:0,3,2:0,1:AEN,0:PON
#define TCS3400_ATIME 0x81 //Integration time
#define TCS3400_CONTROL 0x8F //Gain
#define TCS3400_WTIME 0x83 //Default is 0XFF which should be fine
#define TCS3400_STATUS 0x93 //10100 (0x14) changes to 10101 (0x15), can also go 10,14,94,95
#define INTG_TIME_1_CYCLES   0xFF //Default should be fine
#define INTG_TIME_10_CYCLES  0xF6
#define INTG_TIME_37_CYCLES  0xDB
#define INTG_TIME_64_CYCLES  0xC0
#define INTG_TIME_256_CYCLES 0x00
#define GAIN_1X  0x00
#define GAIN_4X  0x01
#define GAIN_16X 0x02
#define GAIN_64X 0x03
#define TCS3400_AVALID 0x01

#define RDATAL 0x96 // Red data low byte
#define RDATAH 0x97 // Red data high byte
#define GDATAL 0x98 // Green data low byte
#define GDATAH 0x99 // Green data high byte
#define BDATAL 0x9A // Blue data low byte
#define BDATAH 0x9B // Blue data high byte

// Enumerated Types

// Structures
struct colour {
    int16_t red;
    int16_t green;
    int16_t blue;
};

// Function Prototypes
/// @cond INTERNAL
struct colour ShGetColour();
/// @endcond

#endif // TCS3400_H