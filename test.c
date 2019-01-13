#include "libft/includes/libft.h"

int		main()
{
	char *s;
	char **test;
	int	i;

	s = "md5 ";
	i = ft_count_words(s, ' ');
	ft_printf("i=%d\n", i);
	return (0);
}