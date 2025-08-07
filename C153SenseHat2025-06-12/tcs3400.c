/** @brief Modified from https://github.com/davebm1/c-sense-hat
 *  @file tcs3400.c
 *  @since 2024-03-15
 *  @author Credit to https://github.com/seancaulfield/TCS3400/ Sean Caulfield <sean@yak.net>
 *  C code to read colour from the
 *  Raspberry Pi Sense HAT add-on board (TCS3400 sensor)
 */

#include "tcs3400.h"

/*compile with gcc tcs3400.c -li2c, run with ./a.out
int main(void) 
{
    // Output 
    struct colour readings=ShGetColour();
    printf("(Red,Green,Blue)=(%8u,%8u,%8u)\n",readings.red,readings.green,readings.blue); 

    return (0);
}*/

/** Brief
 * @since 2024-03-15
 * @param void
 * @return struct colour
 */
struct colour ShGetColour(void)
{
    int fd = 0;
    uint8_t status = 0;

    /* open i2c comms */
    if ((fd = open(DEV_PATH, O_RDWR)) < 0) {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if (ioctl(fd, I2C_SLAVE, TCS3400_I2C_ADDR) < 0) {
        perror("Unable to configure i2c slave device");
        close(fd);
        exit(1);
    }

    /* check we are who we should be */
    if (i2c_smbus_read_byte_data(fd, TCS3400_WHO_AM_I) != TCS3400_DEV_ID) {
        printf("%s\n", "who_am_i error");
        close(fd);
        exit(1);
    }

	// Power on
    i2c_smbus_write_byte_data(fd, TCS3400_ENABLE, 0x01);
	// Gain
	i2c_smbus_write_byte_data(fd, TCS3400_CONTROL, GAIN_64X);
	// ADC on
    i2c_smbus_write_byte_data(fd, TCS3400_ENABLE, 0x01|0x02);

	while((i2c_smbus_read_byte_data(fd, TCS3400_STATUS)&TCS3400_AVALID)!=0x01);
	//for(int i=0;i<1000;i++)
	//{
	//	printf("TCS3400_STATUS=%x != %x =",i2c_smbus_read_byte_data(fd, TCS3400_STATUS)&TCS3400_AVALID,0x01);
	//	printf("TCS3400_STATUS=%x\n",(i2c_smbus_read_byte_data(fd, TCS3400_STATUS)&TCS3400_AVALID)!=0x01);
	//}
	
    uint8_t red_l = i2c_smbus_read_byte_data(fd, RDATAL);
	//printf("red_l=%d\n",red_l);
    uint8_t red_h = i2c_smbus_read_byte_data(fd, RDATAH);
    uint8_t green_l = i2c_smbus_read_byte_data(fd, GDATAL);
	//printf("green_l=%d\n",green_l);
    uint8_t green_h = i2c_smbus_read_byte_data(fd, GDATAH);
	//printf("green_h=%d\n",green_h);
    uint8_t blue_l = i2c_smbus_read_byte_data(fd, BDATAL);
    uint8_t blue_h = i2c_smbus_read_byte_data(fd, BDATAH);

    struct colour reading;
    reading.red = red_h << 8 | red_l;
    reading.green = green_h << 8 | green_l;
    reading.blue = blue_h << 8 | blue_l;
	//printf("(Red,Green,Blue)=(%d,%d,%d)\n",reading.red,reading.green,reading.blue);
    /* Power down the device */
    i2c_smbus_write_byte_data(fd, TCS3400_ENABLE, 0x00);
    close(fd);

    return reading;
}

