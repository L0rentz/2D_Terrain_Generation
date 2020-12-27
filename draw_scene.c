#include "my.h"

void draw_cells(all_t *s_all)
{
    for (int i = 0; i < s_all->s_map.height; i++) {
        for (int j = 0; j < s_all->s_map.width; j++) {
            if (s_all->s_map.s_cells[i][j].alive == 1)
                sfRenderWindow_drawRectangleShape(s_all->window, s_all->s_map.s_cells[i][j].rectangle, NULL);
        }
    }
}

void draw_scene(all_t *s_all)
{
    sfRenderWindow_clear(s_all->window, sfBlack);
    draw_cells(s_all);
    sfRenderWindow_display(s_all->window);
}