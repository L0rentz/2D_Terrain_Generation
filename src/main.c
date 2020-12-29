#include "my.h"

int main(int ac, char **av)
{
    int cell_size = error_check(ac, av);
    if (cell_size == -1)
        return (84);
    all_t *s_all = init_all(cell_size);

    while (sfRenderWindow_isOpen(s_all->s_window.window)) {
        poll_event(s_all);
        map_scrolling(s_all);
        draw_scene(s_all);
    }
    free_all(s_all);
    return (0);
}