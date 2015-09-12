
void init_pins();
void write_shift_register(unsigned int n);
struct pair map_to_register_cube_index(size_t i);

extern int sin, sclk, lat, blank;

struct pair {
    size_t a;
    size_t b;
};

