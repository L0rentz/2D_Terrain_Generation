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

typedef struct s_cell_node {
    cell_t *s_cells;
    struct s_cell_node *next;
    struct s_cell_node *back;
} cell_node_t;

typedef struct s_cell_head {
    int height;
    int width;
    int length;
    sfVector2f cell_size;
    cell_node_t *head;
    cell_node_t *tail;
} cell_head_t;

typedef struct s_keys {
    int left;
    int right;
} keys_t;

typedef struct s_camera {
    sfView *camera;
    sfVector2f position;
} camera_t;

typedef struct s_perlin {
    double freq;
    int depth;
    int index;
    int seed;
} perlin_t;

typedef struct s_window {
    sfRenderWindow *window;
    sfEvent event;
    sfVector2f size;
} window_t;

typedef struct s_all {
    cell_head_t *s_cell_head;
    keys_t s_keys;
    camera_t s_camera;
    perlin_t s_perlin;
    window_t s_window;
} all_t;

double perlin2d(double x, double y, double freq, int depth, all_t *s_all);
void poll_event(all_t *s_all);
void draw_scene(all_t *s_all);
void map_scrolling(all_t *s_all);
void cell_push_back(all_t *s_all);
void cell_push_front(all_t *s_all);
void cell_pop_back(all_t *s_all);
void cell_pop_front(all_t *s_all);
all_t *init_all(int cell_size);
int error_check(int ac, char **av);
void free_all(all_t *s_all);