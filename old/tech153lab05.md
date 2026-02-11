# TECH 153 Lab 05

- [ ] Demonstrate the execution of the program to your professor. ___/2

## 1. Implement steps discussed in class
Download the updated `led2472g.h`, `led2472g.c`, `lsm9ds1.h`, `lsm9ds1.c`   
Add an `lsm9ds1.o:` recipe to your makefile and add it to the linking recipe along with `-lm`   
Add includes for `<math.h>` and `"lsm9ds1.h"` to `compass.h`  

## 2. Update compass.c
in main add   
```
    double x=0;
    double y=0;
    int angle=0;
```
in the main for loop add
```
        x=ShGetMagX();
        y=ShGetMagY();
        angle=atan2(y,x)*180/M_PI+180+270;//-180to+180,+180+270
```
modify:
```
        ShConvertIntegerToPattern(angle/6,logo,WHITE,BLACK);
```
then run your code and show your professor.   
## 3. Magnetic compass   
Continue to create a program for providing the readings from the lsm9ds1 digital magnetic compass.   


