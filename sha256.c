#include "ss_ssl.h"

static const uint32_t z[64] = {
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

void		init_sha256(t_s256 *sha, size_t len)
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
	sha->blocks = (int)len / 64;
}

void		ft_algo2_sha256(t_s256 *sha, uint32_t *istr, int i)
{
	uint32_t		s1;
	uint32_t		s0;
	uint32_t		ch;
	uint32_t		maj;

	s1 = ft_right_rotate(sha->e, 6) ^ ft_right_rotate(sha->e, 11) ^
			ft_right_rotate(sha->e, 25);
	ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
	sha->tmp1 = sha->h + s1 + ch + z[i] + istr[i];
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

void		ft_algo_sha256(t_s256 *sha, uint32_t *istr)
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

void		ft_print_sha256(t_s256 *sha)
{
	ft_printf("%x%x%x%x%x%x%x%x\n", sha->h0, sha->h1, sha->h2, sha->h3,
			sha->h4, sha->h5, sha->h6, sha->h7);
}

void		ft_sha256(uint32_t *istr, size_t len)
{
	t_s256			sha;
	int				i;

	i = 0;
	init_sha256(&sha, len);
	while (sha.blocks)
	{
		ft_algo_sha256(&sha, istr + i);
		i += 64;
		sha.blocks--;
	}
	free(istr);
	ft_print_sha256(&sha);
}

uint32_t	*ft_from_8_to_32_sha256(unsigned char *str, size_t len)
{
	uint32_t			*istr;
	unsigned int		i;
	int					j;

	i = 0;
	j = 0;
	istr = (uint32_t *) malloc(sizeof(uint32_t) * len);
	ft_bzero(istr, len);
	while (i < len)
	{
		istr[j] = istr[j] | str[i];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | str[i + 1];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | str[i + 2];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | str[i + 3];

		j++;
		i += 4;
		if (j % 64 == 16)
			j = ft_help_sha256(istr, j);
	}
	free(str);
	return (istr);
}

int			ft_help_sha256(uint32_t *istr, int j)
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
				ft_right_rotate(istr[j - 2], 19) ^(istr[j - 2] >> 10);
		istr[j] = istr[j - 16] + s0 + istr[j - 7] + s1;
		i++;
		j++;
	}
	return (j);
}

uint32_t 	ft_right_rotate(uint32_t f, uint32_t s)
{
	return ((f >> s) | (f << (32 - s)));
}