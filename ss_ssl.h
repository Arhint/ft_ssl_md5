#ifndef SS_SSL_H
# define SS_SSL_H

#include "libft/includes/libft.h"
#include <stdio.h>
#include <math.h>

typedef			struct	s_md5
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	size_t				blocks;
}						t_md5;

void					ft_md5(unsigned char *res_bits, size_t len);
int						ft_left_rotate(int f, int s);

#endif
