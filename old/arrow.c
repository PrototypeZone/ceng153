/** @brief Example of sense-hat usage
 *  @file arrow.c
 *  @since 2026-01-21
 *
 *  compile by typing gcc arrow.c led2472g.c lsm9ds1.c -li2c -o arrow
 *             
 *  run by typing ./arrow
 */

#include <stdbool.h>
#include "arrow.h"
#include "led2472g.h"
#include "lsm9ds1.h"

void ShConvertIntegerToPattern(int a, uint16_t image[8][8], uint16_t colorText, uint16_t colorBackground);

/** Development of digital compass
 * @author Kris Medri
 * @since 2026-01-21
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
    sprintf(str,"Compass");
    ShViewMessage(str,100,WHITE,BLACK,fb);
    usleep (300000);
    int angles[]={401,402,355,1,75,135,45,2,0,90,180,315,270,404};
    for (int i =0; i<sizeof(angles);i++){
        ShConvertIntegerToPattern(angles[i],logo,WHITE,BLACK);
        ShViewPattern(logo,fb);
        usleep (300000);
    }
    memset(fb, 0, 128);
    usleep (300000);

    return EXIT_SUCCESS;
}

/** @brief Converts an integer to an LED matrix pattern.
 */
void ShConvertIntegerToPattern(int a, uint16_t image[8][8], uint16_t colorText, uint16_t colorBackground)
{
    int i=0;
    int j,k;
    int tailleTableDeConvertion=sizeof(arrow)/sizeof(Tarrow);

    // Recherche si le caractere existe dans la table de convertion (cf font.h)
    while(a!=arrow[i].angle && i < tailleTableDeConvertion )
	i++;

    // Si le caractere est dans la table on le converti
    if(i < tailleTableDeConvertion)
    {
        for (j=0;j<8;j++)
        {
            for(k=0;k<8;k++)
            {
                if(arrow[i].binarypattern[j][k]) { image[j][k]=colorText; }
                else { image[j][k]=colorBackground; }
            }
        }
    }
    else // caractère inexistant on le remplace par un glyphe inconnu
    {
        ShConvertIntegerToPattern(404,image,colorText,colorBackground);
    }
}
