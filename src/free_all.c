#include "my.h"

void free_cell_list(all_t *s_all)
{
    cell_node_t *tmp = s_all->s_cell_head->head;
    cell_node_t *to_free;
    while (tmp != NULL) {
        for (int y = 0; y < s_all->s_cell_head->height; y++)
            sfRectangleShape_destroy(tmp->s_cells[y].rectangle);
        free(tmp->s_cells);
        to_free = tmp;
        tmp = tmp->next;
        free(to_free);
    }
    free(s_all->s_cell_head);
}

void free_all(all_t *s_all)
{
    sfRenderWindow_destroy(s_all->s_window.window);
    sfView_destroy(s_all->s_camera.camera);
    free_cell_list(s_all);
    free(s_all);
    s_all = NULL;
}