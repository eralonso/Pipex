#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;
	
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	printf("START:\npipefd[0] == %i\n", pipefd[0]);
	printf("pipefd[1] == %i\n", pipefd[1]);
	cpid = fork();
	printf("cpid == %i\n", cpid);
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0) /* Child reads from pipe */
	{
		printf("El HIJO:\n\n");
		close(pipefd[1]);          /* Close unused write end */
	   	while (read(pipefd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
		write(STDOUT_FILENO, "\n\n", 2);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	}
	else            /* Parent writes argv[1] to pipe */
	{
		printf("El PADRE:\n\n");
		//close(pipefd[0]);          /* Close unused read end */
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);          /* Reader will see EOF */
		exit(0);
		wait(NULL);                /* Wait for child */
	}
	dprintf(2, "END:\npipefd[0] == %i\npipefd[1] == %i\n", pipefd[0], pipefd[1]);
	exit(EXIT_SUCCESS);
}
