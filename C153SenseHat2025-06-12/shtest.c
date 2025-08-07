/** @brief Examples of sense-hat usage
 *  @file shtest.c
 *  @since 2024-06-09
 *
 *  compile by typing gcc shtest.c hts221.c lps25h.c led2472g.c lsm9ds1.c tcs3400.c -li2c -o /home/pi/shtest
 *             
 *  run upon boot from /etc/rc.local by line sudo /home/pi/shtest
 *
 */

#include "shtest.h"

/** Based on shtest.py and function in shmenu.c
 * @author Paul Moggach
 * @author Kris Medri
 * @since 2024-02-16
 * C code Demonstration of Astro Pi Sense Hat.
 */
int main(void) 
{
    // Output 
    fprintf(stdout,"Unit: %LX\n",ShGetSerial());
    struct fb_t *fb;
    fb=ShInit(fb);
    memset(fb, 0, 128);
    usleep (300000);

    //shtest
    uint16_t logo[8][8] = { HB,HB,HB,HB,HB,HB,HB,HB,
			HB,HB,HW,HB,HB,HW,HB,HY,
			HB,HB,HW,HB,HB,HW,HY,HY,
			HB,HB,HW,HB,HB,HW,HY,HY,
			HB,HB,HW,HW,HW,HW,HY,HY,
			HB,HB,HW,HY,HY,HW,HY,HY,
			HB,HY,HW,HY,HY,HW,HY,HY,
			HY,HY,HY,HY,HY,HY,HY,HY,
    };
    ShViewPattern(logo,fb);
    usleep (300000);
    char str[33];
    sprintf(str,"T: %5.1fC  H: %5.1f%%  P: %6.1fmB",ShGetTemperature(),ShGetHumidity(),ShGetPressure());
    ShViewMessage(str,100,WHITE,BLACK,fb);

    return EXIT_SUCCESS;
}

