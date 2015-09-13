
#include <stdio.h>
#include <stdlib.h>

#define LED_CUBE_SIZE 5
#define LED_CUBED_SIZE 125

int cube[LED_CUBE_SIZE][LED_CUBE_SIZE][LED_CUBE_SIZE];

struct LED LEDs[LED_CUBED_SIZE];

int compare_LED(const void *a, const void *b) {
    return ((struct LED) a)->p.y - ((struct LED) b)->p.y;
}

enum state {
    INITIAL_STATE,
    DRAW,
    GAME_LOGIC,
    CHECK_FOR_INPUT,
    WIN,
    LOSE,
};

struct position {
    int x, y, z;
};

struct LED {
    struct position p;
}

int position_equals(struct position a, struct position b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

void initialize_game()
{
    for (int i = 0; i <= LED_CUBE_SIZE; i++) {
        for (int j = 0; j <= LED_CUBE_SIZE; j++) {
            for (int k = 0; k <= LED_CUBE_SIZE; k++) {
                cube[i][j][k] = 0;
                LEDs[i + LED_CUBE_SIZE * j + LED_CUBE_SIZE * LED_CUBE_SIZE * k] = 0;
            }
        }
    }
}

void draw() {
    
}

int main()
{
    enum state game_state = INITIAL_STATE;

    while(1) {
        switch(game_state) {
            case INITIAL_STATE:
                initialize_game();
                game_state = DRAW;
                break;
            case DRAW:
                draw();
                // game_state = CHECK_FOR_INPUT;
                break;
            case CHECK_FOR_INPUT:
                game_state = GAME_LOGIC;
                break;
            case GAME_LOGIC:
                game_state = DRAW;
                break;
            case WIN:
            case LOSE:
                game_state = INITIAL_STATE;
                break;
        }
    }
    return 0;
}
