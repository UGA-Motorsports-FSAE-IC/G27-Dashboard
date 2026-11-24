/* data.c
 *
 *  Created on: May 5, 2026
 *      Author: ____Ryan____ Main
 *
 *  Decodes CAN frames and pushes the values to:
 *    - the shift lights / warning LEDs
 *    - the LVGL dashboard (screen1) through its subjects
 *
 *  Subjects are defined in Dashboard_LVGL_UI/ui/globals.xml and
 *  declared in ui_gen.h. Setting a subject automatically updates every
 *  widget bound to it, and LVGL redraws on the next displayTask().
 */

#include "data.h"
#include "shiftLights.h"
#include "ui.h"          /* LVGL Editor UI: subject_rpm, subject_gear, ... */
#include <stdio.h>

extern uint8_t ledcolors[];
extern uint32_t ledbytes[];
extern TIM_HandleTypeDef htim2;
int G1[12] = {500, 3000, 4000, 5000, 6000, 7000, 8000, 8500, 9000, 9500, 10000, 10200};

uint16_t rpmVal;

/* Wheel speeds (FL FR RL RR). No widget on screen1 shows these yet;
 * add a string subject + bind_text in the Editor (e.g. an AUX slot)
 * and set it with lv_subject_set_string() below. */
static char ws[32] = "null";

void processCAN(int id, uint8_t *data) {

    switch (id) {
        case RPMCANID: {
            rpmVal = ((uint16_t)data[6] << 8) + data[7];
            UpdateShiftLights(&htim2, TIM_CHANNEL_1, ledcolors, ledbytes, rpmVal, G1);
            lv_subject_snprintf(subject_rpm, "%u", rpmVal);
            lv_subject_set_int(subject_rpm_value, rpmVal);   /* RPM bar */
            break;
        }

        case SPEEDCANID: {
            uint16_t speedVal = ((uint16_t)data[0] << 8) | data[1];
            speedVal /= 10;
            lv_subject_snprintf(subject_speed, "%u", speedVal);
            break;
        }

        case GEARCANID: {
            uint16_t gearVal = ((uint16_t)data[3] << 8) | data[2];
            int gearNum = calculateGear(gearVal);
            lv_subject_snprintf(subject_gear, "%d", gearNum);
            break;
        }

        case CLTCANID: {
            uint16_t tempVal = ((uint16_t)data[6] << 8) + data[7];
            tempVal /= 10;
            if (tempVal > 220) {
            	setColor(&htim2, TIM_CHANNEL_1, 0, 200, 0, ledcolors, ledbytes, 15);
            } else {
            	setColor(&htim2, TIM_CHANNEL_1, 0, 0, 0, ledcolors, ledbytes, 15);
            }
            lv_subject_snprintf(subject_coolant, "%u", tempVal);
            break;
        }

        case BATTERYCANID: {
            uint16_t battvalue = ((uint16_t)data[2] << 8) + data[3];
            /* value is in tenths of a volt -> "13.8" */
            lv_subject_snprintf(subject_battery, "%u.%u", battvalue / 10, battvalue % 10);
            break;
        }

        case AIRTANKCANID: {
        	uint16_t adc = ((uint16_t)data[5] << 8) + data[4];
        	float volts = adc * (5.0f / 4096.0f);
        	float airtankval = (volts * 1250.0f) - 625.0f;
        	lv_subject_snprintf(subject_air_tank, "%d", (int)airtankval);
        	break;
        }

        case BSPDCANID: {
        	uint16_t bspdvalue = ((uint16_t)data[5] << 8) + data[4];
            uint8_t pmbvalue = data[0];
        	if (bspdvalue < 2000 || pmbvalue == 0) {
        		setColor(&htim2, TIM_CHANNEL_1, 0, 0, 0, ledcolors, ledbytes, 0);
        		setColor(&htim2, TIM_CHANNEL_1, 0, 0, 0, ledcolors, ledbytes, 1);
        	} else {
        		setColor(&htim2, TIM_CHANNEL_1, 0, 255, 0, ledcolors, ledbytes, 0);
        		setColor(&htim2, TIM_CHANNEL_1, 0, 255, 0, ledcolors, ledbytes, 1);
        	}
            break;
        }

        case OILPRESSURECANID: {
			uint16_t oilpressureval = ((uint16_t)data[4] << 8) + data[5];
			oilpressureval /= 10;
			lv_subject_snprintf(subject_oil_press, "%u", oilpressureval);
			break;
		}

        case WSCANID: {
        	snprintf(ws, sizeof(ws), "%u %u %u %u", data[0], data[2], data[4], data[6]);
        	break;
        }
    }
}

int calculateGear(uint16_t gv) {
	if (gv > 385 && gv < 685) {
		return 1;
	} else if (gv >= 685 && gv < 1065) {
		return 7;
	} else if (gv >= 1065 && gv < 1335) {
		return 2;
	} else if (gv >= 1335 && gv < 2014) {
		return 3;
	} else if (gv >= 2014 && gv < 2466) {
		return 4;
	} else if (gv >= 2466 && gv < 3000) {
		return 5;
	} else if (gv >= 3000 && gv < 3689) {
		return 6;
	} else {
		return 8;
	}
}
