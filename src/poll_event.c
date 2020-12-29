#include "my.h"

void poll_event(all_t *s_all)
{
    while (sfRenderWindow_pollEvent(s_all->s_window.window, &s_all->s_window.event)) {
        if (s_all->s_window.event.type == sfEvtClosed)
            sfRenderWindow_close(s_all->s_window.window);
        if (s_all->s_window.event.type == sfEvtKeyPressed) {
            if (s_all->s_window.event.key.code == sfKeyRight)
                s_all->s_keys.right = 1;
            if (s_all->s_window.event.key.code == sfKeyLeft)
                s_all->s_keys.left = 1;
        }
        if (s_all->s_window.event.type == sfEvtKeyReleased) {
            if (s_all->s_window.event.key.code == sfKeyRight)
                s_all->s_keys.right = 0;
            if (s_all->s_window.event.key.code == sfKeyLeft)
                s_all->s_keys.left = 0;
        }
    }
}