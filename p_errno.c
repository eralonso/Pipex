#include	<stdio.h>
#include	<string.h>

int main(void)
{
	int	i;

	i = -1;
	while (++i < 150)
		printf("errno: %i == %s\n", i, strerror(i));
	return (0);
}
