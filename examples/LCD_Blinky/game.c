#include <LPC17xx.H>
#include "GLCD.h"
#include "KBD.h"
#include <stdlib.h>

// Bitmap Files
#include "2.c"
#include "4.c"
#include "8.c"
#include "16.c"
#include "32.c"
// Include other bitmaps (e.g., 8.c, 16.c, etc.)

#define GRID_SIZE 4      // Size of the 2048 grid (4x4)
#define CELL_SIZE 50     // Size of each cell on the LCD
#define DEBOUNCE_DELAY 200 // Debounce delay for joystick inputs
unsigned char* bitmap;
int board[GRID_SIZE][GRID_SIZE]; // Game board

// Timer Initialization for Random Seed
void initTimer() {
    LPC_SC->PCONP |= (1 << 1); // Power on Timer 0
    LPC_TIM0->TCR = 0x02;      // Reset Timer
    LPC_TIM0->TCR = 0x01;      // Enable Timer
}

void seedRandom() {
    srand(LPC_TIM0->TC); // Use Timer 0's counter as a seed
}

// Utility Functions
int randomRange(int min, int max) {
    return (rand() % (max - min + 1)) + min; // Random number between min and max
}

void delay(int ms) {
    int count = ms * 12000; // Approximate delay for LPC17xx at 12 MHz clock
    while (count--) {
        __NOP();
    }
}

int debounceJoystick() {
    int stableInput = get_button();
    delay(DEBOUNCE_DELAY);
    if (stableInput == get_button()) {
        return stableInput;
    }
    return 0; // No stable input
}

// Function to Get Bitmap for a Number
unsigned char* getBitmapForValue(int value) {
    switch (value) {
        case 2: 
						bitmap=(unsigned char*)TWO_pixel_data;
						break;
        case 4: 
						bitmap=(unsigned char*)FOUR_pixel_data;
						break;
				case 8: 
						bitmap=(unsigned char*)EIGHT_pixel_data;
						break;
				case 16: 
						bitmap=(unsigned char*)SIXTEEN_pixel_data;
						break;
				case 32: 
						bitmap=(unsigned char*)THIRTYTWO_pixel_data;
						break;
        default: return NULL; // No bitmap for empty tiles
    }
}


// Function to Display Startup Message
void displayStartupMessage() {
    GLCD_Clear(White);
    GLCD_SetBackColor(White);
    GLCD_SetTextColor(Blue);
    GLCD_DisplayString(2, 2, 1, (unsigned char *)"Welcome to 2048!");
    GLCD_DisplayString(4, 2, 1, (unsigned char *)"To win, reach 32.");
    GLCD_DisplayString(6, 0, 1, (unsigned char *)"Use joystick to play");
    delay(7000); // Wait for 3 seconds
}

// Function to Display Win Message
void displayWinMessage() {
    GLCD_Clear(White);
    GLCD_SetBackColor(White);
    GLCD_SetTextColor(Blue);
    GLCD_DisplayString(4, 4, 1, (unsigned char *)"You Win!");
    GLCD_DisplayString(6, 2, 1, (unsigned char *)"Back to Menu!");
    delay(5000); // Wait for 3 seconds
}


// Game Board Initialization
void addRandomTile() {
    int emptyCells = 0;
    int emptyPositions[GRID_SIZE * GRID_SIZE][2];
    int i, j, randomIndex, row, col;

    // Collect empty positions
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == 0) {
                emptyPositions[emptyCells][0] = i;
                emptyPositions[emptyCells][1] = j;
                emptyCells++;
            }
        }
    }

    if (emptyCells == 0) return; // No empty cells

    // Select a random empty position
    randomIndex = randomRange(0, emptyCells - 1);
    row = emptyPositions[randomIndex][0];
    col = emptyPositions[randomIndex][1];

    // Place a 2 (90%) or 4 (10%)
    board[row][col] = (randomRange(0, 9) < 9) ? 2 : 4;
}

void initBoard() {
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            board[i][j] = 0; // Set all cells to 0
        }
    }
    // Add two initial tiles
    addRandomTile();
    addRandomTile();
}

void GLCD_FillRect(int x, int y, int width, int height) {
	int i,j;
    for (i = x; i < x + width; i++) {
        for (j = y; j < y + height; j++) {
            GLCD_PutPixel(i, j); // Draw a pixel at (i, j)
        }
    }
}


// Display the Game Board
void displayBoard() {
    int i, j;
    GLCD_Clear(White); // Clear the entire screen

    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            int x = j * CELL_SIZE + 20; // X position of tile
            int y = i * CELL_SIZE + 20; // Y position of tile

            // Draw tile background
            GLCD_SetTextColor(White);
            GLCD_FillRect(x, y, CELL_SIZE, CELL_SIZE); // Draw tile background

            // Get bitmap for the tile value
            bitmap = getBitmapForValue(board[i][j]);

            // Draw bitmap if it exists
            if (bitmap != NULL) {
                GLCD_Bitmap(x, y, CELL_SIZE, CELL_SIZE, bitmap);
            }

            // Draw border around tile
            GLCD_SetTextColor(Black);
            GLCD_FillRect(x, y, CELL_SIZE, 1);               // Top border
            GLCD_FillRect(x, y + CELL_SIZE - 1, CELL_SIZE, 1); // Bottom border
            GLCD_FillRect(x, y, 1, CELL_SIZE);               // Left border
            GLCD_FillRect(x + CELL_SIZE - 1, y, 1, CELL_SIZE); // Right border
        }
    }
}

int slideLeft() {
    int moved = 0;
		int i,j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 1; j < GRID_SIZE; j++) {
            if (board[i][j] != 0) {
                int k = j;
                while (k > 0 && board[i][k - 1] == 0) {
                    board[i][k - 1] = board[i][k];
                    board[i][k] = 0;
                    k--;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

int slideRight() {
    int moved = 0;
		int i,j; 
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = GRID_SIZE - 2; j >= 0; j--) {
            if (board[i][j] != 0) {
                int k = j;
                while (k < GRID_SIZE - 1 && board[i][k + 1] == 0) {
                    board[i][k + 1] = board[i][k];
                    board[i][k] = 0;
                    k++;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

int slideUp() {
    int moved = 0;
		int j,i;
    for (j = 0; j < GRID_SIZE; j++) {
        for (i = 1; i < GRID_SIZE; i++) {
            if (board[i][j] != 0) {
                int k = i;
                while (k > 0 && board[k - 1][j] == 0) {
                    board[k - 1][j] = board[k][j];
                    board[k][j] = 0;
                    k--;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

int slideDown() {
    int moved = 0;
		int i,j;
    for (j = 0; j < GRID_SIZE; j++) {
        for (i = GRID_SIZE - 2; i >= 0; i--) {
            if (board[i][j] != 0) {
                int k = i;
                while (k < GRID_SIZE - 1 && board[k + 1][j] == 0) {
                    board[k + 1][j] = board[k][j];
                    board[k][j] = 0;
                    k++;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

void mergeLeft() {
	int i,j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE - 1; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
            }
        }
    }
}

void mergeRight() {
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = GRID_SIZE - 1; j > 0; j--) {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                board[i][j - 1] = 0;
            }
        }
    }
}

void mergeUp() {
    int i, j;
    for (j = 0; j < GRID_SIZE; j++) {
        for (i = 0; i < GRID_SIZE - 1; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                board[i + 1][j] = 0;
            }
        }
    }
}

void mergeDown() {
    int i, j;
    for (j = 0; j < GRID_SIZE; j++) {
        for (i = GRID_SIZE - 1; i > 0; i--) {
            if (board[i][j] != 0 && board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                board[i - 1][j] = 0;
            }
        }
    }
}

int checkWinCondition() {
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == 32) {
                return 1; // Win condition met
            }
        }
    }
    return 0; // No win condition met
}


// Game Loop
int game(void) {
    GLCD_Init();
    KBD_Init();
    initTimer();   // Initialize Timer 0
    seedRandom();  // Seed random number generator
		displayStartupMessage();
    initBoard();
    displayBoard();

    while (1) {
        int buttonPress = debounceJoystick();
        int moved = 0;
				
				if (buttonPress == KBD_SELECT) {
            NVIC_SystemReset(); // Reset the microcontroller
						return 0;
        }

        if (buttonPress == KBD_UP) {
            moved = slideUp();
            mergeUp();
            moved |= slideUp();
        } else if (buttonPress == KBD_DOWN) {
            moved = slideDown();
            mergeDown();
            moved |= slideDown();
        } else if (buttonPress == KBD_LEFT) {
            moved = slideLeft();
            mergeLeft();
            moved |= slideLeft();
        } else if (buttonPress == KBD_RIGHT) {
            moved = slideRight();
            mergeRight();
            moved |= slideRight();
        }

        if (moved) {
            addRandomTile();
            displayBoard();
        }
				
				if (checkWinCondition()) {
            displayWinMessage();
            NVIC_SystemReset();
            return 0;
        }

    }

    return 0;
}
