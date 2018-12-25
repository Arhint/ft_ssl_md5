#include "ss_ssl.h"

size_t	num_bits(char *str)
{
	size_t	len;

	len = (size_t)ft_strlen(str);
	while (len * 8 % 512 != 0)
		len++;
	return (len);
}

int		main()
{
	char			str[] = "md5";
	size_t			bit_len;
	unsigned char	*res_bits;
	size_t			str_len;

	str_len = ft_strlen(str) * 8;
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
	ft_md5(res_bits, (int)bit_len);
	ft_printf("%s\n", "1bc29b36f623ba82aaf6724fd3b16718");
	return (0);
}
