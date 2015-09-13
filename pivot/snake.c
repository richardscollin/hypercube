
#include <stdio.h>
#include <stdlib.h>

struct snake s;
struct position apple;

#define LED_CUBE_SIZE 5
#define LED_CUBED_SIZE 125

int cube[LED_CUBE_SIZE][LED_CUBE_SIZE][LED_CUBE_SIZE];

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

struct snake {
    struct snake_piece *head, *tail;
    int size;
};

struct snake_piece {
    struct snake_piece *next, *prev;
    struct position p;
};

int position_equals(struct position a, struct position b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

int validate_move(struct snake *s, struct position d)
{
    struct snake_piece *current;
    int new_x = s->head->p.x + d.x;
    int new_y = s->head->p.y + d.y;
    int new_z = s->head->p.z + d.z;
    struct position new_position = { new_x, new_y, new_z };

    for (current = s->head; current != s->tail; current = current->next) {
        if (position_equals(current->p, new_position))
            return 0;
    }

    return new_x < 0 || new_x >= LED_CUBE_SIZE ||
        new_y < 0 || new_y >= LED_CUBE_SIZE ||
        new_z < 0 || new_z >= LED_CUBE_SIZE;
}

void snake_add_head(struct snake *s)
{
    struct snake_piece *head = malloc(sizeof(struct snake_piece));
    s->head->prev = head;
    s->head = head;
    s->head->prev = NULL;
    s->size++;
}

void snake_move(struct snake *s, struct position d)
{
    /* assume valid move */
    struct snake_piece *temp;
    int new_x = s->head->p.x + d.x;
    int new_y = s->head->p.y + d.y;
    int new_z = s->head->p.z + d.z;

    s->tail->p.x = new_x;
    s->tail->p.y = new_y;
    s->tail->p.z = new_z;

    if (s->head != s->tail) {
        temp = s->head;
        s->head = s->tail;
        s->head->next = temp;
        s->tail->prev->next = NULL;
        s->tail = s->tail->prev;
        s->head->prev = NULL;
    }
}

// check if player is size of board - win condition
void spawn_apple(struct snake *s)
{
    struct snake_piece *sp;

    while (1) {
        int x = rand() % 5, y = rand() % 5, z = rand() % 5;
        int collision = 0;
        struct position new_position = { x, y, z };
        for (sp = s->head; sp != NULL; sp = sp->next) {
            if (position_equals(sp->p, new_position)) {
                collision = 1;
                break;
            }
        }
        if (!collision) {
            apple = new_position;
        }
    }
}

void initialize_game()
{
    s.head = s.tail = malloc(sizeof(struct snake_piece));
    s.head->p.x = s.head->p.y = s.head->p.x = 2;
    s.size = 1;

    for (int i = 0; i <= LED_CUBE_SIZE; i++) {
        for (int j = 0; j <= LED_CUBE_SIZE; j++) {
            for (int k = 0; k <= LED_CUBE_SIZE; k++) {
                cube[i][j][k] = 0;
            }
        }
    }
}

struct position get_direction()
{
    struct position p = {1, 0, 0};
    return p;
}

int main()
{
    enum state game_state = INITIAL_STATE;
    struct position direction;

    while(1) {
        switch(game_state) {
            case INITIAL_STATE:
                initialize_game();
                game_state = DRAW;
                break;
            case DRAW:
                //TODO
                game_state = CHECK_FOR_INPUT;
                break;
            case CHECK_FOR_INPUT:
                direction = get_direction();
                //TODO
                game_state = GAME_LOGIC;
                break;
            case GAME_LOGIC:
                if (s.size == LED_CUBED_SIZE) {
                    game_state = WIN;
                    break;
                }

                if (position_equals(s.head->p, apple)) {
                    snake_add_head(&s);
                    spawn_apple(&s);
                }

                if (validate_move(&s, direction)) {
                    snake_move(&s, direction);
                } else {
                    game_state = LOSE;
                }

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
