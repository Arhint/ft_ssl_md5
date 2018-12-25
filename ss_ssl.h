#ifndef SS_SSL_H
# define SS_SSL_H

#include "libft/includes/libft.h"
#include <stdio.h>
#include <math.h>
# include <stdint.h>

typedef			struct	s_md5
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	size_t				blocks;
}						t_md5;

void					ft_md5(unsigned char *res_bits, size_t len);
int						ft_left_rotate(uint32_t f, uint32_t s);
uint32_t		*ft_from_8_to_16(unsigned char * str, int len);

void	print_bits_32(int octet);
void	print_bits(unsigned char octet);

#endif
