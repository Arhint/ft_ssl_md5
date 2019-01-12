/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_sha512.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 20:04:15 by arh               #+#    #+#             */
/*   Updated: 2019/01/12 20:04:15 by arh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"


void			ft_printh_sha512(t_s512 *sha, uint8_t *res)
{
	res = (uint8_t *)&sha->h0;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h1;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h2;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h3;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h4;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h5;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h6;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h7;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
}

void			ft_print_sha512(t_s512 *sha, t_flag *flags, char **argv)
{
	if (flags->p == 1)
		ft_printf("%s", flags->str);
	if (!flags->p && !flags->r && !flags->q && flags->s)
		ft_printf("SHA512 (\"%s\") = ", argv[flags->ite]);
	else if (!flags->p && !flags->r && !flags->q)
		ft_printf("SHA512 (%s) = ", argv[flags->ite]);
	if (!flags->q && flags->c)
		ft_printh_sha512(sha, NULL);
	else
		ft_printf("%llx%lx%lx%lx%lx%lx%lx%lx", sha->h0, sha->h1, sha->h2, sha->h3,
				  sha->h4, sha->h5, sha->h6, sha->h7);
	if (flags->r && !flags->p && !flags->q && flags->s)
		ft_printf(" \"%s\"", argv[flags->ite]);
	else if (!flags->p && flags->r && !flags->q)
		ft_printf(" %s", argv[flags->ite]);
	ft_printf("\n");
	free(flags->str);
}

uint64_t		ft_rr512(uint64_t f, uint64_t s)
{
	return ((f >> s) | (f << (64 - s)));
}

void			init_sha512(t_s512 *sha)
{
	sha->a = 0x6a09e667f3bcc908;
	sha->b = 0xbb67ae8584caa73b;
	sha->c = 0x3c6ef372fe94f82b;
	sha->d = 0xa54ff53a5f1d36f1;
	sha->e = 0x510e527fade682d1;
	sha->f = 0x9b05688c2b3e6c1f;
	sha->g = 0x1f83d9abfb41bd6b;
	sha->h = 0x5be0cd19137e2179;
	sha->h0 = sha->a;
	sha->h1 = sha->b;
	sha->h2 = sha->c;
	sha->h3 = sha->d;
	sha->h4 = sha->e;
	sha->h5 = sha->f;
	sha->h6 = sha->g;
	sha->h7 = sha->h;
	sha->blocks = (int)sha->byte_len / 128;
}

unsigned char	*ft_append_sha512(unsigned char *str, uint64_t str_len,
									size_t byte_len)
{
	str[str_len] = 128;
	str_len *= 8;
	str[byte_len - 1] = (unsigned char)(str_len & 0xFF);
	str[byte_len - 2] = (unsigned char)(str_len >> 8 & 0xFF);
	str[byte_len - 3] = (unsigned char)(str_len >> 16 & 0xFF);
	str[byte_len - 4] = (unsigned char)(str_len >> 24 & 0xFF);
	str[byte_len - 5] = (unsigned char)(str_len >> 32 & 0xFF);
	str[byte_len - 6] = (unsigned char)(str_len >> 40 & 0xFF);
	str[byte_len - 7] = (unsigned char)(str_len >> 48 & 0xFF);
	str[byte_len - 8] = (unsigned char)(str_len >> 56 & 0xFF);
	return (str);
}
