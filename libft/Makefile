NAME = libft.a

FLG = -Wall -Wextra -Werror -I./includes

SRC = 	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c  ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c \
		ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c \
		ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
		ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
		ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
		ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
		ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
		ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
		ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
		ft_strtrim.c ft_tolower.c ft_toupper.c ft_swap.c ft_blanks.c \
		ft_count_words.c ft_len_int.c ft_sqrt.c ft_maxint.c ft_error.c \
		get_next_line.c \
		ft_printf/ft_atoll.c ft_printf/ft_create_flg.c \
		ft_printf/ft_doflagxo.c ft_printf/ft_itoa_base.c \
		ft_printf/ft_print_c.c ft_printf/ft_print_flags.c \
		ft_printf/ft_print_o.c ft_printf/ft_print_p.c \
		ft_printf/ft_print_s.c ft_printf/ft_print_u.c \
		ft_printf/ft_print_x.c ft_printf/ft_printf.c \
		ft_printf/ft_printhelp_s.c ft_printf/ft_print_di.c

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[0;32mCreate libft.a\033[0m"

%.o: %.c
	@gcc -c $(FLG) -o $@ $<

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[0;31mdelete:" $(NAME) "\033[0m"

re: fclean all
