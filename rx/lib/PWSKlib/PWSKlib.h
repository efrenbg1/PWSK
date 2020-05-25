#ifndef PWSKlib_H
#define PWSKlib_H

#include <Arduino.h>

class PWSKlib
{
    volatile unsigned long last, sync = 0;
    volatile int pin = -1;
    volatile unsigned int b, c = 0;
    volatile char buff;
    volatile char decoded[2];
    volatile bool off = false;

public:
    void begin(unsigned int, void (*callback)(void));
    void end(void);
    void handle(void);
    String get(void);

private:
    bool inRange(unsigned long);
};

#endif