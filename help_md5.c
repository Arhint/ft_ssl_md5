/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssavchen <ssavchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:45:49 by ssavchen          #+#    #+#             */
/*   Updated: 2019/01/09 16:12:12 by ssavchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			new_gnl(int fd, char **line)
{
	ssize_t		ex;
	char		bif[2];
	char		*tmp;
	char		*str;

	str = ft_strdup("");
	while ((ex = read(fd, bif, 1)) > 0)
	{
		bif[ex] = '\0';
		tmp = str;
		str = ft_strjoin(str, bif);
		free(tmp);
	}
	*line = str;
}

uint32_t		ft_left_rotate(uint32_t f, uint32_t s)
{
	return ((f << s) | (f >> (32 - s)));
}

uint32_t		*ft_from_8_to_32(t_md5 *md5)
{
	uint32_t		*istr;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	istr = (uint32_t *)malloc(sizeof(uint32_t) * md5->byte_len / 4);
	ft_bzero(istr, md5->byte_len);
	while (i < md5->byte_len)
	{
		istr[j] = (istr[j] | md5->res_bits[i + 3]) << 8;
		istr[j] = (istr[j] | md5->res_bits[i + 2]) << 8;
		istr[j] = (istr[j] | md5->res_bits[i + 1]) << 8;
		istr[j] = istr[j] | md5->res_bits[i];
		j++;
		i += 4;
	}
	free(md5->res_bits);
	return (istr);
}

void			init_md5(t_md5 *md)
{
	md->a = 0x67452301;
	md->b = 0xefcdab89;
	md->c = 0x98badcfe;
	md->d = 0x10325476;
	md->a0 = md->a;
	md->b0 = md->b;
	md->c0 = md->c;
	md->d0 = md->d;
	md->blocks = (int)md->byte_len / 64;
}

unsigned char	*ft_append(unsigned char *str,
							uint64_t str_len, size_t byte_len)
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
