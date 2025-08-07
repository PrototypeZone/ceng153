/** @brief Constants, structures, function prototypes for lsm9ds1
 *  @file lsm9ds1.h
 *  @since 2025-02-14
 */
#ifndef LSM9DS1_H
#define LSM9DS1_H

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
//magnetometer 0x1c(0x1e) and accelerometer/gyroscope 0x6a(0x6b)
#define LSM9DS1_I2C_ADDR_MG 0x1C
#define LSM9DS1_I2C_ADDR_AG 0x6A
#define LSM9DS1_WHO_AM_I 0x0F
#define LSM9DS1_DEV_ID_MG 0x3D
#define LSM9DS1_DEV_ID_AG 0x68

#ifndef CTRL_REG1
#define CTRL_REG1 0x20
#endif // CTRL_REG1
#define CTRL_REG6_XL 0x20

//added these lines to .h file for lab04
#define OUT_X_L_XL 0x28
#define OUT_X_H_XL 0x29
#define OUT_Y_L_XL 0x2A
#define OUT_Y_H_XL 0x2B
#define OUT_Z_L_XL 0x2C
#define OUT_Z_H_XL 0x2D

// Enumerated Types

// Structures

// Function Prototypes
/// @cond INTERNAL
double ShGetMG();

//also added these lines to .h file for lab04
double ShGetAccelX();
double ShGetAccelY();
double ShGetAccelZ();

/// @endcond

#endif // LSM9DS1_H
