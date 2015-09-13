#include <stdio.h>

struct position {
    int x,y,z;
};

struct snake {
    struct snake_piece *head, *tail;
};

struct snake_piece {
    struct snake_piece *next, *prev;
    size_t x,y,z;
};


int snake_is_valid_move(struct snake *s, struct position d)
{
    int result = 1;
    struct snake_piece *current;
    int x_pos = s->head.x + d.x;
    int y_pos = s->head.y + d.y;
    int z_pos = s->head.z + d.z;

    for (current = s->head; current != s->tail ;current = current->next) {
        if (current->x == x_pos &&
                current->y == y_pos &&
                current->z == z_pos) {
            return 0;
        }
    }

    return x_pos < 0 || x_pos >= 5 ||
        y_pos < 0 || y_pos >= 5 ||
        z_pos < 0 || z_pos >= 5;
}

void snake_add_tail()
{
    malloc(sizeof(struct snake_piece));
}


struct snake *snake_move(struct snake *s, struct position d)
{
    /* assume valid move */
    struct snake_piece *temp;
    int x_pos = s->head.x + d.x;
    int y_pos = s->head.y + d.y;
    int z_pos = s->head.z + d.z;

    s->tail.x = x_pos;
    s->tail.y = y_pos;
    s->tail.z = z_pos;

    if (s->head != s->tail) {
        temp = s->head;
        s->head = s->tail;
        s->head->next = temp;
        s->tail->prev->next = NULL;
        s->tail = s->tail->prev;
        s->head->prev = NULL;
    }
}

#ifndef SNAKE_TEST
int main()
{

    enum state s = INITIAL_STATE;
    while(1) {
    switch(s) {
        case INITIAL_STATE:
        break;
        case CHECK_FOR_INPUT:
        break;
        case CALCULATE_PATH:
        break;
        case REDRAW:
        for () {
        }
        break;
    }
}
#else
int main()
{
    struct snake s;

    s.head = s.tail = malloc(sizeof(snake_piece));




    
}
#endif
