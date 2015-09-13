#include <wiringPi.h>
#include <stdio.h>
#include "internals.h"

#define DEBUG 1
#define debug_delay(I) if(DEBUG) { delay(250); }

void write_register_led_or_brightness(unsigned int n, unsigned int is_brightness);
void write_shift_register(unsigned int n);
void write_brightness_register(unsigned int n);


int sin = 21, sclk = 22, lat = 23, blank = 24;
int pins[10] = [21, 22, 23, 24, 25, 1, 4, 5, 6, 26];

void init_pins()
{
    pinMode(sin, OUTPUT);
    pinMode(sclk, OUTPUT);
    pinMode(lat, OUTPUT);
    pinMode(blank, OUTPUT);

    digitalWrite(sin, LOW);
    digitalWrite(sclk, LOW);
    digitalWrite(lat, LOW);
    digitalWrite(blank, LOW);
}

void write_shift_register(unsigned int n)
{
    digitalWrite(blank, HIGH);
    write_register_led_or_brightness(n, 0);
    digitalWrite(blank, LOW);
}

void write_brightness_register(unsigned int n)
{
    write_register_led_or_brightness(n, 1);
}

void write_register_led_or_brightness(unsigned int n, unsigned int is_brightness)
{
    int i;
    printf("%x\n", n);
    n = n  & ~(is_brightness << 24);
    //n = n | (is_brightness << 24);
    /* The shift register is only 24 bits long. */

    printf("%x\n", n);
    for (i = 0; i < 25; i++) {

        digitalWrite(sin, n & 1);

        printf("%d\n", n & 1);

        digitalWrite(sclk, LOW);
        debug_delay(500);
        digitalWrite(sclk, HIGH); /* shift register gets value */
        debug_delay(500);
        n = n >> 1; /* dont need to mask out signed bit */
    }

    debug_delay(500); // make this not debug
}

struct pair map_to_register_cube_index_old(size_t i)
{
    size_t led_index;
    struct pair result;
    result.a = i / 18; /* 18: number of usable bits in a shift register */
    
    led_index = i % 18;
    if (led_index <= 15) { /* last bit that is correct before disabled bits */
        result.b = 23 - led_index;
    } else if (led_index == 16) { /* begin special case handling */
        result.b = 4;
    } else {
        result.b = 0;
    }
    return result;
}

struct pair map_to_register_cube_index(size_t i)
{
    struct pair result;
    result.a = i / 18; /* 18: number of usable bits in a shift register */
    i = i % 18;
    if (i >= 3 && i <= 4)
        i += 1;
    else if (i >= 5 && i <= 6)
        i += 2;
    else if (i >= 7 && i <= 11)
        i += 3;
    else if (i >= 12 && i <= 13)
        i += 4;
    else if (i >= 14 && i <= 15)
        i += 5;
    else if (i >= 16 && i <= 17)
        i += 6;
    result.b = i;
    return result;
}


#ifdef TEST_PINS 
int main (void)
{
    wiringPiSetup ();
    init_pins();
    write_brightness_register(0x7F);
    printf("brightness done\n");
    digitalWrite(lat, LOW);
    write_shift_register(0xFFFFFF);
    digitalWrite(lat, HIGH);
    debug_delay(500);
    return 0;
}
#endif
