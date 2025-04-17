#pragma once

int current_button;


struct button {
    char* name;
    char* pos;
    int status;
};

/**
 * a button has been pressed
 */


button listen();

/**
 * which button pressed
 * return 1(correct button)or 0 (not) 
 * 
 * args: which one is correct (we can get this from the led sequencing
 * file, if no buttons are lit currently this is None)
 */


int verify_button();

/**
 * taking verify button's return and sending to the score handler
 * 
 */


void send_result();
