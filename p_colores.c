#include	<stdio.h>

int	main(void)
{
	char	c;

	c = '\033';
	printf("c == %c[1;91m Hola\n", c);
	return (0);
}
