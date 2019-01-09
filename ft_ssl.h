/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssavchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:48:17 by ssavchen          #+#    #+#             */
/*   Updated: 2019/01/09 16:43:59 by ssavchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/includes/libft.h"
# include <math.h>
# include <stdint.h>
# include <limits.h>

typedef struct			s_md5
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
	unsigned char		*res_bits;
	uint64_t			str_bits;
	size_t				byte_len;
}						t_md5;

typedef struct			s_s256
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
	unsigned char		*res_bits;
	uint64_t			str_bits;
	size_t				byte_len;
}						t_s256;

typedef struct			s_s512
{
	uint64_t			a;
	uint64_t			b;
	uint64_t			c;
	uint64_t			d;
	uint64_t			e;
	uint64_t			f;
	uint64_t			g;
	uint64_t			h;
	uint64_t			h0;
	uint64_t			h1;
	uint64_t			h2;
	uint64_t			h3;
	uint64_t			h4;
	uint64_t			h5;
	uint64_t			h6;
	uint64_t			h7;
	uint64_t			tmp1;
	uint64_t			tmp2;
	int					blocks;
	unsigned char		*res_bits;
	uint64_t			str_bits;
	size_t				byte_len;
}						t_s512;

typedef struct			s_flag
{
	int					p;
	int					q;
	int					r;
	int					s;
	int					c;
	int					ite;
	int					fd;
	int					files;
	int					what;
	char				*str;
}						t_flag;

void					ft_md5(char *str, t_flag *flags, char **argv);
uint32_t				ft_left_rotate(uint32_t f, uint32_t s);
uint32_t				*ft_from_8_to_32(t_md5 *md5);
void					ft_print_md5(t_md5 *md5, t_flag *flags, char **argv);
size_t					num_bytes(char *str, int algo);
unsigned char			*ft_append(unsigned char *str, uint64_t str_len,
									size_t byte_len);
void					init_md5(t_md5 *md);


void					ft_sha256(char *str, t_flag *flags, char **argv);
int						ft_help_sha256(uint32_t *istr, int j);
uint32_t				ft_right_rotate(uint32_t f, uint32_t s);
uint32_t				*ft_from_8_to_32_sha256(t_s256 *sha);
void					new_gnl(int fd, char **line);
unsigned char			*ft_append_sha256(unsigned char *str, uint64_t str_len,
								size_t byte_len);
void					init_sha256(t_s256 *sha);
void					ft_printh_sha256(t_s256 *sha);
void					ft_print_sha256(t_s256 *sha, t_flag *flags,
										char **argv);
#endif
