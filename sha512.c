#include "ft_ssl.h"

static const uint64_t g_q[80] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

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
//	ft_printf("x16=%lx\n", sha->a);
}

int				ft_help_sha512(uint64_t *istr, int j)
{
	uint64_t	s0;
	uint64_t	s1;
	int			i;

	i = 0;
	while (i < 64)
	{
		s0 = ft_rr512(istr[j - 15], 1) ^ ft_rr512(istr[j - 15], 8) ^
				(istr[j - 15] >> 7);
		s1 = ft_rr512(istr[j - 2], 19) ^ ft_rr512(istr[j - 2], 61) ^
				(istr[j - 2] >> 6);
		istr[j] = istr[j - 16] + s0 + istr[j - 7] + s1;
		i++;
		j++;
	}
	return (j);
}

uint64_t	*ft_from_8_to_64_sha256(t_s512 *sha)
{
	uint64_t			*istr;
	int					i;
	int					j;

	i = 0;
	j = 0;
	sha->blocks = (int)sha->byte_len / 128;
	istr = (uint64_t *)malloc(sizeof(uint64_t) * sha->blocks * 80);
	ft_bzero(istr, (size_t)sha->blocks * 80);
	while (j < sha->blocks * 80)
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
		istr[j] = istr[j] | sha->res_bits[i + 5];
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

void			ft_algo2_sha512(t_s512 *sha, uint64_t *istr, int i)
{
	uint64_t		s1;
	uint64_t		s0;
	uint64_t		ch;
	uint64_t		maj;

	s1 = ft_rr512(sha->e, 14) ^ ft_rr512(sha->e, 18) ^ ft_rr512(sha->e, 41);
	ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
	sha->tmp1 = sha->h + s1 + ch + g_q[i] + istr[i];
	s0 = ft_rr512(sha->a, 28) ^ ft_rr512(sha->a, 34) ^ ft_rr512(sha->a, 39);
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

void			ft_algo_sha512(t_s512 *sha, uint64_t *istr)
{
	int				i;

	i = 0;
	while (i < 80)
	{
		ft_algo2_sha512(sha, istr, i);
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

void			ft_print_sha512(t_s512 *sha, t_flag *flags, char **argv)
{
	if (flags->p == 1)
		ft_printf("%s", flags->str);
	if (!flags->p && !flags->r && !flags->q && flags->s)
		ft_printf("SHA512 (\"%s\") = ", argv[flags->ite]);
	else if (!flags->p && !flags->r && !flags->q)
		ft_printf("SHA512 (%s) = ", argv[flags->ite]);
//	if (!flags->q && flags->c)
//		ft_printh_sha512(sha);
//	else
		ft_printf("%llx%lx%lx%lx%lx%lx%lx%lx", sha->h0, sha->h1, sha->h2, sha->h3,
				  sha->h4, sha->h5, sha->h6, sha->h7);
	if (flags->r && !flags->p && !flags->q && flags->s)
		ft_printf(" \"%s\"", argv[flags->ite]);
	else if (!flags->p && flags->r && !flags->q)
		ft_printf(" %s", argv[flags->ite]);
	ft_printf("\n");
	free(flags->str);
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
	sha.res_bits = ft_append_sha512(sha.res_bits, sha.str_bits, sha.byte_len);
	istr = ft_from_8_to_64_sha256(&sha);
	init_sha512(&sha);
	while (sha.blocks)
	{
		ft_algo_sha512(&sha, istr + i);
		i += 80;
		sha.blocks--;
	}
	free(istr);
	ft_print_sha512(&sha, flags, argv);
}