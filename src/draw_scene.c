#include "my.h"

void draw_cells(all_t *s_all)
{
    cell_node_t *tmp = s_all->s_cell_head->head;
    for (; tmp != NULL; tmp = tmp->next) {
        for (int y = 0; y < s_all->s_cell_head->height; y++) {
            if (tmp->s_cells[y].alive == 1)
                sfRenderWindow_drawRectangleShape(s_all->s_window.window, tmp->s_cells[y].rectangle, NULL);
        }
    }
}

void draw_scene(all_t *s_all)
{
    sfRenderWindow_clear(s_all->s_window.window, sfBlack);
    draw_cells(s_all);
    sfRenderWindow_display(s_all->s_window.window);
}