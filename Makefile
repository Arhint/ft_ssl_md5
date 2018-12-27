NAME =	ft_ssl

FLG =	-Wall -Wextra -Werror

SRC =	main.c md5.c help_md5.c

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	make -C ./libft/
	gcc $(FLG) $(OBJ) -L ./libft/ -lft -o $(NAME)

%.o: %.c
	gcc -c $(FLG) -o $@ $<

clean:
	make -C ./libft clean
	/bin/rm -f $(OBJ)

fclean:	clean
	make -C ./libft fclean
	/bin/rm -f $(NAME)

re:	fclean all