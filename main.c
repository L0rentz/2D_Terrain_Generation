#include "my.h"

all_t *init_all(void)
{
    all_t *s_all = malloc(sizeof(all_t));
    sfVideoMode mode = {1920, 1080, 32};
    s_all->window = sfRenderWindow_create(mode, "Perlin Noise", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(s_all->window, 60);
    srand(time(NULL));
    init_map(s_all);
    s_all->s_keys.left = 0;
    s_all->s_keys.right = 0;
    return (s_all);
}

void free_all(all_t *s_all)
{
    free_cells_array(s_all);
    sfRenderWindow_destroy(s_all->window);
    free(s_all);
    s_all = NULL;
}

int main(void)
{
    all_t *s_all = init_all();

    while (sfRenderWindow_isOpen(s_all->window)) {
        poll_event(s_all);
        map_scrolling(s_all);
        draw_scene(s_all);
    }
    free_all(s_all);
    return (0);
}