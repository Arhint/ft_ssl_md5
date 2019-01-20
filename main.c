/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssavchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:47:02 by ssavchen          #+#    #+#             */
/*   Updated: 2019/01/17 15:40:38 by ssavchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

void			ft_ssl_stdin(t_flag *flags, char **argv)
{
	char		**test;
	char		*string;
	int			argc;
	int			i;
	int			gnl;

	while (1)
	{
		i = 0;
		gnl = get_next_line(0, &string);
		if (ft_strcmp(string, "quit") == 0 || gnl <= 0)
			break ;
		argv = ft_strsplit(string, ' ');
		argc = ft_count_words(string, ' ') + 1;
		if (!argv[0])
		{
			free(argv[0]);
			free(argv);
			ft_strdel(&string);
			break ;
		}
		test = (char **)malloc(sizeof(char *) * (argc + 1));
		test[0] = ft_strdup("./ft_ssl> ");
		test[argc] = 0;
		while (++i < argc)
			test[i] = ft_strdup(argv[i - 1]);
		ft_ssl_out(flags, argc, test);
		ft_free_that(argv, test, string);
	}
}

void			ft_ssl_out(t_flag *flags, int argc, char **argv)
{
	if ((ft_parser_flags(flags, argc, argv)) == -1)
	{
		ft_usage_ssl(argv);
		return ;
	}
	if ((ft_strcmp(argv[1], "md5") == 0) ||
		(ft_strcmp(argv[1], "sha256") == 0) ||
		(ft_strcmp(argv[1], "sha512") == 0))
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
	t_flag		flags;

	if (argc == 1)
	{
		ft_ssl_stdin(&flags, NULL);
	}
	else if (argc > 1)
	{
		ft_ssl_out(&flags, argc, argv);
	}
	system("leaks ft_ssl");
	return (0);
}
