#include "ss_ssl.h"

size_t		num_bytes(char *str)
{
	size_t			len;

	len = ft_strlen(str) + 1;
	while (len * 8 % 512 != 0)
		len++;
	return (len);
}

unsigned char		*ft_append(unsigned char *str, uint64_t str_len, size_t byte_len)
{
	str[str_len] = 128;
	str_len *= 8;
	str[byte_len - 8] = (unsigned char)(str_len & 0xFF);
	str[byte_len - 7] = (unsigned char)(str_len >> 8 & 0xFF);
	str[byte_len - 6] = (unsigned char)(str_len >> 16 & 0xFF);
	str[byte_len - 5] = (unsigned char)(str_len >> 24 & 0xFF);
	str[byte_len - 4] = (unsigned char)(str_len >> 32 & 0xFF);
	str[byte_len - 3] = (unsigned char)(str_len >> 40 & 0xFF);
	str[byte_len - 2] = (unsigned char)(str_len >> 48 & 0xFF);
	str[byte_len - 1] = (unsigned char)(str_len >> 56 & 0xFF);
	return (str);
}

int		main()
{
	char			str[] = "md5";
	size_t			byte_len;
	uint64_t		str_bits;
	unsigned char	*res_bits;
	uint32_t		*istr;

	str_bits = (uint64_t)ft_strlen(str) * 8;
	byte_len = num_bytes(str);
	res_bits = (unsigned char *)malloc(byte_len);
	ft_bzero(res_bits, byte_len);
	ft_memcpy(res_bits, str, ft_strlen(str));
	res_bits = ft_append(res_bits, str_bits / 8, byte_len);
	istr = ft_from_8_to_32(res_bits, byte_len);
	ft_md5(istr, byte_len);
	return (0);
}
