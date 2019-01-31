NAME =	ft_ssl

FLG =	-Wall -Wextra -Werror

SRC =	main.c md5.c help_md5.c sha256.c help_sha256.c \
		sha512.c help_sha512.c ft_ssl_helper.c \
		sha384.c

OBJ =	$(SRC:.c=.o)

HEAD = -I./libft/includes/

all: $(NAME) lib

$(NAME):	$(OBJ) libft/libft.a
	@gcc $(FLG) $(OBJ) -L ./libft/ -lft -o $(NAME)
	@echo "\033[0;32mCreate ./"$(NAME) "\033[0m"
	@echo "\033[0;32mcompile done\033[0m"

%.o: %.c ft_ssl.h
	@gcc -c $(FLG) $(HEAD) -o $@ $<

libft/libft.a: lib

lib:
	@make -C ./libft/

clean:
	@make -C ./libft clean
	@/bin/rm -f $(OBJ)
	@echo "\033[0;31mdelete: all objects\033[0m"

fclean:	clean
	@make -C ./libft fclean
	@/bin/rm -f $(NAME)
	@echo "\033[0;31mdelete:" $(NAME) "\033[0m"

re:	fclean all