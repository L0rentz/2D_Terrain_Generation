#include "my.h"

void scrolling_left(all_t *s_all)
{
    s_all->s_camera.position.x -= s_all->s_cell_head->cell_size.x;
    sfView_move(s_all->s_camera.camera, (sfVector2f){-s_all->s_cell_head->cell_size.x, 0});
    sfRenderWindow_setView(s_all->s_window.window, s_all->s_camera.camera);
    cell_pop_back(s_all);
    cell_push_front(s_all);
    s_all->s_perlin.index--;
    
}

void scrolling_right(all_t *s_all)
{
    s_all->s_camera.position.x += s_all->s_cell_head->cell_size.x;
    sfView_move(s_all->s_camera.camera, (sfVector2f){s_all->s_cell_head->cell_size.x, 0});
    sfRenderWindow_setView(s_all->s_window.window, s_all->s_camera.camera);
    cell_pop_front(s_all);
    cell_push_back(s_all);
    s_all->s_perlin.index++;
    
}

void map_scrolling(all_t *s_all)
{
    if (s_all->s_keys.left == 1 && s_all->s_keys.right == 0)
        scrolling_left(s_all);
    if (s_all->s_keys.left == 0 && s_all->s_keys.right == 1)
        scrolling_right(s_all);
}