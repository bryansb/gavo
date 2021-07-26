#include "../../../../../header_files/input_simulation.hpp"

// Windows Code
#ifdef OS_Windows 
InputSimulation::InputSimulation() {
    
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.dwFlags = 0;
}

bool InputSimulation::sendInput(int keyCode){
    try {
        ip.ki.dwFlags = 0;
        ip.ki.wVk = keyCode;
        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    } catch (...) {
        cout << "[INFO] Error sending key " << keyCode << endl;
        return false;
    }
    return true;
}

#endif

// Linux Code
#ifndef OS_Windows

#endif