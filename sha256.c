/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssavchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:46:48 by ssavchen          #+#    #+#             */
/*   Updated: 2019/01/09 16:21:43 by ssavchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const uint32_t g_z[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
	0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
	0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
	0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
	0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void			ft_algo2_sha256(t_s256 *sha, uint32_t *istr, int i)
{
	uint32_t		s1;
	uint32_t		s0;
	uint32_t		ch;
	uint32_t		maj;

	s1 = ft_right_rotate(sha->e, 6) ^ ft_right_rotate(sha->e, 11) ^
			ft_right_rotate(sha->e, 25);
	ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
	sha->tmp1 = sha->h + s1 + ch + g_z[i] + istr[i];
	s0 = ft_right_rotate(sha->a, 2) ^ ft_right_rotate(sha->a, 13) ^
			ft_right_rotate(sha->a, 22);
	maj = (sha->a & sha->b) ^ (sha->a & sha->c) ^ (sha->b & sha->c);
	sha->tmp2 = s0 + maj;
	sha->h = sha->g;
	sha->g = sha->f;
	sha->f = sha->e;
	sha->e = sha->d + sha->tmp1;
	sha->d = sha->c;
	sha->c = sha->b;
	sha->b = sha->a;
	sha->a = sha->tmp1 + sha->tmp2;
}

void			ft_algo_sha256(t_s256 *sha, uint32_t *istr)
{
	int				i;

	i = 0;
	while (i < 64)
	{
		ft_algo2_sha256(sha, istr, i);
		i++;
	}
	sha->h0 += sha->a;
	sha->h1 += sha->b;
	sha->h2 += sha->c;
	sha->h3 += sha->d;
	sha->h4 += sha->e;
	sha->h5 += sha->f;
	sha->h6 += sha->g;
	sha->h7 += sha->h;
	sha->a = sha->h0;
	sha->b = sha->h1;
	sha->c = sha->h2;
	sha->d = sha->h3;
	sha->e = sha->h4;
	sha->f = sha->h5;
	sha->g = sha->h6;
	sha->h = sha->h7;
}

void			ft_sha256(char *str, t_flag *flags, char **argv)
{
	t_s256			sha;
	int				i;
	uint32_t		*istr;

	i = 0;
	sha.str_bits = (uint64_t)ft_strlen(str);
	sha.byte_len = num_bytes(str, 256);
	if (!(sha.res_bits = (unsigned char *)malloc(sha.byte_len)))
		return ;
	ft_bzero(sha.res_bits, sha.byte_len);
	ft_memcpy(sha.res_bits, str, sha.str_bits);
	sha.res_bits = ft_append_sha256(sha.res_bits, sha.str_bits, sha.byte_len);
	istr = ft_from_8_to_32_sha256(&sha);
	init_sha256(&sha);
	while (sha.blocks)
	{
		ft_algo_sha256(&sha, istr + i);
		i += 64;
		sha.blocks--;
	}
	free(istr);
	ft_print_sha256(&sha, flags, argv);
}

int				ft_help_sha256(uint32_t *istr, int j)
{
	uint32_t	s0;
	uint32_t	s1;
	int			i;

	i = 0;
	while (i < 48)
	{
		s0 = ft_right_rotate(istr[j - 15], 7) ^
				ft_right_rotate(istr[j - 15], 18) ^ (istr[j - 15] >> 3);
		s1 = ft_right_rotate(istr[j - 2], 17) ^
				ft_right_rotate(istr[j - 2], 19) ^ (istr[j - 2] >> 10);
		istr[j] = istr[j - 16] + s0 + istr[j - 7] + s1;
		i++;
		j++;
	}
	return (j);
}

unsigned char	*ft_append_sha256(unsigned char *str, uint64_t str_len,
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
