/**
 * @file screen1_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "screen1_gen.h"
#include "../ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * screen1_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t card;
    static lv_style_t title;
    static lv_style_t value;
    static lv_style_t unit;
    static lv_style_t bar_bg;
    static lv_style_t bar_fill;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&card);
        lv_style_init(&title);
        lv_style_init(&value);
        lv_style_init(&unit);
        lv_style_init(&bar_bg);
        lv_style_init(&bar_fill);

        lv_style_set_bg_color(&card, lv_color_hex(0x0A0A0A));
        lv_style_set_border_width(&card, 2);
        lv_style_set_radius(&card, 8);
        lv_style_set_pad_all(&card, 0);
        lv_style_set_text_color(&title, lv_color_hex(0xAAAAAA));
        lv_style_set_text_font(&title, body_sm);
        lv_style_set_text_color(&value, lv_color_hex(0xFFFFFF));
        lv_style_set_text_font(&value, title_large);
        lv_style_set_text_color(&unit, lv_color_hex(0x888888));
        lv_style_set_text_font(&unit, body_sm);
        lv_style_set_bg_color(&bar_bg, lv_color_hex(0x222222));
        lv_style_set_bg_opa(&bar_bg, 255);
        lv_style_set_bg_color(&bar_fill, lv_color_hex(0x00FF66));
        lv_style_set_bg_opa(&bar_fill, 255);

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if UI_CHECK_COMPILE_TARGET(UI_TARGET_ALL)
    if (ui_check_target(UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
        lv_obj_set_name_static(lv_obj_0, "screen1_#");
        lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x000000), 0);
        lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
        lv_obj_set_scrollable(lv_obj_0, false);

        lv_obj_t * rpm_bar = lv_bar_create(lv_obj_0);
        lv_obj_set_name(rpm_bar, "rpm_bar");
        lv_obj_set_x(rpm_bar, 6);
        lv_obj_set_y(rpm_bar, 4);
        lv_obj_set_width(rpm_bar, 468);
        lv_obj_set_height(rpm_bar, 12);
        lv_bar_set_min_value(rpm_bar, 0);
        lv_bar_set_max_value(rpm_bar, 10500);
        lv_bar_set_value(rpm_bar, 0, false);
        lv_obj_set_style_radius(rpm_bar, 6, 0);
        lv_bar_bind_value(rpm_bar, subject_rpm_value);
        lv_obj_add_style(rpm_bar, &bar_bg, LV_PART_MAIN);
        lv_obj_add_style(rpm_bar, &bar_fill, LV_PART_INDICATOR);

        lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_1, 6);
        lv_obj_set_y(lv_obj_1, 22);
        lv_obj_set_width(lv_obj_1, 142);
        lv_obj_set_height(lv_obj_1, 94);
        lv_obj_set_scrollable(lv_obj_1, false);
        lv_obj_set_style_border_color(lv_obj_1, lv_color_hex(0x00B4FF), 0);
        lv_obj_add_style(lv_obj_1, &card, 0);
        lv_obj_t * lv_label_0 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_0, "COOLANT");
        lv_obj_set_align(lv_label_0, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_0, 6);
        lv_obj_add_style(lv_label_0, &title, 0);

        lv_obj_t * coolant_val = lv_label_create(lv_obj_1);
        lv_obj_set_name(coolant_val, "coolant_val");
        lv_label_set_text(coolant_val, "82");
        lv_label_bind_text(coolant_val, subject_coolant, NULL);
        lv_obj_set_align(coolant_val, LV_ALIGN_CENTER);
        lv_obj_add_style(coolant_val, &value, 0);

        lv_obj_t * lv_label_1 = lv_label_create(lv_obj_1);
        lv_label_set_text(lv_label_1, "°C");
        lv_obj_set_align(lv_label_1, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_y(lv_label_1, -6);
        lv_obj_add_style(lv_label_1, &unit, 0);

        lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_2, 6);
        lv_obj_set_y(lv_obj_2, 124);
        lv_obj_set_width(lv_obj_2, 142);
        lv_obj_set_height(lv_obj_2, 94);
        lv_obj_set_scrollable(lv_obj_2, false);
        lv_obj_set_style_border_color(lv_obj_2, lv_color_hex(0xFFA000), 0);
        lv_obj_add_style(lv_obj_2, &card, 0);
        lv_obj_t * lv_label_2 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_2, "OIL PRESSURE");
        lv_obj_set_align(lv_label_2, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_2, 6);
        lv_obj_add_style(lv_label_2, &title, 0);

        lv_obj_t * oil_press_val = lv_label_create(lv_obj_2);
        lv_obj_set_name(oil_press_val, "oil_press_val");
        lv_label_set_text(oil_press_val, "4.2");
        lv_label_bind_text(oil_press_val, subject_oil_press, NULL);
        lv_obj_set_align(oil_press_val, LV_ALIGN_CENTER);
        lv_obj_add_style(oil_press_val, &value, 0);

        lv_obj_t * lv_label_3 = lv_label_create(lv_obj_2);
        lv_label_set_text(lv_label_3, "bar");
        lv_obj_set_align(lv_label_3, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_y(lv_label_3, -6);
        lv_obj_add_style(lv_label_3, &unit, 0);

        lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_3, 154);
        lv_obj_set_y(lv_obj_3, 22);
        lv_obj_set_width(lv_obj_3, 172);
        lv_obj_set_height(lv_obj_3, 196);
        lv_obj_set_scrollable(lv_obj_3, false);
        lv_obj_set_style_border_color(lv_obj_3, lv_color_hex(0xFFFFFF), 0);
        lv_obj_add_style(lv_obj_3, &card, 0);
        lv_obj_t * lv_label_4 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_4, "RPM");
        lv_obj_set_align(lv_label_4, LV_ALIGN_TOP_LEFT);
        lv_obj_set_x(lv_label_4, 8);
        lv_obj_set_y(lv_label_4, 6);
        lv_obj_add_style(lv_label_4, &title, 0);

        lv_obj_t * rpm_val = lv_label_create(lv_obj_3);
        lv_obj_set_name(rpm_val, "rpm_val");
        lv_label_bind_text(rpm_val, subject_rpm, NULL);
        lv_obj_set_align(rpm_val, LV_ALIGN_TOP_LEFT);
        lv_obj_set_x(rpm_val, 8);
        lv_obj_set_y(rpm_val, 22);
        lv_obj_set_style_text_color(rpm_val, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_font(rpm_val, body_lg, 0);

        lv_obj_t * lv_label_5 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_5, "SPEED");
        lv_obj_set_align(lv_label_5, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_x(lv_label_5, -8);
        lv_obj_set_y(lv_label_5, 6);
        lv_obj_add_style(lv_label_5, &title, 0);

        lv_obj_t * speed_val = lv_label_create(lv_obj_3);
        lv_obj_set_name(speed_val, "speed_val");
        lv_label_bind_text(speed_val, subject_speed, NULL);
        lv_obj_set_align(speed_val, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_x(speed_val, -8);
        lv_obj_set_y(speed_val, 22);
        lv_obj_set_style_text_color(speed_val, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_font(speed_val, body_lg, 0);

        lv_obj_t * gear_val = lv_label_create(lv_obj_3);
        lv_obj_set_name(gear_val, "gear_val");
        lv_label_bind_text(gear_val, subject_gear, NULL);
        lv_obj_set_align(gear_val, LV_ALIGN_CENTER);
        lv_obj_set_y(gear_val, 12);
        lv_obj_set_style_text_color(gear_val, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_font(gear_val, body_lg, 0);
        lv_obj_set_style_transform_scale_x(gear_val, 512, 0);
        lv_obj_set_style_transform_scale_y(gear_val, 512, 0);

        lv_obj_t * lv_label_6 = lv_label_create(lv_obj_3);
        lv_label_set_text(lv_label_6, "GEAR");
        lv_obj_set_align(lv_label_6, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_y(lv_label_6, -6);
        lv_obj_add_style(lv_label_6, &unit, 0);

        lv_obj_t * lv_obj_4 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_4, 332);
        lv_obj_set_y(lv_obj_4, 22);
        lv_obj_set_width(lv_obj_4, 142);
        lv_obj_set_height(lv_obj_4, 94);
        lv_obj_set_scrollable(lv_obj_4, false);
        lv_obj_set_style_border_color(lv_obj_4, lv_color_hex(0xFFE000), 0);
        lv_obj_add_style(lv_obj_4, &card, 0);
        lv_obj_t * lv_label_7 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_7, "BATTERY");
        lv_obj_set_align(lv_label_7, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_7, 6);
        lv_obj_add_style(lv_label_7, &title, 0);

        lv_obj_t * battery_val = lv_label_create(lv_obj_4);
        lv_obj_set_name(battery_val, "battery_val");
        lv_label_set_text(battery_val, "13.8");
        lv_label_bind_text(battery_val, subject_battery, NULL);
        lv_obj_set_align(battery_val, LV_ALIGN_CENTER);
        lv_obj_add_style(battery_val, &value, 0);

        lv_obj_t * lv_label_8 = lv_label_create(lv_obj_4);
        lv_label_set_text(lv_label_8, "V");
        lv_obj_set_align(lv_label_8, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_y(lv_label_8, -6);
        lv_obj_add_style(lv_label_8, &unit, 0);

        lv_obj_t * lv_obj_5 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_5, 332);
        lv_obj_set_y(lv_obj_5, 124);
        lv_obj_set_width(lv_obj_5, 142);
        lv_obj_set_height(lv_obj_5, 94);
        lv_obj_set_scrollable(lv_obj_5, false);
        lv_obj_set_style_border_color(lv_obj_5, lv_color_hex(0xFF2020), 0);
        lv_obj_add_style(lv_obj_5, &card, 0);
        lv_obj_t * lv_label_9 = lv_label_create(lv_obj_5);
        lv_label_set_text(lv_label_9, "AIR TANK");
        lv_obj_set_align(lv_label_9, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_9, 6);
        lv_obj_add_style(lv_label_9, &title, 0);

        lv_obj_t * air_tank_val = lv_label_create(lv_obj_5);
        lv_obj_set_name(air_tank_val, "air_tank_val");
        lv_label_set_text(air_tank_val, "8.0");
        lv_label_bind_text(air_tank_val, subject_air_tank, NULL);
        lv_obj_set_align(air_tank_val, LV_ALIGN_CENTER);
        lv_obj_add_style(air_tank_val, &value, 0);

        lv_obj_t * lv_label_10 = lv_label_create(lv_obj_5);
        lv_label_set_text(lv_label_10, "bar");
        lv_obj_set_align(lv_label_10, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_y(lv_label_10, -6);
        lv_obj_add_style(lv_label_10, &unit, 0);

        lv_obj_t * lv_obj_6 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_6, 6);
        lv_obj_set_y(lv_obj_6, 226);
        lv_obj_set_width(lv_obj_6, 112);
        lv_obj_set_height(lv_obj_6, 88);
        lv_obj_set_scrollable(lv_obj_6, false);
        lv_obj_set_style_border_color(lv_obj_6, lv_color_hex(0xFF40C0), 0);
        lv_obj_add_style(lv_obj_6, &card, 0);
        lv_obj_t * lv_label_11 = lv_label_create(lv_obj_6);
        lv_label_set_text(lv_label_11, "AUX 1");
        lv_obj_set_align(lv_label_11, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_11, 6);
        lv_obj_add_style(lv_label_11, &title, 0);

        lv_obj_t * aux1_val = lv_label_create(lv_obj_6);
        lv_obj_set_name(aux1_val, "aux1_val");
        lv_label_set_text(aux1_val, "--");
        lv_obj_set_align(aux1_val, LV_ALIGN_CENTER);
        lv_obj_set_y(aux1_val, 8);
        lv_obj_add_style(aux1_val, &value, 0);

        lv_obj_t * lv_obj_7 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_7, 124);
        lv_obj_set_y(lv_obj_7, 226);
        lv_obj_set_width(lv_obj_7, 112);
        lv_obj_set_height(lv_obj_7, 88);
        lv_obj_set_scrollable(lv_obj_7, false);
        lv_obj_set_style_border_color(lv_obj_7, lv_color_hex(0x00FFC0), 0);
        lv_obj_add_style(lv_obj_7, &card, 0);
        lv_obj_t * lv_label_12 = lv_label_create(lv_obj_7);
        lv_label_set_text(lv_label_12, "AUX 2");
        lv_obj_set_align(lv_label_12, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_12, 6);
        lv_obj_add_style(lv_label_12, &title, 0);

        lv_obj_t * aux2_val = lv_label_create(lv_obj_7);
        lv_obj_set_name(aux2_val, "aux2_val");
        lv_label_set_text(aux2_val, "--");
        lv_obj_set_align(aux2_val, LV_ALIGN_CENTER);
        lv_obj_set_y(aux2_val, 8);
        lv_obj_add_style(aux2_val, &value, 0);

        lv_obj_t * lv_obj_8 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_8, 242);
        lv_obj_set_y(lv_obj_8, 226);
        lv_obj_set_width(lv_obj_8, 112);
        lv_obj_set_height(lv_obj_8, 88);
        lv_obj_set_scrollable(lv_obj_8, false);
        lv_obj_set_style_border_color(lv_obj_8, lv_color_hex(0x4060FF), 0);
        lv_obj_add_style(lv_obj_8, &card, 0);
        lv_obj_t * lv_label_13 = lv_label_create(lv_obj_8);
        lv_label_set_text(lv_label_13, "AUX 3");
        lv_obj_set_align(lv_label_13, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_13, 6);
        lv_obj_add_style(lv_label_13, &title, 0);

        lv_obj_t * aux3_val = lv_label_create(lv_obj_8);
        lv_obj_set_name(aux3_val, "aux3_val");
        lv_label_set_text(aux3_val, "--");
        lv_obj_set_align(aux3_val, LV_ALIGN_CENTER);
        lv_obj_set_y(aux3_val, 8);
        lv_obj_add_style(aux3_val, &value, 0);

        lv_obj_t * lv_obj_9 = lv_obj_create(lv_obj_0);
        lv_obj_set_x(lv_obj_9, 360);
        lv_obj_set_y(lv_obj_9, 226);
        lv_obj_set_width(lv_obj_9, 112);
        lv_obj_set_height(lv_obj_9, 88);
        lv_obj_set_scrollable(lv_obj_9, false);
        lv_obj_set_style_border_color(lv_obj_9, lv_color_hex(0x80FF00), 0);
        lv_obj_add_style(lv_obj_9, &card, 0);
        lv_obj_t * lv_label_14 = lv_label_create(lv_obj_9);
        lv_label_set_text(lv_label_14, "AUX 4");
        lv_obj_set_align(lv_label_14, LV_ALIGN_TOP_MID);
        lv_obj_set_y(lv_label_14, 6);
        lv_obj_add_style(lv_label_14, &title, 0);

        lv_obj_t * aux4_val = lv_label_create(lv_obj_9);
        lv_obj_set_name(aux4_val, "aux4_val");
        lv_label_set_text(aux4_val, "--");
        lv_obj_set_align(aux4_val, LV_ALIGN_CENTER);
        lv_obj_set_y(aux4_val, 8);
        lv_obj_add_style(aux4_val, &value, 0);

        the_root = lv_obj_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

