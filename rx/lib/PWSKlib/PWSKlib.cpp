#include "PWSKlib.h"

void PWSKlib::handle()
{
    unsigned long now = micros();
    if (digitalRead(pin))
    {
        last = now;
        return;
    }

    unsigned long width = now - last;   // Width of detected pulse
    unsigned long elapsed = now - sync; // Elapsed time since last sync pulse

    if (width < 530 && width > 470) // Sync pulse
    {
        b = 0;
        buff = 0;
        sync = now;
        return;
    }

    if (width < 100)
        return;

    width = elapsed - 500 - 1000 * b;

    if (inRange(elapsed)) // Bit is in timining range
    {
        if (width > 600)
            buff |= (1 << (7 - b)); // Is a 1
        if (b == 7)
        {
            b = 0;
            decoded[c] = buff;
            c = c == 0 ? 1 : 0;
            return;
        }
        b++;
        return;
    }

    // If bit is not in timing range, check for skipped bits

    int _b = int((elapsed - 500) / 1000); // Current bit by timing
    if (_b >= 7)
    {
        b = 0;
        decoded[c] = buff;
        c = c == 0 ? 1 : 0;
        return;
    }
    if (elapsed - 500 - 1000 * _b > 600)
        buff |= (1 << (7 - b)); // Last received bit is a 1
    b = _b;
}

bool PWSKlib::inRange(unsigned long elapsed)
{
    return elapsed > (500 + 1000 * (b)) && elapsed < (500 + 1000 * (b + 1));
}

String PWSKlib::get()
{
    String d = "";
    for (int i = 0; i < sizeof(decoded); i++)
    {
        d += decoded[i];
    }
    return d;
}

void PWSKlib::begin(unsigned int _pin, void (*callback)(void))
{
    if (pin != -1)
        end();
    pin = _pin;
    attachInterrupt(digitalPinToInterrupt(pin), callback, CHANGE);
}

void PWSKlib::end(void)
{
    detachInterrupt(digitalPinToInterrupt(pin));
    pin = -1;
}