/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:47:02 by ssavchen          #+#    #+#             */
/*   Updated: 2019/01/13 21:41:25 by arh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

size_t			num_bytes(char *str, int algo)
{
	size_t			len;

	len = ft_strlen(str) + 9;
	if (algo == 256)
	{
		while (len * 8 % 512 != 0)
			len++;
	}
	else if (algo == 512)
	{
		len += 8;
		while (len * 8 % 1024 != 0)
			len++;
	}
	return (len);
}

void			ft_do_md5_or_sha256(char *str, t_flag *flags,
									int what, char **argv)
{
	if (what == 1)
		ft_md5(str, flags, argv);
	else if (what == 2)
		ft_sha256(str, flags, argv);
	else if (what == 3)
		ft_sha512(str, flags, argv);
}

int			init_flags(t_flag *flags, int argc, char **argv)
{
	if (ft_strcmp(argv[1], "sha512") == 0)
		flags->what = 3;
	else if (ft_strcmp(argv[1], "md5") == 0)
		flags->what = 1;
	else if (ft_strcmp(argv[1], "sha256") == 0)
		flags->what = 2;
	else
		return (-1);
	flags->ite = 2;
	flags->s = 0;
	flags->r = 0;
	flags->q = 0;
	if (argc == 2)
		flags->q = 1;
	flags->p = 0;
	flags->c = 0;
	flags->files = 0;
	return (0);
}

int			ft_parser_flags(t_flag *flags, int argc, char **argv)
{
	if ((init_flags(flags, argc, argv)) == -1)
		return (-1);
	while (flags->ite < argc)
	{
		if (ft_strcmp(argv[flags->ite], "-p") == 0)
			flags->p = 1;
		else if (ft_strcmp(argv[flags->ite], "-c") == 0)
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
	return (0);
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
		if ((flags->fd = open(argv[flags->ite], O_RDWR)) < 0)
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

void				ft_usage_ssl(char **argv)
{
	ft_printf("Invalid command \"%s\", did you mean: \n\n", argv[1]);
	ft_printf("command \'./ft_ssl md5\' [flags] [file]\n");
	ft_printf("command \'./ft_ssl sha256\' [flags] [file]\n\n");
}

void			ft_free_that(char **argv, char **test, char *string)
{
	int		i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	i = 0;
	while (test[i])
		free(test[i++]);
	free(test);
	ft_strdel(&string);
}

void			ft_ssl_stdin(t_flag *flags, char **argv)
{
	char		**test;
	char		*string;
	int			argc;
	int			i;

//	string = "go";
	while (1)
	{
		i = 0;
		ft_printf("%s", "./ft_ssl> ");
		get_next_line(0, &string);
		if (ft_strcmp(string, "quit") == 0)
			break;
		argv = ft_strsplit(string, ' ');
		argc = ft_count_words(string, ' ') + 1;
		test = (char **)malloc(sizeof(char *) * (argc + 1));
		test[0] = ft_strdup("./ft_ssl> ");
		test[argc] = 0;
		while (++i < argc)
			test[i] = ft_strdup(argv[i - 1]);
		ft_ssl_out(flags, argc, test);
		ft_free_that(argv, test, string);
	}
	ft_strdel(&string);
}

void		ft_ssl_out(t_flag *flags, int argc, char **argv)
{
	if ((ft_parser_flags(flags, argc, argv)) == -1)
	{
		ft_usage_ssl(argv);
		return ;
	}
	if ((ft_strcmp(argv[1], "md5") == 0) ||
		(ft_strcmp(argv[1], "sha256") == 0) || (ft_strcmp(argv[1], "sha512") == 0))
	{
		if (flags->p || !flags->files)
		{
			new_gnl(0, &flags->str);
			ft_do_md5_or_sha256(flags->str, flags, flags->what, argv);
			flags->p = 0;
		}
		while (flags->ite < argc)
		{
			ft_go_with_flags(flags, argv);
			flags->ite++;
		}
	}
}

int				main(int argc, char **argv)
{
	t_flag			flags;

	if (argc == 1)
		ft_ssl_stdin(&flags, NULL);
	else if (argc > 1)
		ft_ssl_out(&flags, argc, argv);
	return (0);
}
