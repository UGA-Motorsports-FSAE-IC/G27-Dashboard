/*
 * display.h
 *
 * LVGL display driver for the 480x320 FMC LCD, plus loading the
 * LVGL Editor UI (Dashboard_LVGL_UI/ui, screen1).
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

/* Reset + init the LCD, start LVGL, build the UI and show screen1.
 * Call once after the peripherals (FMC, DMA2D) are initialized. */
void displayInit(void);

/* Let LVGL redraw whatever changed. Call every main-loop iteration. */
void displayTask(void);

#endif /* DISPLAY_H_ */
