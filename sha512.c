#include "ft_ssl.h"

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

int				ft_help_sha512(uint64_t *istr, int j)
{
	uint64_t	s0;
	uint64_t	s1;
	int			i;

	i = 0;
	while (i < 64)
	{
		s0 = ft_rr512(istr[i - 15], 1) ^ ft_rr512(istr[i - 15], 8) ^
				(istr[i - 15] >> 7);
		s1 = ft_rr512(istr[i - 2], 19) ^ ft_rr512(istr[i - 2], 61) ^
				(istr[i - 2] >> 6);
		istr[j] = istr[j - 16] + s0 + istr[j - 7] + s1;
		i++;
		j++;
	}
	return (j);
}

uint64_t	*ft_from_8_to_64_sha256(t_s256 *sha)
{
	uint64_t			*istr;
	unsigned int		i;
	int					j;

	i = 0;
	j = 0;
	sha->blocks = (int)sha->byte_len / 128;
	istr = (uint64_t *)malloc(sizeof(uint64_t) * sha->blocks * 80);
	ft_bzero(istr, sha->byte_len);
	while (i < sha->blocks * 80)
	{
		istr[j] = istr[j] | sha->res_bits[i];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | sha->res_bits[i + 1];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | sha->res_bits[i + 2];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | sha->res_bits[i + 3];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | sha->res_bits[i + 4];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | sha->res_bits[i + 6];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | sha->res_bits[i + 7];
		j++;
		i += 8;
		if (j % 80 == 16)
			j = ft_help_sha512(istr, j);
	}
	free(sha->res_bits);
	return (istr);
}

void			ft_sha512(char *str, t_flag *flags, char **argv)
{
	t_s512			sha;
	int				i;
	uint64_t		*istr;

	i = 0;
	sha.str_bits = (uint64_t)ft_strlen(str);
	sha.byte_len = num_bytes(str, 512);
	sha.res_bits = (unsigned char *)malloc(sha.byte_len);
	ft_bzero(sha.res_bits, sha.byte_len);
	ft_memcpy(sha.res_bits, str, sha.str_bits);
	sha.res_bits = ft_append_sha256(sha.res_bits, sha.str_bits, sha.byte_len);
	istr = ft_from_8_to_64_sha256(&sha);
	init_sha512(&sha);
}