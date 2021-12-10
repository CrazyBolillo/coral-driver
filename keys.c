#include "keys.h"

uint8_t read_click(void) {
    if (MODE_BTN == 0) {
        is_pushed(MODE_BTN, MODE_ONE_CLICK);
        // TODO: Detect double click
    }
    else if (UP_BTN == 0) {
        is_pushed(UP_BTN, UP_CLICK);
    }
    else if (DOWN_BTN == 0) {
        is_pushed(DOWN_BTN, DOWN_CLICK);
    }
    else if (POWER_BTN == 0) {
        is_pushed(POWER_BTN, POWER_CLICK);
    }
    else {
        return 0;
    }
}