#include <wiringPi.h>
#include <unistd.h>

//int pins[] = { 21, 22, 23, 24, 25, 1, 4, 5, 6, 26 };
int pins[] = { 21, 22 };
int main()
{
    int i;
    wiringPiSetup ();
    for (i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
        pinMode(pins[i], OUTPUT);
    }

    for (i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
        digitalWrite(pins[i], LOW);
    }

    while (1) {
        for (i = 0; i < sizeof(pins) / sizeof(pins[0]); i++) {
            digitalWrite(pins[i], LOW);
            usleep(200);
            digitalWrite(pins[i], HIGH);
            usleep(800);
        }
    }
}
