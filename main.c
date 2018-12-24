#include "ss_ssl.h"

size_t	num_bits(char *str)
{
	size_t	len;

	len = (size_t)ft_strlen(str);
	while (len * 8 % 512 != 0)
		len++;
	return (len);
}

void	print_bits(unsigned char octet)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		octet & (1 << i) ? write(1, "1", 1) : write(1, "0", 1);
		i--;
	}
	write(1, "\n", 1);
}

void	print_bits_32(int octet)
{
	int i;

	i = 31;
	while (i >= 0)
	{
		octet & (1 << i) ? write(1, "1", 1) : write(1, "0", 1);
		i--;
	}
	write(1, "\n", 1);
}

int		main()
{
	char			str[] = "md5";
	size_t			bit_len;
	unsigned char	*res_bits;
	size_t			str_len;

	str_len = ft_strlen(str);
	bit_len = num_bits(str);
	res_bits = (unsigned char *)malloc(bit_len);
	ft_bzero(res_bits, bit_len);
	ft_memcpy(res_bits, str, ft_strlen(str));
	res_bits[ft_strlen(str)] = 128;
	res_bits[bit_len - 8] = (unsigned char)(str_len & 0x00000000000000FF);
	res_bits[bit_len - 7] = (unsigned char)(str_len & 0x000000000000FF00);
	res_bits[bit_len - 6] = (unsigned char)(str_len & 0x0000000000FF0000);
	res_bits[bit_len - 5] = (unsigned char)(str_len & 0x00000000FF000000);
	res_bits[bit_len - 4] = (unsigned char)(str_len & 0x000000FF00000000);
	res_bits[bit_len - 3] = (unsigned char)(str_len & 0x0000FF0000000000);
	res_bits[bit_len - 2] = (unsigned char)(str_len & 0x00FF000000000000);
	res_bits[bit_len - 1] = (unsigned char)(str_len & 0xFF00000000000000);
//	ft_printf("str = %s || len = %zd\n", res_bits, bit_len);
//	int				k = 1;
//	for (int i = bit_len; i != 0; i--)
//	{
//		ft_printf("%d - ", k);
//		print_bits(res_bits[bit_len - i]);
//		k++;
//	}
	ft_printf("bit_len = %d\n", bit_len);
	ft_md5(res_bits, (int)bit_len);
	ft_printf("%s\n", "1bc29b36f623ba82aaf6724fd3b16718");
	return (0);
}
