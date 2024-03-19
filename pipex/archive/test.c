/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:50:29 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/03/16 17:53:18 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void	ft_close_fds(int fd[][2], int argc, int i)
{
	if (argc < 5 || i == 0)
	{
		close(fd[0][0]);
		close(fd[argc - 3][1]);
	}
	else if (i == 1)
	{
		
		close(fd[i][0]);
		close(fd[i][1]);
		close(fd[0][0]);
		close(fd[argc - 3][1]);
	}
}

int	main(int argc, char *argv[])
{
	int		i;
	pid_t	pid[argc - 3];
	int		fd[argc - 2][2];

	fd[0][0] = open("words.txt", O_RDONLY);
	fd[argc - 3][1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	i = -1;
	while (++i < argc - 3)
	{
		if (i != argc - 4)
			pipe(fd[i + 1]);
		// printf("%d\n%d\n", pipe)
		pid[i] = fork();
		if (pid[i] == 0)
		{
			printf("This is child[%d]\n", i);
			dup2(fd[i][0], STDIN_FILENO);
			dup2(fd[i + 1][1], STDOUT_FILENO);
			ft_close_fds(fd, argc, i);
			char **arg_vect;
			arg_vect = malloc(2 * sizeof(char *));
			arg_vect[0] = argv[i + 2];
			arg_vect[1] = NULL;
			printf("arg_vect[0] = %s\n", arg_vect[0]);
			printf("arg_vect[1] = %s\n\n", arg_vect[1]);
			printf("%d\n", i);
			if (i == 0)
				execl("/usr/bin/ls", "/usr/bin/ls", "-la", NULL);
			if (i == 1)
				execlp("wc", "wc", NULL);
			// execv(arg_vect[0], arg_vect);
			return (0);
		}
		int status = 0;
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			printf("\nExited with status: %d\n\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("\nTerminated by singal: %d\n\n", WTERMSIG(status));
	}
	close(fd[0][0]);
	close(fd[argc - 3][1]);
	return (0);
}
//use a dynamically allocated double string array for execv input 