/** @brief Modified from https://github.com/davebm1/c-sense-hat
 *  @file lsm9ds1.c
 *  @since 2025-02-12
 *  C code to read colour from the
 *  Raspberry Pi Sense HAT add-on board (LSM9DS1 sensor)
 */

#include "lsm9ds1.h"

/** Brief
 * @since 2024-02-16
 * @param void
 * @return 
 */
double ShGetAccelX()
{
    int fd = 0;
    uint8_t status = 0;

    /* open i2c comms */
    if ((fd = open(DEV_PATH, O_RDWR)) < 0) {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if (ioctl(fd, I2C_SLAVE, LSM9DS1_I2C_ADDR_AG) < 0) {
        perror("Unable to configure i2c slave device");
        close(fd);
        exit(1);
    }

    //printf("\nThe device at %#x identifies as %#x\n",LSM9DS1_I2C_ADDR_AG,i2c_smbus_read_byte_data(fd, LSM9DS1_WHO_AM_I));

    /* check we are who we should be */
    if (i2c_smbus_read_byte_data(fd, LSM9DS1_WHO_AM_I) != LSM9DS1_DEV_ID_AG) {
        printf("%s\n", "who_am_i error");
        close(fd);
        exit(1);
    }

    //adding this to the .c file for lab04
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x00);
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x84);
    i2c_smbus_write_byte_data(fd, CTRL_REG6_XL, 0x7B);

    do{
	    usleep(25000);
	    status = i2c_smbus_read_byte_data(fd, CTRL_REG1);
    }while(status =0);

    uint8_t out_x_l_xl = i2c_smbus_read_byte_data(fd, OUT_X_L_XL);
    uint8_t out_x_h_xl = i2c_smbus_read_byte_data(fd, OUT_X_H_XL);
    int16_t OUT_X = out_x_h_xl << 8 | out_x_l_xl;

    /* Power down the device */
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x00);
    close(fd);

    return OUT_X*0.000244;
}
/** Brief
 * @since 2024-02-16
 * @param void
 * @return 
 */
double ShGetAccelY()
{
    int fd = 0;
    uint8_t status = 0;

    /* open i2c comms */
    if ((fd = open(DEV_PATH, O_RDWR)) < 0) {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if (ioctl(fd, I2C_SLAVE, LSM9DS1_I2C_ADDR_AG) < 0) {
        perror("Unable to configure i2c slave device");
        close(fd);
        exit(1);
    }

    //printf("\nThe device at %#x identifies as %#x\n",LSM9DS1_I2C_ADDR_AG,i2c_smbus_read_byte_data(fd, LSM9DS1_WHO_AM_I));

    /* check we are who we should be */
    if (i2c_smbus_read_byte_data(fd, LSM9DS1_WHO_AM_I) != LSM9DS1_DEV_ID_AG) {
        printf("%s\n", "who_am_i error");
        close(fd);
        exit(1);
    }

    //also adding this to the .c file for lab04
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x00);
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x84);
    i2c_smbus_write_byte_data(fd, CTRL_REG6_XL, 0x7B);

    do{
	    usleep(25000);
	    status = i2c_smbus_read_byte_data(fd, CTRL_REG1);
    }while(status =0);

    uint8_t out_y_l_xl = i2c_smbus_read_byte_data(fd, OUT_Y_L_XL);
    uint8_t out_y_h_xl = i2c_smbus_read_byte_data(fd, OUT_Y_H_XL);
    int16_t OUT_Y = out_y_h_xl << 8 | out_y_l_xl;

    /* Power down the device */
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x00);
    close(fd);

    return OUT_Y*0.000244;
}

/** Brief
 * @since 2024-02-16
 * @param void
 * @return 
 */
double ShGetAccelZ()
{
    int fd = 0;
    uint8_t status = 0;

    /* open i2c comms */
    if ((fd = open(DEV_PATH, O_RDWR)) < 0) {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if (ioctl(fd, I2C_SLAVE, LSM9DS1_I2C_ADDR_AG) < 0) {
        perror("Unable to configure i2c slave device");
        close(fd);
        exit(1);
    }

    //printf("\nThe device at %#x identifies as %#x\n",LSM9DS1_I2C_ADDR_AG,i2c_smbus_read_byte_data(fd, LSM9DS1_WHO_AM_I));

    /* check we are who we should be */
    if (i2c_smbus_read_byte_data(fd, LSM9DS1_WHO_AM_I) != LSM9DS1_DEV_ID_AG) {
        printf("%s\n", "who_am_i error");
        close(fd);
        exit(1);
    }

    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x00);
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x84);
    i2c_smbus_write_byte_data(fd, CTRL_REG6_XL, 0x7B);

    do{
	    usleep(25000);
	    status = i2c_smbus_read_byte_data(fd, CTRL_REG1);
    }while(status =0);

    uint8_t out_z_l_xl = i2c_smbus_read_byte_data(fd, OUT_Z_L_XL);
    uint8_t out_z_h_xl = i2c_smbus_read_byte_data(fd, OUT_Z_H_XL);
    int16_t OUT_Z = out_z_h_xl << 8 | out_z_l_xl;

    /* Power down the device */
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x00);
    close(fd);

    return OUT_Z*0.000244;
}

/** Brief
 * @since 2024-02-16
 * @param void
 * @return 
 */
double ShGetMG(void)
{
    int fd = 0;
    uint8_t status = 0;

    /* open i2c comms */
    if ((fd = open(DEV_PATH, O_RDWR)) < 0) {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if (ioctl(fd, I2C_SLAVE, LSM9DS1_I2C_ADDR_MG) < 0) {
        perror("Unable to configure i2c slave device");
        close(fd);
        exit(1);
    }

    printf("\nThe device at %#x identifies as %#x\n",LSM9DS1_I2C_ADDR_MG,i2c_smbus_read_byte_data(fd, LSM9DS1_WHO_AM_I));

    /* check we are who we should be */
    if (i2c_smbus_read_byte_data(fd, LSM9DS1_WHO_AM_I) != LSM9DS1_DEV_ID_MG) {
        printf("%s\n", "who_am_i error");
        close(fd);
        exit(1);
    }

    /* Power down the device */
    i2c_smbus_write_byte_data(fd, CTRL_REG1, 0x00);
    close(fd);

    return (0);
}

