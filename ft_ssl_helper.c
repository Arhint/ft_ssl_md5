/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssavchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:34:17 by ssavchen          #+#    #+#             */
/*   Updated: 2019/01/17 15:34:17 by ssavchen         ###   ########.fr       */
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

int				init_flags(t_flag *flags, int argc, char **argv)
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

void			ft_usage_ssl(char **argv)
{
	ft_printf("Invalid command \"%s\", did you mean: \n\n", argv[1]);
	ft_printf("command \'./ft_ssl md5\' [flags] [file]\n");
	ft_printf("command \'./ft_ssl sha256\' [flags] [file]\n\n");
}

int				ft_parser_flags(t_flag *flags, int argc, char **argv)
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

void			ft_free_that(char **argv, char **test, char *string)
{
	int			i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	i = 0;
	while (test[i])
		free(test[i++]);
	free(test);
	free(string);
}
