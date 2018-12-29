#include "ss_ssl.h"

size_t			num_bytes(char *str)
{
	size_t		len;

	len = ft_strlen(str) + 1;
	while (len * 8 % 512 != 0)
		len++;
	return (len);
}

void			ft_parser_flags(t_flag *flags, int argc, char **argv)
{
	int			i;

	i = 2;
	flags->num_rnds = 0;
	flags->s = 0;
	flags->r = 0;
	flags->q = 0;
	flags->p = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-p") == 0)
		{
			flags->p = 1;
			flags->num_rnds++;
		}
		else if (ft_strcmp(argv[i], "-q") == 0)
			flags->q = 1;
		else if (ft_strcmp(argv[i], "-r") == 0)
			flags->r = 1;
		else if (ft_strcmp(argv[i], "-s") == 0)
			flags->s = 1;
		i++;
	}
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

unsigned char	*ft_append(unsigned char *str, uint64_t str_len,
												size_t byte_len)
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

void			ft_do_md5_or_sha256(char *str, int what)
{
	size_t			byte_len;
	uint64_t		str_bits;
	unsigned char	*res_bits;
	uint32_t		*istr;

	str_bits = (uint64_t)ft_strlen(str);
	byte_len = num_bytes(str);
	res_bits = (unsigned char *)malloc(byte_len);
	ft_bzero(res_bits, byte_len);
	ft_memcpy(res_bits, str, str_bits);
	if (what == 1)
	{
		res_bits = ft_append(res_bits, str_bits, byte_len);
		istr = ft_from_8_to_32(res_bits, byte_len);
		ft_md5(istr, byte_len);
	}
	else if (what == 2)
	{
		res_bits = ft_append_sha256(res_bits, str_bits, byte_len);
		istr = ft_from_8_to_32_sha256(res_bits, byte_len);
		ft_sha256(istr, byte_len);
	}
}

int				main(int argc, char **argv)
{
	t_flag			flags;

	if (argc == 1)
		return (0);
	else if (argc > 1)
	{
		ft_parser_flags(&flags, argc, argv);
		if (ft_strcmp(argv[1], "md5") == 0)
			ft_do_md5_or_sha256(argv[2], 1);
		else if (ft_strcmp(argv[1], "sha256") == 0)
			ft_do_md5_or_sha256(argv[2], 2);
	}
	return (0);
}
