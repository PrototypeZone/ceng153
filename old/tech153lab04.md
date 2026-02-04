# TECH 153 Lab 04

- [ ] Demonstrate the execution of the program to your professor. ___/2

## 1. Implement steps discussed in class
Create the makefile as per class for compass.c and download the updated led2472g.h, led2472g.c, font.h   
Update the serial in the block comment to your actual serial number.   

## 2. Update compass.c
in GhDisplayHeader add   
```
fprintf(stdout,"Unit: %LX\n",ShGetSerial());
```
in main add   
```
    uint16_t logo[8][8];
    struct fb_t *fb;
    fb=ShInit(fb);
    memset(fb, 0, 128);
    usleep (300000);
```
change the main while loop from `while(1){` to `for(int i =0; i<=60;i++){`
and add
```
        ShConvertIntegerToPattern(i,logo,WHITE,BLACK);
        ShViewPattern(logo,fb);
```
after the loop add
```
    memset(fb, 0, 128);
    usleep (300000);
```
and change `FAILURE` to `SUCCESS` then run your code and show your professor.   
## 3. Magnetic compass   
Continue to create a program for providing the readings from the lsm9ds1 digital magnetic compass.   


