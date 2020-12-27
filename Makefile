NAME	=	PerlinNoise

SRCS	=	main.c \
			perlin.c \
			poll_event.c \
			draw_scene.c \
			map_scrolling.c \
			init_map.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -g -Og
CFLAGS	+=	-I./include
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
