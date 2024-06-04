#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int fd[2];
    int fd_infile = open("words.txt", O_RDONLY);
    pipe(fd);
    pid_t pid = fork();
    if (!pid)
    {
        dup2(fd_infile, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd_infile);
        close(fd[0]);
        close(fd[1]);
        char *argument_vector[] = {argv[2], NULL};
        execv(argument_vector[0], argument_vector);
        perror("Exec did not execute\n");
        return (EXIT_FAILURE);
    }
    close(fd_infile);
    int fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(fd_outfile, STDOUT_FILENO);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
    close(fd_outfile);
    char    *argument_vector1[] = {argv[3], NULL};
    waitpid(pid, NULL, 0);
    execv(argument_vector1[0], argument_vector1);
    return (0);
}
