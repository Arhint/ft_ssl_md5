/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssavchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:49:19 by ssavchen          #+#    #+#             */
/*   Updated: 2019/01/09 14:52:40 by ssavchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	*ft_from_8_to_32_sha256(t_s256 *sha)
{
	uint32_t			*istr;
	unsigned int		i;
	int					j;

	i = 0;
	j = 0;
	if (!(istr = (uint32_t *)malloc(sizeof(uint32_t) * sha->byte_len)))
		return (NULL);
	ft_bzero(istr, sha->byte_len);
	while (i < sha->byte_len)
	{
		istr[j] = (istr[j] | sha->res_bits[i]) << 8;
		istr[j] = (istr[j] | sha->res_bits[i + 1]) << 8;
		istr[j] = (istr[j] | sha->res_bits[i + 2]) << 8;
		istr[j] = istr[j] | sha->res_bits[i + 3];
		j++;
		i += 4;
		if (j % 64 == 16)
			j = ft_help_sha256(istr, j);
	}
	free(sha->res_bits);
	return (istr);
}

uint32_t	ft_right_rotate(uint32_t f, uint32_t s)
{
	return ((f >> s) | (f << (32 - s)));
}

void		init_sha256(t_s256 *sha)
{
	sha->a = 0x6a09e667;
	sha->b = 0xbb67ae85;
	sha->c = 0x3c6ef372;
	sha->d = 0xa54ff53a;
	sha->e = 0x510e527f;
	sha->f = 0x9b05688c;
	sha->g = 0x1f83d9ab;
	sha->h = 0x5be0cd19;
	sha->h0 = sha->a;
	sha->h1 = sha->b;
	sha->h2 = sha->c;
	sha->h3 = sha->d;
	sha->h4 = sha->e;
	sha->h5 = sha->f;
	sha->h6 = sha->g;
	sha->h7 = sha->h;
	sha->blocks = (int)sha->byte_len / 64;
}

void		ft_printh_sha256(t_s256 *sha)
{
	uint8_t	*res;

	res = (uint8_t *)&sha->h0;
	ft_printf("%02x:%02x:%02x:%02x:", res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h1;
	ft_printf("%02x:%02x:%02x:%02x:", res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h2;
	ft_printf("%02x:%02x:%02x:%02x:", res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h3;
	ft_printf("%02x:%02x:%02x:%02x:", res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h4;
	ft_printf("%02x:%02x:%02x:%02x:", res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h5;
	ft_printf("%02x:%02x:%02x:%02x:", res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h6;
	ft_printf("%02x:%02x:%02x:%02x:", res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h7;
	ft_printf("%02x:%02x:%02x:%02x", res[3], res[2], res[1], res[0]);
}

void		ft_print_sha256(t_s256 *sha, t_flag *flags, char **argv)
{
	if (flags->p == 1)
		ft_printf("%s", flags->str);
	if (!flags->p && !flags->r && !flags->q && flags->s)
		ft_printf("SHA256 (\"%s\") = ", argv[flags->ite]);
	else if (!flags->p && !flags->r && !flags->q)
		ft_printf("SHA256 (%s) = ", argv[flags->ite]);
	if (!flags->q && flags->c)
		ft_printh_sha256(sha);
	else
		ft_printf("%x%x%x%x%x%x%x%x", sha->h0, sha->h1, sha->h2, sha->h3,
				sha->h4, sha->h5, sha->h6, sha->h7);
	if (flags->r && !flags->p && !flags->q && flags->s)
		ft_printf(" \"%s\"", argv[flags->ite]);
	else if (!flags->p && flags->r && !flags->q)
		ft_printf(" %s", argv[flags->ite]);
	ft_printf("\n");
	free(flags->str);
}
