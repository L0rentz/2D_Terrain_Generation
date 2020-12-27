#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Types.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/System/Vector2.h>

typedef struct s_cell {
    int alive;
    sfVector2f position;
    sfRectangleShape *rectangle;
} cell_t;

typedef struct s_map {
    int height;
    int width;
    sfVector2f cell_size;
    float *perlin_noise;
    double perlin_freq;
    int perlin_depth;
    int perlin_index;
    cell_t **s_cells;
} map_t;

typedef struct s_keys {
    int left;
    int right;
} keys_t;

typedef struct s_all {
    sfRenderWindow *window;
    sfEvent event;
    map_t s_map;
    keys_t s_keys;
    int seed;
} all_t;

double perlin2d(double x, double y, double freq, int depth, all_t *s_all);
void poll_event(all_t *s_all);
void draw_scene(all_t *s_all);
void map_scrolling(all_t *s_all);
void init_map(all_t *s_all);
void free_cells_array(all_t *s_all);