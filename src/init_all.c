#include "my.h"

void init_window(all_t *s_all)
{
    s_all->s_window.size = (sfVector2f){1920, 1080};
    sfVideoMode mode = {s_all->s_window.size.x, s_all->s_window.size.y, 32};
    s_all->s_window.window = sfRenderWindow_create(mode, "Perlin Noise", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(s_all->s_window.window, 60);
}

void init_camera(all_t *s_all)
{
    s_all->s_camera.camera = sfView_copy(sfRenderWindow_getView(s_all->s_window.window));
    s_all->s_camera.position.x = 0;
    s_all->s_camera.position.y = 0;
}

void init_perlin(all_t *s_all)
{
    s_all->s_perlin.seed = rand();
    s_all->s_perlin.index = 0;
    s_all->s_perlin.depth = 5;
    s_all->s_perlin.freq = 0.010;
}

void init_cell_list(all_t *s_all, int cell_size)
{
    s_all->s_cell_head = malloc(sizeof(cell_head_t));
    s_all->s_cell_head->cell_size = (sfVector2f){cell_size, cell_size};
    s_all->s_cell_head->width = s_all->s_window.size.x / s_all->s_cell_head->cell_size.x;
    s_all->s_cell_head->height = s_all->s_window.size.y / s_all->s_cell_head->cell_size.y;
    s_all->s_cell_head->length = 0;
    for (; s_all->s_perlin.index < s_all->s_cell_head->width; s_all->s_perlin.index++)
        cell_push_back(s_all);
}

void init_keys(all_t *s_all)
{
    s_all->s_keys.left = 0;
    s_all->s_keys.right = 0;
}

all_t *init_all(int cell_size)
{
    all_t *s_all = malloc(sizeof(all_t));
    srand(time(NULL));
    init_window(s_all);
    init_camera(s_all);
    init_perlin(s_all);
    init_cell_list(s_all, cell_size);
    init_keys(s_all);
    return (s_all);
}