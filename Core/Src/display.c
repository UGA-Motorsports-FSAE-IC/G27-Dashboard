/*
 * display.c
 *
 * LVGL display driver for the 480x320 FMC LCD, plus loading the
 * LVGL Editor UI (Dashboard_LVGL_UI/ui, screen1).
 */

#include "display.h"
#include "main.h"
#include "lcd_io.h"
#include "rpiDisplayShapes.h"   /* modifySpace() */

#include "lvgl.h"
#include "ui.h"                 /* LVGL Editor UI: ui_init(), screen1_create(), subjects */

/* Full-screen RGB565 buffer, defined in rpiDisplaySceneBuilder.cpp.
 * LVGL renders into it, then the flush callback copies it to the LCD. */
extern uint16_t framebuffer[];

/*
 * Copy one rendered area to the LCD.
 *
 * PARTIAL render mode: px_map holds exactly this area's pixels, packed
 * row by row (w * h pixels), so it can go straight into the
 * LCD's memory-write command after setting the column/page window.
 */
static void lcdFlushCb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    uint32_t w = (uint32_t)lv_area_get_width(area);
    uint32_t h = (uint32_t)lv_area_get_height(area);

    modifySpace(area->x1, area->y1, area->x2, area->y2);
    commandAndData(WRITE_COMMAND, (uint16_t *)px_map, w * h);

    lv_display_flush_ready(disp);
}

void displayInit(void)
{
    /* LCD controller bring-up (reset, init sequence, clear, display on) */
    resetScreen();
    initializeScreen();

    /* LVGL core + millisecond tick source */
    lv_init();
    lv_tick_set_cb(HAL_GetTick);

    /* Display driver. The whole framebuffer is used as one PARTIAL
     * draw buffer, so LVGL can redraw any area in a single pass. */
    lv_display_t *display = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_color_format(display, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(display,
                           framebuffer, NULL,
                           SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint16_t),  /* size in BYTES */
                           LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, lcdFlushCb);

    /* Build the Editor UI (fonts, styles, subjects) and show the dashboard.
     * Asset path is empty: every font/image is compiled in. */
    ui_init("");
    lv_screen_load(screen1_create());
}

void displayTask(void)
{
    lv_timer_handler();
}
