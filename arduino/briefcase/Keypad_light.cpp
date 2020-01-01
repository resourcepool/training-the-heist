/*
||
|| @file Keypad.cpp
|| @version 3.1
|| @author Mark Stanley, Alexander Brevig
|| @contact mstanley@technologist.com, alexanderbrevig@gmail.com
||
|| @description
|| | This library provides a simple interface for using matrix
|| | keypads. It supports multiple keypresses while maintaining
|| | backwards compatibility with the old single key library.
|| | It also supports user selectable pins and definable keymaps.
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/
#include "Keypad_light.h"

// <<constructor>> Allows custom keymap, pin configuration, and keypad sizes.
Keypad_light::Keypad_light(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols) {
    rowPins = row;
    columnPins = col;
    sizeKpd.rows = numRows;
    sizeKpd.columns = numCols;

    begin(userKeymap);

//	setDebounceTime(0);
//	setHoldTime(500);
//	keypadEventListener = 0;

//	startTime = 0;
//	single_key = false;
}

// Let the user define a keymap - assume the same row/column count as defined in constructor
void Keypad_light::begin(char *userKeymap) {
    keymap = userKeymap;
}

// Returns a single key only. Retained for backwards compatibility.
char Keypad_light::getKey() {
//	single_key = true;

//    if (getKeys() && key[0].stateChanged && (key[0].kstate == PRESSED))
//        return key[0].kchar;
    return scanKeys();
//	single_key = false;

//    return NO_KEY;
}


// Private : Hardware scan
char Keypad_light::scanKeys() {
    // Re-intialize the row pins. Allows sharing these pins with other hardware.
    for (byte r = 0; r < sizeKpd.rows; r++) {
        pin_mode(rowPins[r], INPUT_PULLUP);
    }
    char keyPressed = NO_KEY;
    // bitMap stores ALL the keys that are being pressed.
    for (byte c = 0; c < sizeKpd.columns; c++) {
        pin_mode(columnPins[c], OUTPUT);
        pin_write(columnPins[c], LOW);    // Begin column pulse output.
        for (byte r = 0; r < sizeKpd.rows; r++) {
            delay(1);
            if (!pin_read(rowPins[r])) {
                keyPressed = keymap[r * sizeKpd.columns + c];
                break;
            }
//			bitWrite(bitMap[r], c, !pin_read(rowPins[r]));  // keypress is active low so invert to high.
        }
        // Set pin to high impedance input. Effectively ends column pulse.
        pin_write(columnPins[c], HIGH);
//		pin_mode(columnPins[c],INPUT);
//		IL FAUT TESTER EN COMMENTANT LA LIGNE AU DESSUS. PARCE QUE JE ME BASE SUR LA VALEUR DE LA COLONNE. SI ELLE EST EN INPUT... FUCKED UP.
    }
    return keyPressed;
}
