#include "ss_ssl.h"

void	print_bits(unsigned char octet)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		octet & (1 << i) ? write(1, "1", 1) : write(1, "0", 1);
		i--;
	}
	write(1, "\n", 1);
}

void	print_bits_32(uint32_t octet)
{
	int i;

	i = 31;
	while (i >= 0)
	{
		octet & (1 << i) ? write(1, "1", 1) : write(1, "0", 1);
		i--;
	}
	write(1, "\n", 1);
}

void	new_gnl(int fd, char **line)
{
	ssize_t		ex;
	char		bif[2];
	char		*tmp;
	char		*str;

	str = ft_strdup("");
	while ((ex = read(fd, bif, 1)) > 0)
	{
		bif[ex] = '\0';
		tmp = str;
		str = ft_strjoin(str, bif);
		free(tmp);
	}
	*line = str;
}