NAME	=	PerlinNoise

SRCS	=	src/main.c \
			src/perlin.c \
			src/poll_event.c \
			src/draw_scene.c \
			src/map_scrolling.c \
			src/init_all.c \
			src/cell_list_utils.c \
			src/error_check.c \
			src/cave_generation.c \
			src/free_all.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -g -Og
CFLAGS	+=	-I./includes
CFLAGS	+=	-l csfml-system
CFLAGS	+=	-l csfml-graphics
CFLAGS	+=	-l csfml-audio
CFLAGS	+=	-l csfml-window
CFLAGS  +=	-lm


all:	$(NAME)

$(NAME):	$(OBJS) $(SRCS)
		gcc -o $(NAME) $(OBJS) $(CFLAGS)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re: fclean all
