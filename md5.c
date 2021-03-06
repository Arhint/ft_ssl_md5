/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssavchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:46:38 by ssavchen          #+#    #+#             */
/*   Updated: 2019/01/09 14:47:11 by ssavchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const uint32_t g_s[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20,
	5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t g_k[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void			ft_algo_md5(t_md5 *md5, int i)
{
	if (i < 16)
	{
		md5->f = (md5->b0 & md5->c0) | ((~md5->b0) & md5->d0);
		md5->g = i;
	}
	else if (i < 32)
	{
		md5->f = (md5->d0 & md5->b0) | ((~md5->d0) & md5->c0);
		md5->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		md5->f = md5->b0 ^ md5->c0 ^ md5->d0;
		md5->g = (3 * i + 5) % 16;
	}
	else if (i < 64)
	{
		md5->f = md5->c0 ^ (md5->b0 | (~md5->d0));
		md5->g = (7 * i) % 16;
	}
}

void			ft_algo2_md5(t_md5 *md5, uint32_t *istr)
{
	int			i;

	i = 0;
	while (i < 64)
	{
		ft_algo_md5(md5, i);
		md5->f = md5->f + md5->a0 + g_k[i] + istr[md5->g];
		md5->a0 = md5->d0;
		md5->d0 = md5->c0;
		md5->c0 = md5->b0;
		md5->b0 = md5->b0 + ft_left_rotate(md5->f, g_s[i]);
		i++;
	}
	md5->a += md5->a0;
	md5->b += md5->b0;
	md5->c += md5->c0;
	md5->d += md5->d0;
	md5->a0 = md5->a;
	md5->b0 = md5->b;
	md5->c0 = md5->c;
	md5->d0 = md5->d;
	md5->blocks--;
}

void			ft_md5(char *str, t_flag *flags, char **argv)
{
	t_md5		md5;
	int			i;
	uint32_t	*istr;

	i = 0;
	md5.str_bits = (uint64_t)ft_strlen(str);
	md5.byte_len = num_bytes(str, 256);
	md5.res_bits = (unsigned char *)malloc(md5.byte_len);
	ft_bzero(md5.res_bits, md5.byte_len);
	ft_memcpy(md5.res_bits, str, md5.str_bits);
	md5.res_bits = ft_append(md5.res_bits, md5.str_bits, md5.byte_len);
	istr = ft_from_8_to_32(&md5);
	init_md5(&md5);
	while (md5.blocks)
	{
		ft_algo2_md5(&md5, istr + i);
		i += 16;
	}
	free(istr);
	ft_print_md5(&md5, flags, argv);
}

void			ft_printh_md5(t_md5 *md5, t_flag *flags)
{
	uint8_t		*res;

	res = (uint8_t *)&md5->a;
	if (!flags->q && flags->c)
	{
		ft_printf("%02x:%02x:%02x:%02x:", res[0], res[1], res[2], res[3]);
		res = (uint8_t *)&md5->b;
		ft_printf("%02x:%02x:%02x:%02x:", res[0], res[1], res[2], res[3]);
		res = (uint8_t *)&md5->c;
		ft_printf("%02x:%02x:%02x:%02x:", res[0], res[1], res[2], res[3]);
		res = (uint8_t *)&md5->d;
		ft_printf("%02x:%02x:%02x:%02x", res[0], res[1], res[2], res[3]);
	}
	else
	{
		ft_printf("%02x%02x%02x%02x", res[0], res[1], res[2], res[3]);
		res = (uint8_t *)&md5->b;
		ft_printf("%02x%02x%02x%02x", res[0], res[1], res[2], res[3]);
		res = (uint8_t *)&md5->c;
		ft_printf("%02x%02x%02x%02x", res[0], res[1], res[2], res[3]);
		res = (uint8_t *)&md5->d;
		ft_printf("%02x%02x%02x%02x", res[0], res[1], res[2], res[3]);
	}
}

void			ft_print_md5(t_md5 *md5, t_flag *flags, char **argv)
{
	if (flags->p == 1)
		ft_printf("%s", flags->str);
	if (!flags->p && !flags->r && !flags->q && flags->s)
		ft_printf("MD5 (\"%s\") = ", argv[flags->ite]);
	else if (!flags->p && !flags->r && !flags->q)
		ft_printf("MD5 (%s) = ", argv[flags->ite]);
	ft_printh_md5(md5, flags);
	if (flags->r && !flags->p && !flags->q && flags->s)
		ft_printf(" \"%s\"", argv[flags->ite]);
	else if (!flags->p && flags->r && !flags->q)
		ft_printf(" %s", argv[flags->ite]);
	ft_printf("\n");
	free(flags->str);
}
