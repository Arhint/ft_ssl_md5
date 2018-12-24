#include <ss_ssl.h>

int		ss_f(int b, int c, int d)
{
	return ((b & c) | ((~b) & d));
}

int		ss_g(int b, int c, int d)
{
	return ((d & b) | ((~d) & c));
}

int		ss_h(int b, int c, int d)
{
	return (b ^ c ^ d);
}

int		ss_i(int b, int c, int d)
{
	return (c ^ (b | (~d)));
}

int		ss_ff(int a, int b, int c, int d, int ac, int *istr)
{
	a += ss_f(b, c, d) + k[i]
}