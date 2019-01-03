#ifndef SS_SSL_H
# define SS_SSL_H

#include "libft/includes/libft.h"
#include <stdio.h>
#include <math.h>
# include <stdint.h>

typedef					struct	s_md5
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

typedef					struct	s_s256
{
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			e;
	uint32_t			f;
	uint32_t			g;
	uint32_t			h;
	uint32_t			h0;
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	uint32_t			h4;
	uint32_t			h5;
	uint32_t			h6;
	uint32_t			h7;
	uint32_t			tmp1;
	uint32_t			tmp2;
	int					blocks;
}						t_s256;

typedef					struct t_flag
{
	int					p;
	int					q;
	int					r;
	int					s;
	int					ite;
	int					fd;
	char				*str;
}						t_flag;

void					ft_md5(uint32_t *istr, size_t len, t_flag *flags);
uint32_t				ft_left_rotate(uint32_t f, uint32_t s);
uint32_t				*ft_from_8_to_32(unsigned char *str, size_t len);
void					ft_print_md5(t_md5 *md5, t_flag *flags);

void					ft_sha256(uint32_t *istr, size_t len);
int						ft_help_sha256(uint32_t *istr, int j);
uint32_t 				ft_right_rotate(uint32_t f, uint32_t s);
uint32_t				*ft_from_8_to_32_sha256(unsigned char *str, size_t len);
void					new_gnl(const int fd, char **line);


void				print_bits_32(uint32_t octet);
void				print_bits(unsigned char octet);

#endif
