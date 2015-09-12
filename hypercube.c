#include <stdio.h>
#include <assert.h>
#include <wiringPi.h>
#include "internals.h"

int register_cube[7][18]; /* soft copy used for reading before writing to the register */
int led_cube[5][5][5]; /* soft copy used for the game */


void write_led(int led_value /* to write */, int x, int y, int z)
{
    /* when we write to led we must:
    - compute the register index then 
    - map onto register cube
    - write in LED cube
    - write block of register cube to shift register (if needed)
    */

    int linearized = x + 5 * y + 25 * z;
    assert(x < 5 && y < 5 && z < 5);
    struct pair p = map_to_register_cube_index(linearized);

    led_cube[x][y][z] = led_value;

    if (led_value != register_cube[p.a][p.b]) {
        write_shift_register(linearized);
    }
}

enum state {
    STATE_INITIALIZE=0,

};

void init()
{
    int x,y,z;
    digitalWrite(lat, HIGH);
    /*
    for (x=0;x<5;x++) for (y=0;y<5;y++) for (z=0;z<5;z++)
        write_led(0, x,y,z);
    */

    for (x=0;x<5;x++) for (y=0;y<5;y++) for (z=0;z<5;z++)
        write_led(1, x,y,z);

}

int main()
{
asld
    enum state s = STATE_INITIALIZE;
    while (1)
    {
        switch (s)
        {
            case STATE_INITIALIZE:
            init();

            return 0;
            break;
        }
    }
}


