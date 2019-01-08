#include "ss_ssl.h"

size_t			num_bytes(char *str)
{
	size_t			len;

	len = ft_strlen(str) + 1;
	while (len * 8 % 512 != 0)
		len++;
	return (len);
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

unsigned char	*ft_append(unsigned char *str, uint64_t str_len, size_t byte_len)
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

void			ft_do_md5_or_sha256(char *str, t_flag *flags,
									int what, char **argv)
{
	if (what == 1)
		ft_md5(str, flags, argv);
	else if (what == 2)
		ft_sha256(str, flags, argv);
}

void			init_flags(t_flag *flags, int argc, char **argv)
{
	flags->ite = 2;
	flags->s = 0;
	flags->r = 0;
	flags->q = 0;
	if (argc == 2)
		flags->q = 1;
	flags->p = 0;
	flags->c = 0;
	flags->files = 0;
	flags->what = (ft_strcmp(argv[1], "md5") == 0) ? 1 : 2;
}

void			ft_parser_flags(t_flag *flags, int argc, char **argv)
{
	init_flags(flags, argc, argv);
	while (flags->ite < argc)
	{
		if (ft_strcmp(argv[flags->ite], "-p") == 0)
			flags->p = 1;
		if (ft_strcmp(argv[flags->ite], "-c") == 0)
			flags->c = 1;
		else if (ft_strcmp(argv[flags->ite], "-q") == 0)
			flags->q = 1;
		else if (ft_strcmp(argv[flags->ite], "-r") == 0)
			flags->r = 1;
		else if (ft_strcmp(argv[flags->ite], "-s") == 0)
			flags->s = flags->ite + 1;
		else
			break ;
		flags->ite++;
	}
	flags->files = argc - flags->ite;
}


void			ft_go_with_flags(t_flag *flags, char **argv)
{
	if (flags->s)
	{
		flags->str = (char *)malloc(ft_strlen(argv[flags->s]) + 1);
		ft_bzero(flags->str, ft_strlen(argv[flags->s]) + 1);
		ft_memcpy(flags->str, argv[flags->s], ft_strlen(argv[flags->s]));
		ft_do_md5_or_sha256(argv[flags->s], flags, flags->what, argv);
		flags->s = 0;
		flags->files--;
	}
	else if (flags->files > 0)
	{
		if ((flags->fd = open(argv[flags->ite], O_RDONLY)) == -1)
		{
			ft_printf("ft_ssl: %s: %s: No such file or directory\n",
					argv[1], argv[flags->ite]);
			return ;
		}
		new_gnl(flags->fd, &flags->str);
		ft_do_md5_or_sha256(flags->str, flags, flags->what, argv);
		flags->files--;
		if (!flags->files)
			flags->files = -1;
	}
}

int				ft_usage_ssl(char **argv)
{
	ft_printf("Command %s not found, did you mean: \n\n", argv[0]);
	ft_printf("command \'./ft_ssl md5\' [flags] [file]\n");
	ft_printf("command \'./ft_ssl sha256\' [flags] [file]\n");
	return (0);
}

int				main(int argc, char **argv)
{
	t_flag			flags;

	if (argc == 1)
		return (ft_usage_ssl(argv));
	else if (argc > 1)
	{
		ft_parser_flags(&flags, argc, argv);
		if ((ft_strcmp(argv[1], "md5") == 0) || (ft_strcmp(argv[1], "sha256") == 0))
		{
			if (flags.p || !flags.files)
			{
				new_gnl(0, &flags.str);
				ft_do_md5_or_sha256(flags.str, &flags, flags.what, argv);
				flags.p = 0;
			}
			while (flags.ite < argc)
			{
				ft_go_with_flags(&flags, argv);
				flags.ite++;
			}
		}
	}
	return (0);
}
