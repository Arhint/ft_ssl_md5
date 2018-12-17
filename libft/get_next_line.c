/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssavchen <ssavchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:55:39 by ssavchen          #+#    #+#             */
/*   Updated: 2018/01/12 18:16:49 by ssavchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	ft_xwrite(char **tmp, char *bif)
{
	char	*led;

	if (!(*tmp))
		*tmp = ft_strdup(bif);
	else
	{
		led = *tmp;
		*tmp = ft_strjoin(*tmp, bif);
		ft_strdel(&led);
	}
}

static	int		ft_read_tmp(char **line, char **tmp)
{
	char	*led;

	if (ft_strchr(*tmp, '\n'))
	{
		led = *tmp;
		*line = ft_strsub(*tmp, 0, (ft_strchr(*tmp, '\n') - *tmp));
		*tmp = ft_strdup(ft_strchr(*tmp, '\n') + 1);
		if ((*tmp)[0] == '\0')
			ft_strdel(tmp);
		ft_strdel(&led);
	}
	else
	{
		*line = ft_strdup(*tmp);
		ft_strdel(tmp);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*tmp[MFD];
	int				ex;
	char			*bif;

	if (!line || fd < 0 || fd > MFD)
		return (-1);
	bif = ft_strnew(BUFF_SIZE);
	while ((ex = read(fd, bif, BUFF_SIZE)) > 0)
	{
		bif[ex] = '\0';
		ft_xwrite(&tmp[fd], bif);
		if (ft_strchr(bif, '\n'))
		{
			ft_strdel(&bif);
			return (ft_read_tmp(line, &tmp[fd]));
		}
	}
	if (ex < 0)
		return (-1);
	ft_strdel(&bif);
	if (tmp[fd])
		return (ft_read_tmp(line, &tmp[fd]));
	return (0);
}
