#include <stdio.h>
#include "libft/includes/libft.h"

int main()
{
	char str[1] = "";
	char **str2;

	str2 = ft_strsplit(str, ' ');
	printf("%s\n", str2[0]);
	return 0;
}