/** @brief Examples of sense-hat usage
 *  @file shmenu.c
 *  @since 2024-03-27
 *
 *  compile by typing gcc shmenu.c hts221.c lps25h.c led2472g.c lsm9ds1.c tcs3400.c -li2c
 *               or just 'make'
 *  run by typing ./a.out
 *
 */

#include "shmenu.h"

/** Menu system providing access to examples of sense-hat usage
 * @version CENG153, serial: 1a2b3c4d
 * @author Kris Medri
 * @author Modifier's Name
 * @since 2024-03-15
 * @param void
 * @return void
 */
int main(void)
{
    char cmd;
    char enterkey;

    //for (;;) {
    //while(1){
    do{
        printf("\nExamples of sense-hat usage\n");
        printf("Commands: 0=serial, 1=led2472g, ");
        printf("3=hts221, 4=lps25h, 7=shtest, q=quit\n\n");
        printf("Enter command: ");
        scanf("%c", &cmd);
        scanf("%c", &enterkey);
        if (cmd=='0')
        {
            fprintf(stdout,"Unit: %LX\n",ShGetSerial());
        } 
        else if (cmd=='1')
        {
            led2472g();
        } 
        else if (cmd=='2')
        {
            int ret; //TODO port snake game
	    //ret=game();
	    //if (ret)
	    //{
		//fprintf(stderr,"Error code from snake is: %d\n",ret);
	    //}
        } 
        else if (cmd=='3')
        {
            hts221(); //temp and humidity
        }
        else if (cmd=='4')
        {
            lps25h(); //temp and pressure
        } 
        else if (cmd=='5')
        {
            //TODO IMU magnetometer and accelerometer/gyroscope
	        lsm9ds1();
        } 
        else if (cmd=='6')
        {
            //TODO Colour Sensor
	        tcs3400();
        } 
        else if (cmd=='7')
        {
            //ported logo and scrolling test readings
	        shtest();
        } 
        else if (cmd=='8')
        {
            //TODO port simple LED on GPIO 17
        } 
        else if (cmd=='9')
        {
            //TODO port bubble level
        } 
        else if (cmd=='p')
        {
            //TODO port servo hardware PWM using lgpio
        } 
        else if (cmd=='q')
        {
            return 0;
        } 
        else
        {
            printf("Invalid command");
        }  // end of if/else
    }while(1);  // end of loop
    return(1);
}  // end of main

/** Example usage of led2472g etchsketch
 * @version CENG153, serial: 1a2b3c4d
 * @author Raspberry Pi Foundation
 * @author Leon King
 * @author Kris Medri
 * @author Modifier's Name
 * @since 2024-01-03
 * @param void
 * @return void
 */
int led2472g(void){
    struct fb_t *fb;
    fb=ShInit(fb);

    //ShWipeScreen(0,fb); //same as below
    memset(fb, 0, 128); //ShWipeScreen() is unnecessary, remove in the future

    //memset(fb, MAGENTA, 128); //MAGENTA seems to be light blue, not the same as for a pixel
    //memset(fb, 0, 128);

    //ShLightPixel(4,4,MAGENTA,fb); //MAGENTA color is correct, same as below
    //fb->pixel[4][4] = MAGENTA; //ShLightPixel() is unnecessary, remove in the future

    usleep (300000);

    //Set a test pixel pattern
    fb->pixel[0][5]=BLUE;
    fb->pixel[1][5]=GREEN;
    fb->pixel[2][5]=RED;
    fb->pixel[3][5]=YELLOW;
    fb->pixel[4][5]=MAGENTA;
    fb->pixel[5][5]=CYAN;
    fb->pixel[6][5]=WHITE;
    usleep (300000); // to allow pixels to be set
    ShRotatePattern(90,fb);
    usleep (300000);

    //Simple drawing program reminiscent of an Etch A Sketch
    struct brush_t brush;
    brush.colourindex=0;
    brush.colours[0]=RED;
    brush.colours[1]=GREEN;
    brush.colours[2]=BLUE;
    brush.colours[3]=YELLOW;
    brush.colours[4]=MAGENTA;
    brush.colours[5]=CYAN;
    brush.colours[6]=WHITE;
    brush.colours[7]=BLACK;
    brush.apple.x = 4;
    brush.apple.y = 4;
    struct pollfd evpoll = {
        .events = POLLIN,
    };

    //printf("Quit by holding down Ctrl and typing a c\n");
    //while(1){
    //    while (poll(&evpoll, 1, 0) > 0){
    //        move_events(evpoll.fd, &brush);
    //    }
    //    fb->pixel[brush.apple.x][brush.apple.y]=brush.colours[brush.colourindex];
    //    usleep(30000);
    //}

    return EXIT_FAILURE;
}

/** Example usage of led2472g snake
 * @version CENG153, serial: 1a2b3c4d
 * @author Kris Medri
 * @author Modifier's Name
 * @since 2024-01-03
 * @param void
 * @return int
 */
int game(void){
    // TODO
}

/** Example usage of hts221
 * @version CENG153, serial: 1a2b3c4d
 * @author Kris Medri
 * @author Modifier's Name
 * @since 2024-01-03
 * @param void
 * @return void
 */
void hts221(void){
    printf("Temp (from hts221) = %.1f°C\n", ShGetTemperatureAlt()); //From humidity sensor
    printf("Humidity (from hts221) = %.0f%% rH\n", ShGetHumidity());
    return;
}

/** Example usage of lps25h
 * @version CENG153, serial: 1a2b3c4d
 * @author Kris Medri
 * @author Modifier's Name
 * @since 2024-01-03
 * @param void
 * @return void
 */
void lps25h(void){
    printf("Temp (from lps25h) = %.2f°C\n", ShGetTemperature()); //From pressure sensor
    printf("Pressure (from lps25h) = %.0f hPa\n", ShGetPressure());
    return;
}

/** Example usage of lsm9ds1
 * @version CENG153, serial: 1a2b3c4d
 * @author Kris Medri
 * @author Modifier's Name
 * @since 2025-08-25
 * @param void
 * @return void
 */
void lsm9ds1(void)
{
    //TODO
    printf("magnetometer = %.2f\n", ShGetMG()); 
    printf("accelerometer x = %.2f \n", ShGetAccelX());
    printf("accelerometer y = %.2f \n", ShGetAccelY());
    printf("accelerometer z = %.2f \n", ShGetAccelZ());
	return;
}

/** Example usage of tcs3400
 * @version CENG153, serial: 1a2b3c4d
 * @author Kris Medri
 * @author Modifier's Name
 * @since 2024-03-12
 * @param void
 * @return void
 */
void tcs3400(void)
{
    struct colour readings=ShGetColour();
    printf("(Red,Green,Blue)=(%5u,%5u,%5u)\n",readings.red,readings.green,readings.blue); 
	return;
}

/** Based on shtest.py
 * @author Paul Moggach
 * @author Kris Medri
 * @since 2024-02-16
 * C code Demonstration of Astro Pi Sense Hat.
 */
int shtest(void) 
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

