#include "../../../header_files/input_simulation.hpp"

// Windows Code
#if OS_Windows
InputSimulation::InputSimulation() {
    
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
}

bool InputSimulation::sendInput(int keyCode){
    try {
        
        ip.ki.dwFlags = 0;
        ip.ki.wVk = keyCode;
        SendInput(1, &ip, sizeof(INPUT));
        Sleep(15);
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        ip.ki.wVk = keyCode;
        SendInput(1, &ip, sizeof(INPUT));
        Sleep(15);
    } catch (...) {
        cout << "[INFO] Error sending key " << keyCode << endl;
        return false;
    }
    return true;
}

// Linux Code
#else 

InputSimulation::InputSimulation() {
    display = XOpenDisplay(NULL);
}

bool InputSimulation::sendInput(int keyCode){
    try {
        unsigned int keycode;
        keycode = XKeysymToKeycode(display, keyCode);
        XTestFakeKeyEvent(display, keycode, True, 15);
        XTestFakeKeyEvent(display, keycode, False, 15);
        XFlush(display);
        return true;
    } catch (...) {
        cout << "[INFO] Error sending key " << keyCode << endl;
        return false;
    }
}
#endif