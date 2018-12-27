#ifndef SS_SSL_H
# define SS_SSL_H

#include "libft/includes/libft.h"
#include <stdio.h>
#include <math.h>
# include <stdint.h>

typedef			struct	s_md5
{
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			a0;
	uint32_t			b0;
	uint32_t			c0;
	uint32_t			d0;
	uint32_t			f;
	int					g;
	int					blocks;
}						t_md5;

void					ft_md5(uint32_t *istr, size_t len);
uint32_t				ft_left_rotate(uint32_t f, uint32_t s);
uint32_t				*ft_from_8_to_32(unsigned char *str, size_t len);
void					ft_print_md5(t_md5 *md5);


void	print_bits_32(uint32_t octet);
void	print_bits(unsigned char octet);

#endif
