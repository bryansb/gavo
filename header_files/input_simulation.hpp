#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
    #define OS_Windows 0
#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or 64 bit Windows systems */
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