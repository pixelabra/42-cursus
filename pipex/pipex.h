/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:54:50 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/03/31 17:37:15 by a3y3g1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>

# include "./libft/libft.h"

void	pipex(int argc, char **argv, char **envp);
void	io_dup(int i, int argc, char **argv, int fd[2]);
void	inter_dup(pid_t pid, int fd[2]);
void	exec_cmd(int i, char **envp, char **argv);
int		dup_check(int oldfd, int newfd);
void	check_access(char **arg_vect, char **envp);
void	getcmdpath(char **arg_vect, char **envp, int i, int status);
void	ft_error(int error_code, char *str);
char	*px_strjoin(char *s1, char *s2);
void	termination_check(pid_t pid);

#endif