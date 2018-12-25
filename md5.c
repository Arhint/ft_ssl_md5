#include "ss_ssl.h"

static uint32_t s[64] = {
		7, 12, 17, 22, 7, 12, 17, 22,
		7, 12, 17, 22, 7, 12, 17, 22,
		5,  9, 14, 20, 5,  9, 14, 20,
		5,  9, 14, 20, 5,  9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23,
		4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21,
		6, 10, 15, 21, 6, 10, 15, 21
};

static uint32_t k[64] = {
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

void	init_md5(t_md5 *md)
{
	md->a = 0x67452301;
	md->b = 0xefcdab89;
	md->c = 0x98badcfe;
	md->d = 0x10325476;
}

void	ft_md5(unsigned char *res_bits, size_t len)
{
	t_md5			*md5;
	int				i = 0;
	uint32_t		a0;
	uint32_t		b0;
	uint32_t		c0;
	uint32_t		d0;
	uint32_t		f;
	int				g;
	uint32_t		*istr;

	istr = ft_from_8_to_16(res_bits, len);
	md5 = (t_md5 *)malloc(sizeof(t_md5));
	init_md5(md5);
	a0 = md5->a;
	b0 = md5->b;
	c0 = md5->c;
	d0 = md5->d;
	md5->blocks = len / 64;
	while (md5->blocks)
	{
		while (i < 64)
		{
			if (i < 16)
			{
				f = (b0 & c0) | ((~b0) & d0);
				g = i;
			}
			else if (i < 32)
			{
				f = (d0 & b0) | ((~d0) & c0);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				f = b0 ^ c0 ^ d0;
				g = (3 * i + 5) % 16;
			}
			else if (i < 64)
			{
				f = c0 ^ (b0 | (~d0));
				g = (7 * i) % 16;
			}
			f = f + a0 + k[i] + istr[g];
			a0 = d0;
			d0 = c0;
			c0 = b0;
			b0 = b0 + ft_left_rotate(f, s[i]);

			i++;
		}
		md5->a += a0;
		md5->b += b0;
		md5->c += c0;
		md5->d += d0;
		md5->blocks--;
	}
	uint8_t *p;
	p = (uint8_t *)&md5->a;
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&md5->b;
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&md5->c;
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&md5->d;
	printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3]);
	ft_printf("%x\n", md5->a);
	ft_printf("%x\n", md5->b);
	ft_printf("%x\n", md5->c);
	ft_printf("%x\n", md5->d);
}

int 	ft_left_rotate(uint32_t f, uint32_t s)
{
	return ((f << s) | (f >> (32 - s)));
}

uint32_t		*ft_from_8_to_16(unsigned char *str, int len)
{
	uint32_t *istr;
	int i = 0;
	int j = 0;

	istr = (uint32_t *) malloc(sizeof(uint32_t) * 16);
	ft_bzero(istr, (size_t)len);

	while (i < 64)
	{
		istr[j] = istr[j] | str[i + 3];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | str[i + 2];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | str[i + 1];
		istr[j] = (istr[j] << 8);
		istr[j] = istr[j] | str[i];

		j++;
		i += 4;
	}
	return (istr);
}