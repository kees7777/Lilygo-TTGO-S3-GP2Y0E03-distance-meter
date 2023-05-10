#ifndef GP2Y0E03_h
#define GP2Y0E03_h
#include "Arduino.h"

// base adres = 0x80 W / 0x81 R = 8 bit. > 7 bit = 0x40  / adres kan geprogrameerd dd worden.

class GP2Y0E03
{
    public:
        GP2Y0E03( int addr );
        float get_length();
    private:
        int I2C_ADDR;
        float distance;
};

#endif

