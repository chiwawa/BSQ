NAME	= 	bsq

SRC	=	main.c \
		map.c	\
		internals/get_next_line.c

CFLAGS +=	-I./internals -ggdb

LDFLAGS +=	-ggdb

OBJ	=	$(SRC:.c=.o)


all: $(NAME)


$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all