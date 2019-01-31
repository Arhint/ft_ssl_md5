#include "ft_ssl.h"

void		ft_init_sha384(t_s512 *sha)
{
	sha->a = 0xcbbb9d5dc1059ed8;
	sha->b = 0x629a292a367cd507;
	sha->c = 0x9159015a3070dd17;
	sha->d = 0x152fecd8f70e5939;
	sha->e = 0x67332667ffc00b31;
	sha->f = 0x8eb44a8768581511;
	sha->g = 0xdb0c2e0d64f98fa7;
	sha->h = 0x47b5481dbefa4fa4;
}

void			ft_printh_sha384(t_s512 *sha, uint8_t *res)
{
	res = (uint8_t *)&sha->h0;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h1;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h2;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h3;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h4;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
	res = (uint8_t *)&sha->h5;
	ft_printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
			  res[7], res[6], res[5], res[4], res[3], res[2], res[1], res[0]);
}

void			ft_print_sha384(t_s512 *sha, t_flag *flags, char **argv)
{
	if (flags->p == 1)
		ft_printf("%s", flags->str);
	if (!flags->p && !flags->r && !flags->q && flags->s)
		ft_printf("SHA384 (\"%s\") = ", argv[flags->ite]);
	else if (!flags->p && !flags->r && !flags->q)
		ft_printf("SHA384 (%s) = ", argv[flags->ite]);
	if (!flags->q && flags->c)
		ft_printh_sha384(sha, NULL);
	else
		ft_printf("%016lx%016lx%016lx%016lx%016lx%016lx", sha->h0,
				  sha->h1, sha->h2, sha->h3, sha->h4, sha->h5);
	if (flags->r && !flags->p && !flags->q && flags->s)
		ft_printf(" \"%s\"", argv[flags->ite]);
	else if (!flags->p && flags->r && !flags->q)
		ft_printf(" %s", argv[flags->ite]);
	ft_printf("\n");
	free(flags->str);
}