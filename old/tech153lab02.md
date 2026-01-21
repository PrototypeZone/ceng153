# TECH 153 Lab 02

- [ ] Demonstrate the execution of the program to your professor. ___/2

## 1. Continue to work on the main part of compass.c on mikelake
```
/** @brief Digital compass display, with timestamped humitdity, pressure and temperature.
 *  @file compass.c
 *  @version ceng153, Serial: 1a2b3c4d  
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Constants
#define GHUPDATE 2000
#define SENSORS 3
#define TEMPERATURE 0
#define HUMIDITY 1
#define PRESSURE 2
#define HSH 0
#define BME280 0
#define HTS221 0
#define LPS25H 0
#define USHUMID 100
#define LSHUMID 0
#define USPRESS 1016
#define LSPRESS 975
#define USTEMP 50
#define LSTEMP -10
#if HSH
#define HSH_RTC_I2CADR 0x68
#define HSH_MCP23017_I2CADR 0x20
#define HSH_PCF8591_I2CADR 0x48
#define HSH_BME280_I2CADR 0x76
#define HSH_MCP23017_PINBASE 100
#define HSH_PCF8591_PINBASE 200
#define HSH_BME280_PINBASE 300
#define HSH_PCF8591_A01N 3 //analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A01N);
#define GEN00 0
#define GEN01 1
typedef enum {NOCOLOUR,RED,YELLOW,GREEN}ledcolour_e;
#define HEATERON 0 //RED digitalWrite(GEN00,HIGH);
#define HUMIDIFIERON 1 //GREEN digitalWrite(GEN01,HIGH);
#define GHCOFF 2
#endif

// Function Prototypes
void GhControllerInit(void);
void GhDisplayHeader(const char * sname);
void GhDisplayReadings(time_t rtime,float dreads[SENSORS]);
float GhGetHumidity(void);
float GhGetPressure(void);
void GhGetReadings(float readings[SENSORS]);
float GhGetTemperature(void);

/** @brief Defines the entry point for the console application.  
 * @author Your Name
 * @since 2026-01-21
 * @param void
 * @return exit status
 */
int main(void)  
{  
	time_t now;
	float creadings[SENSORS]={0.0};
	GhControllerInit();
	while(1){
		now = time(NULL);
		GhGetReadings(creadings);
		GhDisplayReadings(now,creadings);
		usleep(GHUPDATE*1000);
	}

	return EXIT_FAILURE;
}
```

## 2. Add the protoyped functions

```
void GhControllerInit(void){
	srand((unsigned) time(NULL));
	GhDisplayHeader("Your Name");
#if HSH
	wiringPiSetup();
	mcp23017Setup(HSH_MCP23017_PINBASE, HSH_MCP23017_I2CADR);
	pcf8591Setup(HSH_PCF8591_PINBASE, HSH_PCF8591_I2CADR);
	pinMode(HSH_MCP23017_PINBASE+HEATERON, OUTPUT);
	pinMode(HSH_MCP23017_PINBASE+HUMIDIFIERON, OUTPUT);
	pinMode(HSH_MCP23017_PINBASE+GHCOFF, INPUT);
	SetLED(GREEN);
#endif
#if BME280
	BME280Setup();
#endif
}

void GhDisplayHeader(const char * sname)
{
	fprintf(stdout, "%s's CENG153 Digital Compass\n",sname);
}

void GhDisplayReadings(time_t rtime,float dreads[SENSORS])
{
	fprintf(stdout,"%s Readings\tT: %5.1fC\tH: %5.1f%%\tP: %6.1fmb\n",ctime(&rtime),dreads[TEMPERATURE],dreads[HUMIDITY],dreads[PRESSURE]);
}

float GhGetHumidity(void)
{
#if BME280
	return GetBME280Humidity();
#elif HTS221
    return ShGetHumidity();
#else
	return (float) (rand() % (USHUMID - LSHUMID +1) + LSHUMID);
#endif
}

float GhGetPressure(void)
{
#if BME280
	return GetBME280Pressure();
#elif LPS25H
    return ShGetPressure();
#else
	return (float) (rand() % (USPRESS - LSPRESS + 1) +LSPRESS);
#endif
}

void GhGetReadings(float readings[SENSORS])
{
	readings[TEMPERATURE] = GhGetTemperature();
	readings[HUMIDITY] = GhGetHumidity();
	readings[PRESSURE] = GhGetPressure();
}

float GhGetTemperature(void)
{
#if BME280
	return GetBME280TempC();
#elif LPS25H
    return ShGetTemperature(); //From pressure sensor
#else
	return (float) (rand() % (USTEMP - LSTEMP + 1) + LSTEMP);
#endif
}

```

## 3. Magnetic compass
Continue to create a program for providing the readings from the lsm9ds1 digital magnetic compass.   


