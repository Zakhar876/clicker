#include "../include/keyboard.h"
#include <Windows.h>

void pressKey(WORD key) {
    keybd_event(key, 0, 0, 0); // Press the key
}

void releaseKey(WORD key) {
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0); // Release the key
}

void sendKeyCombination(WORD key1, WORD key2) {
    pressKey(key1);
    pressKey(key2);
    releaseKey(key2);
    releaseKey(key1);
}
