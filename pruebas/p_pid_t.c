#include	<sys/types.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<limits.h>

int	main(void)
{
	pid_t	i;

	i = INT_MAX; 	//El tipo de dato pid_t tiene el rango de INT
	printf("Rango de pid_t == %i\n", i);
	return (0);
}
