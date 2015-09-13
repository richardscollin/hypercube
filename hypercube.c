#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include "internals.h"

int register_cube[7][18]; /* soft copy used for reading before writing to the register */
int led_cube[5][5][5]; /* soft copy used for the game */
int player[1];

struct position {
    int x;
    int y;
    int z;
}


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
    MAIN,
};

void init_board()
{
    int x,y,z;
    memset(register_cube, 0, sizeof(register_cube));
    write_led(0, 0,0,0);
    /* only flushes one block if unitialized fix */
}

int main()
{
    enum state s = STATE_INITIALIZE;
    while (1)
    {
        switch (s)
        {
            case STATE_INITIALIZE:
            init_board();
            s = MAIN;
            break;

            case MAIN:

            update_LED();

            if () {
            }


        }
    }
}


