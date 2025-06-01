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
#include "GLCD.h"
#include "KBD.h"
#include "photoGallery.h"
//#include "game.c"

#define __FI        1                      /* Font index 16x24               */
#define MENU_OPTIONS 3

// Menu items
const char *menu_items[MENU_OPTIONS] = {
    "  1. Photo Gallery", 
    "  2. MP3 Player", 
    "  3. Game"
};
int disp_val = 0;  // Current selection in the menu

// Function prototypes
void displayMenu(int selected);
void handleSelection(void);
void navigateMenu(void);
int MP3(void);       // Placeholder for MP3 player function
int game(void);      // Placeholder for game function

/*----------------------------------------------------------------------------
  Display Menu Function
 *----------------------------------------------------------------------------*/
void displayMenu(int selected) {
	
		int i;
	
    // Display header
    GLCD_SetBackColor(White);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(0, 0, __FI, "--------------------");
				GLCD_DisplayString(1, 0, __FI, "   Welcome to the   ");
				GLCD_DisplayString(2, 0, __FI, "    Media Center!   ");
				GLCD_DisplayString(3, 0, __FI, "--------------------");
				GLCD_SetTextColor(DarkGrey);
				GLCD_DisplayString(8, 0, __FI, "--------------------");
				GLCD_DisplayString(9, 0, __FI, "           by: Maria");


    
    // Display menu items
    for (i = 0; i < MENU_OPTIONS; i++) {
        if (i == selected) {
            GLCD_SetBackColor(Blue);
            GLCD_SetTextColor(White);
        } else {
            GLCD_SetBackColor(White);
            GLCD_SetTextColor(Black);
        }
        GLCD_DisplayString(5 + i, 0, __FI, (unsigned char*)menu_items[i]);
    }
}

/*----------------------------------------------------------------------------
  Handle Selection Function
 *----------------------------------------------------------------------------*/
void handleSelection(void) {
    GLCD_Clear(White);
    switch (disp_val) {
        case 0:
            photoGallery(); // Call to photo function
            break;
        case 1:
            MP3(); // Call to MP3 function
            break;
        case 2:
            game(); // Call to game function
            break;
    }
}

/*----------------------------------------------------------------------------
  Navigate Menu Function
 *----------------------------------------------------------------------------*/
void navigateMenu(void) {
    int KBD_but = get_button();

    switch (KBD_but) {
        case KBD_SELECT:
            handleSelection();
            break;
        case KBD_UP:
            disp_val = (disp_val > 0) ? disp_val - 1 : MENU_OPTIONS - 1;
            displayMenu(disp_val);
            break;
        case KBD_DOWN:
            disp_val = (disp_val < MENU_OPTIONS - 1) ? disp_val + 1 : 0;
            displayMenu(disp_val);
            break;
    }
}

/*----------------------------------------------------------------------------
  Main Functionality
 *----------------------------------------------------------------------------*/
int mainFunctionality(void) {
    KBD_Init();
    GLCD_Init();
    GLCD_Clear(White);
    displayMenu(disp_val);  // Display initial menu

    while (1) {
        navigateMenu();
    }
}


/*----------------------------------------------------------------------------
  Placeholder Functions
 *----------------------------------------------------------------------------*/

/*
int photo(void) {
    // Placeholder for photo gallery functionality
    //GLCD_DisplayString(0, 0, __FI, "   Photo Gallery   ");
		photoGallery();
    return 0;
}
*/

//int MP3(void) {
    // Placeholder for MP3 player functionality
  //  GLCD_DisplayString(0, 0, __FI, "     MP3 Player    ");
    // Add your MP3 player implementation here
 //   return 0;
//}

/*
int game(void) {
    // Placeholder for game functionality
    GLCD_DisplayString(0, 0, __FI, "       Game        ");
    // Add your game implementation here
    return 0;
}
*/

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main(void) {
    mainFunctionality();
}
