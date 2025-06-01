/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "bulbasaur.c"
#include "eevee.c"
#include "piplup.c"
extern main(void);

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int photoGallery (void) {                      
  int currentButtonState = 0;
  int lastButtonState = -1;    
  int pic = 0;
	int KBD_but;
	unsigned char* images[] = {(unsigned char *)&bulbasaur_pixel_data,
														 (unsigned char *)&eevee_pixel_data,
														 (unsigned char *)&piplup_pixel_data
														};
	
	int totalImages = sizeof(images) / sizeof(images[0]); 

	KBD_Init();
  LED_Init ();
  GLCD_Init();

    for (;;) {
        currentButtonState = get_button(); 

        // Check if the button state has changed since the last loop iteration
        if (currentButtonState != lastButtonState) {
            switch (currentButtonState) {
                case KBD_RIGHT:
                    pic = (pic + 1) % totalImages;  // right, wrap around if necessary
                    break;
                case KBD_LEFT:
                    pic = (pic - 1 + totalImages) % totalImages;  // left, wrap around if necessary
                    break;
								case KBD_SELECT:
										GLCD_Clear (White);
										main();
										return 0;
										break;
            }

						if(currentButtonState == KBD_UP | currentButtonState == KBD_DOWN){
							
						} 
						else {
							switch (pic){
								case 0:
									GLCD_Clear(White);	//bulb
									GLCD_SetTextColor(Black);
									GLCD_DisplayString(9, 0, __FI, " <    bulbasaur   >");
									break;
								
								case 1:
									GLCD_Clear(White); //eve
									GLCD_SetTextColor(Black);
									GLCD_DisplayString(9, 0, __FI, " <     eevee      >");
								
									break;
								case 2:
									GLCD_Clear(White); //pip
									GLCD_SetTextColor(Black);
									GLCD_DisplayString(9, 0, __FI, " <     piplup     >");
									break;
						}
							
							GLCD_Bitmap(60, 30, 200, 160, images[pic]);
						
            lastButtonState = currentButtonState; 
        }
    }
}
		}
