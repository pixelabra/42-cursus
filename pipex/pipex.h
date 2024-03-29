/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a3y3g1 <a3y3g1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:54:50 by a3y3g1            #+#    #+#             */
/*   Updated: 2024/03/21 23:00:05 by a3y3g1           ###   ########.fr       */
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

void	pipex(int fd[2], int argc, char **argv, char **envp);
void	io_dup(int i,  int argc, char **argv, int fd[2]);
void	inter_dup(pid_t pid, int fd[2]);
void	check_access(char **arg_vect, char **envp);
void	getcmdpath(char **arg_vect, char **envp);
void	ft_error(int error_code);
char	*px_strjoin(char *s1, char *s2);
char	**ft_getcmdpaths(char **envp);
void	exec_cmd(int i, char **envp, char **argv);

# endif