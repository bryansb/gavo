#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

#ifdef __unix__
    #define OS_Windows 0
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
    #include <X11/extensions/XTest.h>
    #include <unistd.h>

    class InputSimulation {
        private:
            Display *display;
            
        public:
            InputSimulation();
            bool sendInput(int keyCode);
    };

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows 1
    #include <windows.h>

    class InputSimulation {
        
        private:
            INPUT ip;

        public:
            InputSimulation();
            bool sendInput(int keyCode);
    };

#endif