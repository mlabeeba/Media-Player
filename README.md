# 🎮 Media Center on MCB1700 – COE718 Final Project

This project is a **menu-driven multimedia system** implemented on the **LPC1768 (MCB1700)** embedded development board using **C and Keil uVision IDE**. Built as a final project for the *Embedded Systems Design* course (COE718), it combines software and hardware to simulate a fully functional **Media Center** with:

* 🖼️ Photo Gallery
* 🎵 MP3 Music Player
* 🎮 2048-Inspired Game

---

## Features Overview

| Feature           | Description                                                             |
| ------------------| ----------------------------------------------------------------------- |
| **Photo Gallery** | View images using the joystick to navigate through a gallery of Pokémon |
| **MP3 Player**    | Stream USB audio from a PC and control volume via potentiometer         |
| **Game - 2048**   | A playable version of the 2048 puzzle where the win condition is 32     |

---

## Hardware & Tools

* **MCB1700 Board** with LPC1768 (ARM Cortex-M3)
* **Onboard LCD screen** for display
* **Joystick** for user input
* **Potentiometer** for volume control
* **USB Audio Streaming**
* **Keil uVision IDE** for development

---

## Navigation

The Media Center uses a **main menu interface** with joystick control:

* ⬆️ / ⬇️ to navigate through menu options
* ⬅️ / ➡️ to scroll images or move tiles
* Select to confirm or return

Each module is implemented in a separate `.c` file for modularity.

---

## System Modules

### Photo Gallery

* Navigate between Bulbasaur, Eevee, and Piplup images
* PNGs were converted to `.c` files using GIMP and displayed using `GLCD_Bitmap()`

### MP3 Player

* Streams audio from PC via USB
* Volume controlled by onboard potentiometer
* Real-time volume display as hex value

### Game (2048 Variant)

* Win condition: Reach tile **32**
* 4x4 grid with joystick controls
* Randomized tile placement and merging logic
* Display updated after every move with GLCD visuals

---

## Experimental Results

Each module was tested independently:

* Photo gallery supports smooth navigation through bitmap images
* MP3 player streams real-time audio with interactive volume changes
* Game logic supports merges, movement, win-checks, and UI redraws

---

## Design Highlights

* Modular C structure (`main menu`, `photoGallery.c`, `usbdMain.c`, `game.c`)
* Peripheral integration: LCD, Joystick, Potentiometer, USB Audio
* Joystick-controlled menu loop with switch-case logic
* Efficient bitmap handling for LCD display

---

## 📂 File Structure

```
├── Blinky.c             # Main menu logic
├── photoGallery.c       # Image viewer logic
├── usbdMain.c           # MP3 player logic
├── game.c               # 2048-style game logic
├── *.c                  # Image bitmap files (e.g., bulbasaur.c, eevee.c)
└── Maria Labeeba COE718 Final Project Report.pdf  # Full documentation
```

---

## 📄 Full Report

For detailed diagrams, flowcharts, implementation notes, and code appendices, see:

📄 [`Maria Labeeba COE718 Final Project Report.pdf`](./Maria%20Labeeba%20COE718%20Final%20Project%20Report.pdf)

---
