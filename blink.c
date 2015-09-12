#include <wiringPi.h>
#include <stdio.h>

#define DEBUG
void init_pins();
void write_shift_register(unsigned int n);
struct pair map_to_cube_index(size_t i);

struct pair {
    size_t a;
    size_t b;
};


int sin = 21, sclk = 22, lat = 23, blank = 24;

int main (void)
{
    struct pair p0, p1 = { 3, 10 };
    p0 = map_to_cube_index(2+3*5+2*25);
    if (p0.a == p1.a && p0.b == p1.b) {
        printf("correct");
    } else {
        printf("incorrect");
    }
    
#if 0
    wiringPiSetup ();
    init_pins();
    write_shift_register(0xFFF0FFFF);
    digitalWrite(lat, LOW);
#ifdef DEBUG
        delay(500);
#endif
    digitalWrite(lat, HIGH);
    init_pins();
    return 0 ;
#endif
}

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
    int i;
    n = n & (0x1000000 - 1);
    /* The shift register is only 24 bits long. */

    for (i = 0; i < 24; i++) {

        digitalWrite(sin, n & 1);
        digitalWrite(sclk, LOW);
        delay(500);
        digitalWrite(sclk, HIGH); /* shift register gets value */
#ifdef DEBUG
        printf("%d\n", (n & 1) );
        delay(500);
#endif
        n = n >> 1; /* dont need to mask out signed bit */
    }
}

struct pair map_to_cube_index(size_t i)
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


